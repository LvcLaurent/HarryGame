package modele;

import java.util.HashMap;

public class Phase1 extends Phase {
	private String indice;
	private int startNextPhase;
	private String[] qualifie; 
	
	public Phase1(){
		indice = null;
	}
	
	public String[] getQualifie() {
		return qualifie;
	}
	public void setQualifie(String[] qualifie) {
		this.qualifie = qualifie;
	}
	
	public int getStartNextPhase() {
		return startNextPhase;
	}
	public void setStartNextPhase(int startNextPhase) {
		this.startNextPhase = startNextPhase;
	}
	public String getIndice() {
		return indice;
	}
	public void setIndice(String indice) {
		this.indice = indice;
	}
	
	
}
