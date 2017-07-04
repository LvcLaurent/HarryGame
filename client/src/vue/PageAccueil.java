package vue;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;

import modele.ModeleTabPartie;

public class PageAccueil {
	
	private JPanel menu;
	private JPanel affichagePrincipale;
	private JTable listePartie;
	private JScrollPane gestionPartie;
	private JButton creerPartie;
	private JButton rejoindrePartie;
	private JButton spectateur;
	private JButton inscription;
	private JLabel messageBienvenue;
	private CreationPartie creationPartie;
	
	public PageAccueil(JPanel fenetre){
		menu = new JPanel();
		affichagePrincipale = new JPanel();
		creerPartie = new JButton("Créer partie");
		rejoindrePartie = new JButton("Rejoindre partie");
		spectateur = new JButton("Regarder partie");
		inscription = new JButton("Inscription");
		listePartie = new JTable();
		gestionPartie = new JScrollPane(listePartie);
		creationPartie = new CreationPartie();
		
		menu.setBackground(InterfaceGraphique.couleurJaune);
		menu.setMinimumSize(new Dimension(500, 100));
		menu.setSize(new Dimension(500, 100));
		menu.setBounds(0, 0, 500, 100);
		
		affichagePrincipale.setBackground(InterfaceGraphique.couleurBleu);
		affichagePrincipale.setPreferredSize(new Dimension(500, 400));
		affichagePrincipale.setSize(new Dimension(500, 400));
		affichagePrincipale.setBounds(0, 100, 500, 400);
		affichagePrincipale.add(creerPartie);
		affichagePrincipale.add(rejoindrePartie);
		affichagePrincipale.add(spectateur);
		affichagePrincipale.add(inscription);
		
		messageBienvenue = new JLabel("Bienvenue dans Harry");
		messageBienvenue.setFont(new Font("arial",2,30));
		menu.add(messageBienvenue);
		
		listePartie.setPreferredSize(new Dimension(450, 300));
		listePartie.setMinimumSize(new Dimension(450, 300));
		
		gestionPartie.setMinimumSize(new Dimension(450, 300));
		affichagePrincipale.add(gestionPartie);

		creerPartie.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent arg0) {
				creationPartie.setVisible(true);
			}
			
		});
		fenetre.setLayout(null);
		fenetre.add(menu);
		fenetre.add(affichagePrincipale);
	}
	public void setButtonConnecte(boolean active){
		creerPartie.setVisible(active);
		rejoindrePartie.setVisible(active);
		spectateur.setVisible(!active);
		inscription.setVisible(!active);
	}
	public JButton getInscription(){
		return inscription;
	}
	public void setJTable(ModeleTabPartie tab){
		listePartie.setModel(tab.getTab());	
	}
	public JTable getTable(){
		return listePartie;
	}
	public JButton getRejoindrePartie(){
		return rejoindrePartie;
	}
	public CreationPartie getFormCreation(){
		return creationPartie;
	}
}
