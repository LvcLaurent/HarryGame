package vue;

import javax.swing.JButton;
import javax.swing.JPanel;

public class PageInscription extends PageForm {
	private JButton redirConnexion;
	public PageInscription(JPanel fenetre) {
		super(fenetre);
		this.redirConnexion = new JButton("Connecte-toi!");
		contenantFormulaire.add(redirConnexion);
		this.envoieForm.setText("Inscription");
	}
	public JButton getRedirConnexion(){
		return this.redirConnexion;
	}

}
