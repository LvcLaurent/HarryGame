package controleur;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;
import java.math.BigInteger;
import java.rmi.UnknownHostException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;

import client.DecodeJSON;
import client.GenererJSON;
import client.HttpClient;
import client.HttpResponse;
import modele.Donnees;
import vue.InterfaceGraphique;

public class Controleur {
	private HttpClient client;
	private InterfaceGraphique vue;
	private Donnees modele;
	private GenererJSON generateJSON;
	private HttpResponse reponse;
	private ControleurAccueil controlAccueil;
	
	public Controleur(InterfaceGraphique v, Donnees m, String IP, int port){
		vue = v;
		modele = m;
		generateJSON = new GenererJSON();
		try {
			client = new HttpClient(IP, port);
			reponse = new HttpResponse(client.getIn());
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e){
			e.printStackTrace();
		}
		ajouterActionEnvoyerForm();
	}
	private void ajouterActionEnvoyerForm(){
		vue.getPageCo().getEnvoieForm().addActionListener(new ActionListener(){
			
			public void actionPerformed(ActionEvent e) {
				String contenuJSON;
				HashMap<String,String> mapJSON = new HashMap<String, String>();
				String id, mdp;
				try {
					if(!(id = vue.getPageCo().champId()).isEmpty() && !(mdp = vue.getPageCo().champMdp()).isEmpty()){
						try {
							envoieFormulaireCo("/identification", id, sha256Encoding(mdp));
							try{
								reponse.statut();
								contenuJSON = reponse.lireReponse();
								System.out.println(contenuJSON);
								mapJSON = (HashMap<String, String>) DecodeJSON.decodeConnexion(contenuJSON);
								modele.getJoueur().addToken(mapJSON.get("token"));
								System.out.println(mapJSON.get("token"));
								controlAccueil = new ControleurAccueil(vue, modele, client, reponse);
								vue.changementPageAccueil();
								controlAccueil.actualiserListPartie();
							}catch(Exception e1){
								e1.printStackTrace();
							}
						} catch (UnsupportedEncodingException e2) {
							e2.printStackTrace();
						}
					}
				}catch (NoSuchAlgorithmException e2) {
					e2.printStackTrace();
				}
			}
			
		});
		vue.getPageInscription().getEnvoieForm().addActionListener(new ActionListener(){
			
			public void actionPerformed(ActionEvent e) {
				String id, mdp;
				if(!(id = vue.getPageInscription().champId()).isEmpty() && !(mdp = vue.getPageInscription().champMdp()).isEmpty())
					try {
						envoieFormulaireInscr("/account/create", id, sha256Encoding(mdp), modele.getJoueur().getToken());
						reponse.statut();
						reponse.lireReponse();
						modele.getJoueur().setId(id);
						vue.getPageAccueil().setButtonConnecte(true);
						vue.changementPageAccueil();
						controlAccueil.actualiserListPartie();
					} catch (NoSuchAlgorithmException | UnsupportedEncodingException e1) {
						e1.printStackTrace();
					} catch (Exception e1) {
						e1.printStackTrace();
					}
				
			}
			
		});
	}
	private static String sha256Encoding(String chAEncode) throws NoSuchAlgorithmException, UnsupportedEncodingException{
		MessageDigest md = MessageDigest.getInstance("SHA-256");
		md.update(chAEncode.getBytes("UTF-8"));
		byte[] hash = md.digest();
		return String.format("%0" + (hash.length*2) + "X", new BigInteger(1, hash));
	}
	private void envoieFormulaireCo(String ressource, String id, String mdp){
		String query;
		modele.ajoutJoueur(id);
		query = client.genererMessage("POST",ressource, generateJSON.connexion(id, mdp));
		System.out.println(query);
		client.query(query);

	}
	private void envoieFormulaireInscr(String ressource, String id, String mdp, String token){
		String query;
		query = client.genererMessage("POST",ressource, generateJSON.inscription(id, mdp,token));
		System.out.println(query);
		client.query(query);

	}

}
