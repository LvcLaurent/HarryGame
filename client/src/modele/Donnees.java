package modele;

import java.util.ArrayList;

public class Donnees {
	private Joueur joueurLoc;
	private ArrayList<PartieInfo> listePartie;
	private ModeleTabPartie tabInfoPartie;
	private PartieInfo partieCourante;
	
	public Donnees(){
		tabInfoPartie = new ModeleTabPartie();
	}
	public ModeleTabPartie getTabInfoPartie(){
		return tabInfoPartie;
	}
	public void ajoutJoueur(String identifiant){
		joueurLoc = new Joueur(identifiant);
	}
	public Joueur getJoueur(){
		return joueurLoc;
	}
	public void setPartieCourante(PartieInfo partie){
		partieCourante = partie;
	}
	public PartieInfo getPartieCourante(){
		return partieCourante;
	}
}
