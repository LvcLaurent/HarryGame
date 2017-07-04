package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

public class HttpResponse {
	private InputStream reader;
	private HashMap<String, String> headerMap;
	
	public HttpResponse(InputStream r){
		reader = r;
		headerMap = new HashMap<String, String>();
	}
	public void statut() throws Exception{
		String statut = lireLigne();
		//System.out.println(statut);
		int code = code(statut);
		if(code!=200){
			//System.out.println(code);
			throw new Exception("erreur 401");
		}
	}
	public int code(String statut){
		String[] parseStatut = statut.split(" ");
		return Integer.parseInt(parseStatut[1]);
	}
	public String lireReponse(){
		lireHeader();
		for(String element : headerMap.keySet()){
			//System.out.println(element + " : "+ headerMap.get(element));
		}
		String type[] = headerMap.get("Content-Type").split("/");
		if(type[1].equals("json")) {
			return lireJson(Integer.parseInt(headerMap.get("Content-Length")));
		}
		else{
			return null;
		}
	}
	public void lireHeader(){
		String ret;
		String parse[];
		lireLigne();
		while((ret = lireLigne())!= null && !ret.isEmpty()){
			//System.out.println(ret);
			parse=ret.split(":",2);
			if(parse[1]!=null)
				headerMap.put(parse[0].trim(),parse[1].trim());
		}
	}
	public String lireJson(int length){
		byte[] lecture=new byte[1];
		StringBuffer buffer = new StringBuffer(length);
		for(int i=0; i<length ;i++)
			try {
				reader.read(lecture, 0, 1);
				buffer.append((char)lecture[0]);
			} catch (IOException e) {
				e.printStackTrace();
			}
		return buffer.toString();
	}
	public String lireLigne(){
		StringBuffer buffer = new StringBuffer(100);
		byte lecture[] = new byte[1];
		try {
			while(reader.read(lecture,0,1)!=-1 && (char)lecture[0] != '\r'){
				buffer.append((char)lecture[0]);
				System.out.print((char)lecture[0]);
			}
			reader.read(lecture,0,1);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return buffer.toString();
	}
}
