package client;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import modele.PartieInfo;
import modele.Phase1;
import modele.Phase2;

public class DecodeJSON {
	
	public static Map<String,String> decodeConnexion(String chAdecode){
		JSONObject decode = new JSONObject(chAdecode);
		Map<String,String> reponse = new HashMap<String,String>();
		for(String key : decode.keySet()){
			reponse.put(key, decode.getString(key));
		}
		return reponse;
	}
	public static ArrayList<String> decodeListePartie(String chADecode){
		ArrayList<String> reponse = new ArrayList<String>();
		JSONObject decode = new JSONObject(chADecode);
		JSONObject listeJeu;
		JSONArray decodeGame;
		decodeGame = decode.getJSONArray("games");
		for(int i=0; i < decodeGame.length(); i++){
			reponse.add(decodeGame.getJSONObject(i).toString());
		}
		return reponse;
	}
	public static PartieInfo decodePartie(String chADecode, PartieInfo partie){
		JSONObject decode = new JSONObject(chADecode);
		partie.setIdGame(decode.getString("id-game"));
		partie.setNbMaxJoueur(decode.getInt("#players"));
		partie.setNbPlaceRestante(decode.getInt("available-seats"));
		partie.setStatus(decode.getString("status"));
		partie.setCreateur(decode.getString("creator"));
		JSONArray listeJoueurs = decode.getJSONArray("players");
		for(int i=0; i<listeJoueurs.length(); i++){
			 partie.addJoueur(listeJoueurs.getString(i));
		}
		if(partie.getStatus().equals("in-progress")){
			try{
				System.out.println(decode.getInt("start-in"));
				partie.setStartIn(decode.getInt("start-in"));
			}catch(JSONException e){
				
			}
		}
		return partie;
	}
	public static void decodePartieEnCours(PartieInfo partieCourante, String chADecode){
		JSONObject decode = new JSONObject(chADecode);
		try{
			int phase = decode.getInt("phase");
			System.out.println("phase : "+phase);
			partieCourante.setPhase(phase);
			partieCourante.setIdGame(decode.getString("id-game"));
			partieCourante.setStatus("closed");
			if(phase == 1){	
				decodePhase1(decode, partieCourante);
			}else if(phase == 2){
				decodePhase2(decode, partieCourante);
			}
			
		}catch(JSONException e){
			System.out.println("phase pas lancée");
			decodePartie(chADecode, partieCourante);
		}
	}
	public static void decodePhase1(JSONObject decode, PartieInfo partieCourante){
		try{
			decode.getInt("start-next-phase");
			System.out.println("start-next-phase");
			decodeFinPhase1(decode, partieCourante);
		}catch(JSONException e){
			decodePhase1EnCours(decode, partieCourante);
		}
	}
	public static void decodeFinPhase1(JSONObject decode, PartieInfo partieCourante){
		Phase1 phase1 = partieCourante.getPhase1();
		phase1.setMotEnCours(false);
		phase1.setPhaseEnCours(false);
		phase1.setStartNextPhase(decode.getInt("start-next-phase"));
		phase1.setPoint(decodePoints(decode, "total-points"));
		phase1.setQualifie(decodeListe(decode, "qualified"));
	}
	
	public static void decodePhase1EnCours(JSONObject decode, PartieInfo partieCourante){
		Phase1 phase1 = partieCourante.getPhase1();
		phase1.setPhaseEnCours(true);
		System.out.println("phase 1 en cours");
		try{
			partieCourante.setBulles(decodeListe(decode, "circles"));
			phase1.setPoint(decodePoints(decode,"points"));
			int timeLeft = decode.getInt("time-left");
			phase1.setMotEnCours(true);
			phase1.setTimeLeft(timeLeft);
			if(timeLeft <= 3){
				phase1.setIndice(decode.getString("clue"));
			}
		}catch(JSONException e){
			phase1.setMotEnCours(false);
			phase1.setIndice(null);
			phase1.setStartNextWord(decode.getInt("start-next-word"));
			partieCourante.setPropositions(decodePropositions(decode));
			partieCourante.setGoodAnswer(decode.getString("good-answer"));
		}
	}
	
	public static void decodePhase2(JSONObject decode, PartieInfo partieCourante){
		try{
			decode.getInt("closing-time");
			System.out.println("closing-time");
			decodeFinPhase2(decode, partieCourante);
		}catch(JSONException e){
			decodePhase2EnCours(decode, partieCourante);
		}
	}
	public static void decodeFinPhase2(JSONObject decode, PartieInfo partieCourante){
		Phase2 phase2 = partieCourante.getPhase2();
		phase2.setMotEnCours(false);
		phase2.setPhaseEnCours(false);
		phase2.setClosingTime(decode.getInt("closing-time"));
		phase2.setPoint(decodePoints(decode, "points"));
	}
	public static void decodePhase2EnCours(JSONObject decode, PartieInfo partieCourante){
		Phase2 phase2 = partieCourante.getPhase2();
		phase2.setPhaseEnCours(true);
		System.out.println("phase 2 en cours");
		try{
			int startNextWord = decode.getInt("start-next-word");
			phase2.setStartNextWord(startNextWord);
			phase2.setMotEnCours(false);
			phase2.setQuestion(null);
			partieCourante.setPropositions(decodePropositions(decode));
			phase2.setTimeLeft(decode.getInt("time-left"));
			partieCourante.setGoodAnswer(decode.getString("good-answer"));
		}catch(JSONException e){
			partieCourante.setPropositions(decodePropositions(decode));
			partieCourante.setBulles(decodeListe(decode, "circles"));
			int timeLeft = decode.getInt("time-left");
			phase2.setTimeLeft(timeLeft);
			phase2.setMotEnCours(true);
			phase2.setQuestion(decode.getString("question"));
		}
	}
	public static HashMap<String, Integer> decodePoints(JSONObject decode, String keyPoints){
		HashMap<String,Integer> points = new HashMap<String, Integer>();
		JSONObject decodePoints = decode.getJSONObject(keyPoints);
		for(String key : decodePoints.keySet()){
			if(!decodePoints.isNull(key))
				points.put(key, decodePoints.getInt(key));
			else points.put(key , 0);
		}
		return points;
	}
	public static HashMap<String, String> decodePropositions(JSONObject decode){
		HashMap<String, String> propositions = new HashMap<String, String>();
		JSONObject decodePropositions = decode.getJSONObject("propositions");
		for(String key : decodePropositions.keySet()){
			if(decodePropositions.isNull(key))
				propositions.put(key, null);
			else
				propositions.put(key, decodePropositions.getString(key));
		}
		return propositions;
	}
	public static String[] decodeListe(JSONObject decode, String key){
		JSONArray liste = decode.getJSONArray(key);
		String[] chaineListe = new String[liste.length()];
		for(int i=0; i<liste.length(); i++){
			chaineListe[i] = liste.getString(i);
		}
		return chaineListe;
	}
}
