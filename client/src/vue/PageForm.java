package vue;

import java.awt.Dimension;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

public class PageForm {
	protected JPanel contenantFormulaire;
	protected JLabel labelIdentifiant;
	protected JLabel labelMdp;
	protected JTextField saisieIdentifiant;
	protected JPasswordField saisieMdp;
	protected JButton envoieForm;
	
	public PageForm(JPanel fenetre){
		contenantFormulaire = new JPanel();
		labelIdentifiant = new JLabel("Identifiant :");
		labelMdp = new JLabel("Mot de passe :");
		saisieIdentifiant = new JTextField();
		saisieMdp = new JPasswordField();
		envoieForm = new JButton("Envoyer");
		
		saisieIdentifiant.setPreferredSize(new Dimension(100,20));
		saisieMdp.setPreferredSize(new Dimension(100,20));
		
		fenetre.add(contenantFormulaire);
		fenetre.setLayout(null);
		System.out.println(fenetre.getHeight());
		contenantFormulaire.setBounds(fenetre.getHeight()/2 - 100/2, fenetre.getWidth()/2 - 150/2, 100, 150);
		contenantFormulaire.add(labelIdentifiant);
		contenantFormulaire.add(saisieIdentifiant);
		contenantFormulaire.add(labelMdp);
		contenantFormulaire.add(saisieMdp);
		contenantFormulaire.add(envoieForm);
	}
	public JButton getEnvoieForm(){
		return envoieForm;
	}
	public String champId(){
		return saisieIdentifiant.getText();
	}
	@SuppressWarnings("deprecation")
	public String champMdp(){
		return saisieMdp.getText();
	}
}
