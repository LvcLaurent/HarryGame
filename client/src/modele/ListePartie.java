package modele;

import java.util.ArrayList;

import client.DecodeJSON;

public class ListePartie {
	private ArrayList<PartieInfo> liste;
	
	public ListePartie(String chaineJSON){
		ArrayList<String> listeJSONPartie = DecodeJSON.decodeListePartie(chaineJSON);
		liste = new ArrayList<PartieInfo>();
		for(int i=0; i<listeJSONPartie.size(); i++){
			liste.add(new PartieInfo());
			DecodeJSON.decodePartie(listeJSONPartie.get(i),liste.get(i));
		}
	}
	public int getTaille(){
		return liste.size();
	}
	public PartieInfo getPartie(int i){
		if(i<liste.size()) return liste.get(i);
		else return null;
	}
	public String toString(){
		String res="";
		for(int i=0; i<liste.size(); i++){
			res += liste.get(i).toString();
			res += "\n";
		}
		return res;
	}

}
