package vue;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class InterfaceGraphique extends JFrame {
	
	//Couleur de th�me du jeu Harry
	public static Color couleurJaune = new Color(255, 211, 0);
	public static Color couleurBleu = new Color(0, 135, 203);
	
	private JPanel conteneurPageCo;
	private JPanel conteneurPageAccueil;
	private JPanel conteneurPageInscription;
	private JPanel conteneurPageJeu;
	private JPanel conteneurPrincipal;
	private JPanel pageActive;
	private PageConnexion pageCo;
	private PageAccueil pageAccueil;
	private PageInscription pageInscription;
	private PageJeu pageJeu;
	
	public InterfaceGraphique(){
		conteneurPageInscription = new JPanel();
		conteneurPageAccueil =  new JPanel();
		conteneurPageCo = new JPanel();
		conteneurPageJeu = new JPanel();
		conteneurPrincipal = new JPanel();
		
		initConteneur(conteneurPageCo);
		initConteneur(conteneurPageInscription);
		initConteneur(conteneurPageAccueil);
		initConteneur(conteneurPageJeu);
		initConteneur(conteneurPrincipal);
		
		pageCo = new PageConnexion(this.conteneurPageCo);
		pageAccueil = new PageAccueil(this.conteneurPageAccueil);
		pageInscription = new PageInscription(this.conteneurPageInscription);
		pageJeu = new PageJeu(this.conteneurPageJeu);
		
		actionRedirConnexion();
		actionNonConnecte();
		
		conteneurPageCo.setBackground(couleurBleu);
		conteneurPageInscription.setBackground(couleurJaune);
		
		this.conteneurPrincipal.add(conteneurPageCo);
		this.conteneurPrincipal.add(conteneurPageAccueil);
		this.conteneurPrincipal.add(conteneurPageInscription);
		this.conteneurPrincipal.add(conteneurPageJeu);
		
		this.pageActive = conteneurPageCo;
		this.conteneurPageAccueil.setVisible(false);
		this.conteneurPageCo.setVisible(true);
		this.conteneurPageInscription.setVisible(false);
		this.conteneurPageJeu.setVisible(false);
		
		this.setMinimumSize(new Dimension(500,500));
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setContentPane(conteneurPrincipal);
		this.setVisible(true);
	}
	public void initConteneur(JPanel conteneur){
		conteneur.setSize(new Dimension(500, 500));
		conteneur.setPreferredSize(new Dimension(500, 500));
	}
	
	public void changementPage(JPanel panel){
		pageActive.setVisible(false);
		panel.setVisible(true);
		pageActive = panel;
	}
	public void actionRedirConnexion(){
		pageInscription.getRedirConnexion().addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent e) {
				changementPage(conteneurPageCo);
			}
		});
	}
	public void actionNonConnecte(){
		pageAccueil.getInscription().addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent e) {
				changementPage(conteneurPageInscription);
			}
			
		});
	}
	public void changementPageAccueil(){
		changementPage(conteneurPageAccueil);
	}
	public void changementPageJeu(){
		changementPage(conteneurPageJeu);
	}
	//Getters and Setters 
	public PageConnexion getPageCo(){
		return this.pageCo;
	}
	public PageInscription getPageInscription(){
		return pageInscription;
	}
	public PageAccueil getPageAccueil(){
		return pageAccueil;
	}
	public PageJeu getPageJeu(){
		return pageJeu;
	}
	
}
