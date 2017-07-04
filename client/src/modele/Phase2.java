package modele;

public class Phase2 extends Phase {
	private String question;
	private int closingTime;
	private String vainqueur;
	private String goodAnswer;
	
	public String getGoodAnswer() {
		return goodAnswer;
	}

	public void setGoodAnswer(String goodAnswer) {
		this.goodAnswer = goodAnswer;
	}

	public Phase2(){
		question = null;
	}

	public String getQuestion() {
		return question;
	}

	public void setQuestion(String question) {
		this.question = question;
	}

	public int getClosingTime() {
		return closingTime;
	}

	public void setClosingTime(int closingTime) {
		this.closingTime = closingTime;
	}

	public String getVainqueur() {
		return vainqueur;
	}

	public void setVainqueur(String vainqueur) {
		this.vainqueur = vainqueur;
	}
	
}
