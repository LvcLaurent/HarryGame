package vue;

import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class CreationPartie extends JFrame {
	private JButton creerPartie;
	private JPanel phase1;
	private JPanel phase2;
	private JTextField nbJoueurs;
	private JTextField minWord;
	private JTextField winnerPoint;
	
	public CreationPartie(){
		JPanel panelPrincipal = new JPanel();
		JLabel textNbJoueur = new JLabel("nombre de joueurs : ");
		JLabel textMinWord = new JLabel("minimum nombre de mots : ");
		JLabel textWinnerPoint = new JLabel("points pour gagner : ");
		JLabel textPhase1 = new JLabel("Phase 1 : ");
		JLabel textPhase2 = new JLabel("Phase 2 : ");
		creerPartie = new JButton("Creer partie");
		phase1 = new JPanel();
		phase2 = new JPanel();
		nbJoueurs = new JTextField();
		minWord = new JTextField();
		winnerPoint = new JTextField();
		
		panelPrincipal.setPreferredSize(new Dimension(300, 300));
		textNbJoueur.setBounds(10,20,150,20);
		nbJoueurs.setBounds(150,20,20,20);
		textPhase1.setBounds(10,40,150,20);
		textMinWord.setBounds(10,60,150,20);
		minWord.setBounds(150,60,40,20);
		textPhase2.setBounds(10,80,150,20);
		textWinnerPoint.setBounds(10,100,150,20);
		winnerPoint.setBounds(150,100,40,20);
		creerPartie.setBounds(50, 120, 200, 40);
		
		panelPrincipal.setLayout(null);
		panelPrincipal.add(textNbJoueur);
		panelPrincipal.add(nbJoueurs);
		panelPrincipal.add(textPhase1);
		panelPrincipal.add(textMinWord);
		panelPrincipal.add(minWord);
		panelPrincipal.add(textPhase2);
		panelPrincipal.add(textWinnerPoint);
		panelPrincipal.add(winnerPoint);
		panelPrincipal.add(creerPartie);
		
		this.getContentPane().add(panelPrincipal);
		
		this.setPreferredSize(new Dimension(300, 300));
		this.setMinimumSize(new Dimension(300, 300));
		this.setVisible(false);
	}
	public JButton getCreerPartie(){
		return creerPartie;
	}
	public int getNbJoueurs(){
		return Integer.parseInt(nbJoueurs.getText());
	}
	public int getMinWords(){
		return Integer.parseInt(minWord.getText());
	}
	public int getWinnerPoint(){
		return Integer.parseInt(winnerPoint.getText());
	}
}
