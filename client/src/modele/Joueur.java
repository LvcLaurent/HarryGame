package modele;

public class Joueur {
	private String identifiant;
	private String token;
	
	public Joueur(String id){
		identifiant = id;
	}
	public void addToken(String token){
		this.token = token;
	}
	public String getToken(){
		return token;
	}
	public String getId(){
		return identifiant;
	}
	public void setId(String identifiant){
		this.identifiant = identifiant;
	}
}
