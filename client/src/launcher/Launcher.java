package launcher;
import org.json.JSONArray;
import org.json.JSONObject;

import controleur.Controleur;
import modele.Donnees;
import vue.InterfaceGraphique;

public class Launcher {
	
	public static void main(String args[]){
		String IP;
		int port;
		System.out.println(args.length);
		if(args.length > 0 && args[0]!=null){
			IP = args[0];
		}else IP = "127.0.0.1";
		if(args.length > 1 && args[1]!= null){
			try{
				port = Integer.parseInt(args[1]);
			}catch(NumberFormatException e){
				port = 1664;
			}
		}else port = 1664;
		InterfaceGraphique v = new InterfaceGraphique();
		Donnees d = new Donnees();
		Controleur control = new Controleur(v, d, IP, port);
		
	}
}
