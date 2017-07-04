package modele;

import java.util.ArrayList;
import java.util.HashMap;

import client.DecodeJSON;

public class PartieInfo {
	private String idGame;
	private int nbMaxJoueur;
	private int nbPlaceRestante;
	private int phase;
	private String status;
	private String createur;
	private String minWord;
	private int startIn;
	private String goodAnswer;

	private Phase1 phase1;
	private Phase2 phase2;
	private ArrayList<String> listeJoueurs;
	private HashMap<String, String> propositions;
	private String[] bulles;
	
	
	public PartieInfo(){
		listeJoueurs = new ArrayList<String>();
		phase1 = new Phase1();
		phase2 = new Phase2();
	}
	public String getGoodAnswer() {
		return goodAnswer;
	}
	public void setGoodAnswer(String goodAnswer) {
		this.goodAnswer = goodAnswer;
	}
	public Phase2 getPhase2() {
		return phase2;
	}
	public void setPhase2(Phase2 phase2) {
		this.phase2 = phase2;
	}
	public Phase1 getPhase1(){
		return phase1;
	}
	public ArrayList<String> getJoueurs(){
		return listeJoueurs;
	}
	public void addJoueur(String joueur){
		if(!listeJoueurs.contains(joueur))
			listeJoueurs.add(joueur);
	}
	public void setIdGame(String idGame) {
		this.idGame = idGame;
	}
	public void setNbMaxJoueur(int nbMaxJoueur) {
		this.nbMaxJoueur = nbMaxJoueur;
	}
	public void setNbPlaceRestante(int nbPlaceRestante) {
		this.nbPlaceRestante = nbPlaceRestante;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public void setCreateur(String createur) {
		this.createur = createur;
	}
	public void setMinWord(String minWord) {
		this.minWord = minWord;
	}
	public void setStartIn(int start){
		this.startIn = start;
	}
	public String getIdGame() {
		return idGame;
	}
	public int getNbMaxJoueur() {
		return nbMaxJoueur;
	}
	public int getNbPlaceRestante() {
		return nbPlaceRestante;
	}
	public String getStatus() {
		return status;
	}
	public String getCreateur() {
		return createur;
	}
	public int getStartIn(){
		return startIn;
	}
	public int getPhase() {
		return phase;
	}
	public void setPhase(int phase) {
		this.phase = phase;
	}
	public String[] getBulles() {
		return bulles;
	}
	public void setBulles(String[] bulles) {
		this.bulles = bulles;
	}
	public HashMap<String, String> getPropositions() {
		return propositions;
	}
	public void setPropositions(HashMap<String, String> propositions) {
		this.propositions = propositions;
	}
	public String toString(){
		return "idGame :" + idGame +"\nnbJoueurs dans partie : "+ nbPlaceRestante+"/"+nbMaxJoueur
				+"\nstatus : "+status+"\ncreateur : "+createur;
	}
}
