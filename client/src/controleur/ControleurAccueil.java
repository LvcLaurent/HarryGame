package controleur;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;

import client.DecodeJSON;
import client.GenererJSON;
import client.HttpClient;
import client.HttpResponse;
import modele.Donnees;
import modele.ListePartie;
import modele.ModeleTabPartie;
import modele.PartieInfo;
import vue.CreationPartie;
import vue.InterfaceGraphique;
import vue.PageJeu;

public class ControleurAccueil {
	private InterfaceGraphique vue;
	private Donnees modele;
	private HttpClient client;
	private HttpResponse reponse;
	private ModeleTabPartie tab;
	private ListePartie listePartie;
	private ControleurPartie controlPartie;
	
	public ControleurAccueil(InterfaceGraphique vue, Donnees modele, HttpClient client, HttpResponse response){
		this.vue = vue;
		this.modele = modele;
		this.client = client;
		this.reponse = response;
		this.vue.getPageAccueil().setJTable(modele.getTabInfoPartie());
		this.vue.revalidate();
		this.tab = new ModeleTabPartie();
		vue.getPageAccueil().setJTable(tab);
		if(modele.getJoueur().getId().equals("anonymous")){
			vue.getPageAccueil().setButtonConnecte(false);
		}else vue.getPageAccueil().setButtonConnecte(true);
	}
	public void actualiserListPartie(){
		try {
			String token = modele.getJoueur().getToken();
			String query = client.genererMessage("POST", "/games/list", GenererJSON.listePartie(token));
			String contenuJSON;
			HashMap<String,String> mapJSON = new HashMap<String, String>();
			System.out.println(query);
			client.query(query);
			reponse.statut();
			contenuJSON = reponse.lireReponse();
			listePartie = new ListePartie(contenuJSON);
			System.out.println(listePartie.toString());
			actionFormCreation();
			actionRejoindrePartie();
			tab = new ModeleTabPartie();
			tab.setData(listePartie);
			vue.getPageAccueil().setJTable(tab);
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public void actionFormCreation(){
		vue.getPageAccueil().getFormCreation().getCreerPartie().addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				CreationPartie formCreat =  vue.getPageAccueil().getFormCreation();
				String query = client.genererMessage("POST", "/games/create", GenererJSON.creationPartie(modele.getJoueur().getToken(), formCreat.getNbJoueurs(),
						formCreat.getMinWords(), formCreat.getWinnerPoint()));
				System.out.println(query);
				client.query(query);
				try {
					String messJSON;
					reponse.statut();
					messJSON = reponse.lireReponse();
					modele.setPartieCourante(new PartieInfo());
					DecodeJSON.decodePartie(messJSON, modele.getPartieCourante());
					vue.getPageAccueil().getFormCreation().setVisible(false);
					controlPartie = new ControleurPartie(vue, modele, client, reponse);
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
			
		});
	}
	public void actionRejoindrePartie(){
		vue.getPageAccueil().getRejoindrePartie().addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e) {
				int selectedRow;
				if((selectedRow = vue.getPageAccueil().getTable().getSelectedRow())!=-1){
					System.out.println(selectedRow);
					String query = client.genererMessage("POST", "/games/join", GenererJSON.rejoindrePartie(modele.getJoueur().getToken(), 
							listePartie.getPartie(selectedRow).getIdGame()));
					client.query(query);
					try{
						String messJSON;
						reponse.statut();
						messJSON = reponse.lireReponse();
						modele.setPartieCourante(new PartieInfo());
						DecodeJSON.decodePartie(messJSON, modele.getPartieCourante());
						vue.getPageAccueil().getFormCreation().setVisible(false);
						controlPartie = new ControleurPartie(vue, modele, client, reponse);
					}catch(Exception e1){
						e1.printStackTrace();
					}	
				}	
			}
			
		});
	}
	
}
