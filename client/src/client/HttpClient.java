package client;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class HttpClient {
	
	private Socket socket;
	private OutputStream out;
	private InputStream in;
	private BufferedWriter writer;
	private BufferedReader reader;
	private HttpResponse reponse;
	
	public HttpClient(String IP, int port) throws UnknownHostException, IOException{
		socket = new Socket(InetAddress.getByName(IP),port);
		System.out.println(socket.isConnected());
		socket.setSoTimeout(120);
		try {
			out = socket.getOutputStream();
			in = socket.getInputStream();
		} catch (IOException e) {
			e.printStackTrace();
		}
		writer = new BufferedWriter(new OutputStreamWriter(out));
		reader = new BufferedReader(new InputStreamReader(in));
		reponse = new HttpResponse(in);
	}
	public InputStream getIn(){
		return in;
	}
	public void query(String envoie){
		try {
			writer.append(envoie);
			writer.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public String genererMessage(String type, String ressource, String contenu){
		StringBuilder builder = new StringBuilder();
		builder.append(type);
		builder.append(" ");
		builder.append(ressource);
		builder.append(" HTTP/1.1\r\nHost: \r\nUser-Agent: fablag\r\nOrigin: *\r\nContent-Type: application/json\r\n"
				+ "Content-Length: "+contenu.length()+"\r\n\r\n");
		builder.append(contenu);
		return builder.toString();
	}
}
