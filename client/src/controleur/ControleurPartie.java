package controleur;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Timer;

import client.DecodeJSON;
import client.GenererJSON;
import client.HttpClient;
import client.HttpResponse;
import modele.Donnees;
import modele.PartieInfo;
import modele.Phase1;
import modele.Phase2;
import vue.InterfaceGraphique;
import vue.PageJeu;

public class ControleurPartie {
	private InterfaceGraphique vue;
	private Donnees modele;
	private HttpClient client;
	private HttpResponse reponse;
	private Timer timerPoll;
	
	public ControleurPartie(InterfaceGraphique vue, Donnees modele, HttpClient client, HttpResponse response){
		this.vue = vue;
		this.modele = modele;
		this.client = client;
		this.reponse = response;
		this.vue.getPageJeu().setListeJoueur(modele.getPartieCourante().getJoueurs());
		this.vue.changementPageJeu();
		actionReponse();
		timerPoll = new Timer(1000, new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				pollPartie();
			}
			
		});
		timerPoll.start();
	}
	public void pollPartie(){
		String query = client.genererMessage("POST", "/game/poll", GenererJSON.pollPartie(modele.getJoueur().getToken(), modele.getPartieCourante().getIdGame()));
		
		client.query(query);
		try {
			reponse.statut();
			String messJSON = reponse.lireReponse();
			System.out.println(messJSON);
			DecodeJSON.decodePartieEnCours(modele.getPartieCourante(), messJSON);
			actualiserVue();
			vue.revalidate();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void actionReponse(){
		vue.getPageJeu().getBoutonEnvoyer().addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				if(vue.getPageJeu().getReponse()!=null){	
					String query = client.genererMessage("POST", "/game/answer", GenererJSON.reponsePhase1(modele.getJoueur().getToken(), modele.getPartieCourante().getIdGame(),
							vue.getPageJeu().getReponse()));
					client.query(query);
					try {
						reponse.statut();
						reponse.lireReponse();
						
					} catch (Exception e1) {
						e1.printStackTrace();
					}
				}
			}
			
		});
	}
	public void actualiserVue(){
		PageJeu vueJeu = vue.getPageJeu();
		PartieInfo partieCourante = modele.getPartieCourante();
		String status = partieCourante.getStatus();
		if(status.equals("open")){
			vueJeu.setInfo("en attente de joueurs");
			vueJeu.getBoutonEnvoyer().setEnabled(false);
			vueJeu.setListeJoueur(partieCourante.getJoueurs());
		}else if(status.equals("in-progress")){
			vueJeu.setInfo("Partie commence dans "+ partieCourante.getStartIn()+" secondes");
			vueJeu.setListeJoueur(partieCourante.getJoueurs());
		}else{
			vueJeu.getBoutonEnvoyer().setEnabled(true);
			if(partieCourante.getPhase()==1){	
				Phase1 phase1 = partieCourante.getPhase1();
				if(phase1.isPhaseEnCours()){
					
					if(phase1.isMotEnCours()){
							vueJeu.viderGoodAnswer();
							vueJeu.viderProposition();
							vueJeu.setLabelQuestion(phase1.getIndice());
							vueJeu.setBulles(partieCourante.getBulles());
							vueJeu.getBoutonEnvoyer().setEnabled(true);
							vueJeu.setInfo("temps restant : "+phase1.getTimeLeft());
					}else{
						vueJeu.setGoodAnswer(partieCourante.getGoodAnswer());
						vueJeu.setPropositions(partieCourante.getPropositions());
						vueJeu.setInfo("Prochain mot dans "+phase1.getStartNextWord());
						vueJeu.getBoutonEnvoyer().setEnabled(false);
					}
				}else{
					vueJeu.setInfo("Prochaine phase dans "+phase1.getStartNextPhase());
					vueJeu.getBoutonEnvoyer().setEnabled(false);
				}
			}else if(partieCourante.getPhase()==2){
				Phase2 phase2 = partieCourante.getPhase2();
				if(phase2.isPhaseEnCours()){
					
					if(phase2.isMotEnCours()){
						vueJeu.viderGoodAnswer();
						vueJeu.setPropositions(partieCourante.getPropositions());
						vueJeu.setLabelQuestion(phase2.getQuestion());
						vueJeu.setBulles(partieCourante.getBulles());
						vueJeu.getBoutonEnvoyer().setEnabled(true);
						vueJeu.setInfo("temps restant : "+phase2.getTimeLeft());
					}else{
						vueJeu.setGoodAnswer(partieCourante.getGoodAnswer());
						vueJeu.setPropositions(partieCourante.getPropositions());
						vueJeu.setInfo("Prochain mot dans "+phase2.getStartNextWord());
						vueJeu.getBoutonEnvoyer().setEnabled(false);
					}
				}else{
					vueJeu.setInfo("fermeture partie dans "+phase2.getClosingTime());
					vueJeu.getBoutonEnvoyer().setEnabled(false);
				}
			}
		}
	}
}
