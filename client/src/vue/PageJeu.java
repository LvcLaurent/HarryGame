package vue;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.LineBorder;

public class PageJeu {
	private JPanel affichagePoint;
	private JPanel affichageQuestionRep;
	private JPanel affichageBulles;
	private JPanel affichageInfo;
	private JPanel affichageProposition;
	private JPanel affichageBonneReponse;
	private JLabel infoGenerale;
	private JButton buttonEnvoieRep;
	private JTextArea saisirReponse;
	private JLabel labelQuestion;
	private JLabel labelBulles;
	private ArrayList<JLabel> labelsJoueurs;
	private ArrayList<JLabel> labelsPropositions;
	private JLabel goodAnswer;
	private JScrollPane scrollPoint;
	
	public PageJeu(JPanel fenetre){
		labelsJoueurs = new ArrayList<JLabel>();
		labelsPropositions = new ArrayList<JLabel>();
		affichagePoint = new JPanel();
		affichageQuestionRep = new JPanel();
		affichageBulles = new JPanel();
		affichageInfo = new JPanel();
		affichageProposition = new JPanel();
		affichageBonneReponse = new JPanel();
		labelBulles = new JLabel();
		goodAnswer = new JLabel();
		labelBulles.setMinimumSize(new Dimension(300,50));
		affichagePoint.setBackground(InterfaceGraphique.couleurBleu);
		affichageQuestionRep.setBackground(InterfaceGraphique.couleurBleu);
		affichageBulles.setBackground(InterfaceGraphique.couleurBleu);
		affichageInfo.setBackground(InterfaceGraphique.couleurBleu);
		
		affichageInfo.setBounds(150,0,350,50);
		affichageQuestionRep.setBounds(0, 350, 500, 150);
		affichageBulles.setBounds(150, 50, 350, 100);
		affichageBonneReponse.setBounds(150, 150, 350, 50);
		affichageProposition.setBounds(150, 200, 350, 150);
		
		affichageBulles.add(labelBulles);
		
		goodAnswer.setBounds(50, 30, 100, 50);
		affichageBonneReponse.add(goodAnswer);
		
		setPanelQuestion();
		setAffichagePoint();
		setAffichageInfo();
		affichagePoint.setLayout(null);
		
		fenetre.setLayout(null);
		//fenetre.add(affichagePoint);
		fenetre.add(scrollPoint);
		fenetre.add(affichageQuestionRep);
		fenetre.add(affichageBulles);
		fenetre.add(affichageInfo);
		fenetre.add(affichageProposition);
		fenetre.add(affichageBonneReponse);
	}
	public void setPanelQuestion(){
		buttonEnvoieRep = new JButton("Envoyer");
		buttonEnvoieRep.setBounds(350, 40, 100, 50);
		saisirReponse = new JTextArea();
		saisirReponse.setBounds(30,50,250,50);
		labelQuestion = new JLabel("Ceci est la question");
		labelQuestion.setBounds(25,0,400,50);
		affichageQuestionRep.setLayout(null);
		affichageQuestionRep.add(labelQuestion);
		affichageQuestionRep.add(saisirReponse);
		affichageQuestionRep.add(buttonEnvoieRep);
	}
	public String getReponse(){
		return saisirReponse.getText();
	}
	public void setBulles(String[] bulles){
		String res="";
		for(int i=0; i<bulles.length;i++){
			res+=bulles[i]+" ";
		}
		labelBulles.setText(res);
	}
	public JLabel getLabelQuestion() {
		return labelQuestion;
	}
	public void setLabelQuestion(String question) {
		this.labelQuestion.setText(question);
	}
	public ArrayList<JLabel> getLabelsJoueurs() {
		return labelsJoueurs;
	}
	public void setLabelsJoueurs(ArrayList<JLabel> labelsJoueurs) {
		this.labelsJoueurs = labelsJoueurs;
	}
	public void setAffichagePoint(){
		scrollPoint = new JScrollPane();
		scrollPoint.setBounds(0, 0, 150, 350);
		this.scrollPoint.setBackground(Color.ORANGE);
		affichagePoint.setSize(new Dimension(150,350));
		affichagePoint.setMinimumSize(new Dimension(150,350));
		affichagePoint.setPreferredSize(new Dimension(150,350));
		//scrollPoint.setBorder(new LineBorder(InterfaceGraphique.couleurJaune));
	}
	public void setGoodAnswer(String answer){
		goodAnswer.setText("Good answer : "+answer);
	}
	public void viderGoodAnswer(){
		goodAnswer.setText("");
	}
	public void setPropositions(HashMap<String,String> propositions){
		labelsPropositions.clear();
		this.affichageProposition.removeAll();
		int cpt = 0;
		System.out.println(propositions.size());
		for(String key : propositions.keySet()){
			System.out.println(cpt);
			String chaineProposition = key + " : ";
			if(propositions.get(key)!=null)
				chaineProposition += propositions.get(key);
			else 
				chaineProposition += "aucune proposition";
			this.labelsPropositions.add(new JLabel(chaineProposition));
			this.labelsPropositions.get(cpt).setBounds(50, 70*(cpt+1)+30,100,50);
			this.affichageProposition.add(this.labelsPropositions.get(cpt));
			cpt++;
		}
	}
	public void viderProposition(){
		this.affichageProposition.removeAll();
	}
	public void setListeJoueur(ArrayList<String> joueur){
		labelsJoueurs.clear();
		this.scrollPoint.removeAll();
		for(int i=0; i<joueur.size(); i++){
			System.out.println(joueur.get(i));
			this.labelsJoueurs.add(new JLabel(joueur.get(i)));
			this.labelsJoueurs.get(i).setBounds(50, 70*(i+1),100,50);
			this.labelsJoueurs.get(i).setBackground(Color.ORANGE);
			this.scrollPoint.add(this.labelsJoueurs.get(i));
			
		}
	}
	
	public void setAffichageInfo(){
		this.infoGenerale = new JLabel();
		this.infoGenerale.setMinimumSize(new Dimension(200,50));
		this.affichageInfo.add(this.infoGenerale);
	}
	public void setInfo(String info){
		this.infoGenerale.setText(info);
	}
	public JButton getBoutonEnvoyer(){
		return buttonEnvoieRep;
	}
}
