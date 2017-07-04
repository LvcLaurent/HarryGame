package modele;

import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableModel;

public class ModeleTabPartie {
	private static String[] title = {"Cr�ateur", "places disponibles","Status" };
	private static Object[][] data = null;
	private DefaultTableModel tab;
	
	public ModeleTabPartie(){
		tab = new DefaultTableModel(data, title);
	}
	public DefaultTableModel getTab(){
		return tab;
	}
	public void setData(Object[][] data){
		this.data = data;
	}
	public void setData(ListePartie liste){
		int taille = liste.getTaille();
		for(int i=0; i<taille; i++){
			PartieInfo p = liste.getPartie(i);
			tab.addRow(new String[]{p.getCreateur(), p.getNbMaxJoueur() - p.getNbPlaceRestante()+"/"+p.getNbMaxJoueur(), p.getStatus()});
		}
	}
	

}
