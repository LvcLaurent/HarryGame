package client;

import org.json.JSONArray;
import org.json.JSONObject;

public class GenererJSON {
	
	public String connexion(String identifiant, String mdp){
		JSONObject json = new JSONObject();
		json.put("username",identifiant);
		json.put("password",mdp);
		return json.toString();
	}
	public String inscription(String identifiant, String mdp, String token){
		JSONObject json = new JSONObject();
		json.put("password", mdp);
		json.put("username",identifiant);
		json.put("token", token);
		return json.toString();
	}
	
	public static String listePartie(String token){
		JSONObject json = new JSONObject();
		json.put("token", token);
		return json.toString();
	}
	public static String creationPartie(String token, int nbPlayer, int minWord, int winnerPoint){
		JSONObject json = new JSONObject();
		JSONObject jsonPhase1 = new JSONObject();
		JSONObject jsonPhase2 = new JSONObject();
		JSONArray jsonPoint = new JSONArray();
		jsonPhase1.put("min-#words", minWord);
		for(int i=nbPlayer; i>0; i--){
			jsonPoint.put(i+1);
		}
		jsonPhase2.put("winner-#points", winnerPoint);
		jsonPhase1.put("points", jsonPoint);
		json.put("token", token);
		json.put("#players", nbPlayer);
		json.put("phase-1", jsonPhase1);
		json.put("phase-2", jsonPhase2);
		return json.toString();
	}
	public static String rejoindrePartie(String token, String idGame){
		JSONObject json = new JSONObject();
		json.put("token", token);
		json.put("id-game", idGame);
		return json.toString();
	}
	public static String pollPartie(String token, String idGame){
		JSONObject json = new JSONObject();
		json.put("token", token);
		json.put("id-game", idGame);
		return json.toString();
	}
	public static String reponsePhase1(String token, String idGame, String proposition){
		JSONObject json = new JSONObject();
		json.put("token", token);
		json.put("id-game", idGame);
		json.put("proposition", proposition);
		return json.toString();
	}
}
