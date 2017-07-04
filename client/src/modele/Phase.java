package modele;

import java.util.HashMap;

public class Phase {
	protected int startNextWord;
	protected int timeLeft;
	protected HashMap<String, Integer> point;
	protected boolean motEnCours;
	protected boolean phaseEnCours;
	
	public int getTimeLeft() {
		return timeLeft;
	}
	public void setTimeLeft(int timeLeft) {
		this.timeLeft = timeLeft;
	}
	public boolean isMotEnCours() {
		return motEnCours;
	}
	public void setMotEnCours(boolean motEnCours) {
		this.motEnCours = motEnCours;
	}
	public boolean isPhaseEnCours() {
		return phaseEnCours;
	}
	public void setPhaseEnCours(boolean phaseEnCours) {
		this.phaseEnCours = phaseEnCours;
	}
	public int getStartNextWord() {
		return startNextWord;
	}
	public void setStartNextWord(int startNextWord) {
		this.startNextWord = startNextWord;
	}
	public HashMap<String, Integer> getPoint() {
		return point;
	}
	public void setPoint(HashMap<String, Integer> point) {
		this.point = point;
	}
}
