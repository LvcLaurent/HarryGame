#ifndef _TRAITEMENTMESSAGE_H
#define _TRAITEMENTMESSAGE_H
#include <iostream>
#include "../include/Serveur.h"
#include "../include/Partie.h"
#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../lib/rapidjson/include/rapidjson/document.h"         // rapidjson's DOM-style API
#include "../lib/rapidjson/include/rapidjson/prettywriter.h"     // for stringify JSON
#include "../lib/rapidjson/include/rapidjson/filestream.h"       // wrapper of C stream for prettywriter as output
#include <cstdio>
#include <string.h>




class TraitementMessage
{
	public:
		//constructeur
		TraitementMessage();
		void traitementHead(char* head,int taille);
		int traitementCommande(char* tabJson);
		void envoiAuthentifier(char* reponseServeur);
		char* retourneHeure(char *buff);
		void envoiInscrit();
		void envoiPasInscrit();
		void nettoyageT();
		void remplissage();
		void badRequest();
		void envoiLesPartie(Serveur* s);
		void envoiPartieCreer(char* id,char* login,Partie* p);
		int getContentLength();
		char* getCommande();
		char* getLogin();
		char* getPassword();
		char* getMessageATransmettre();
		int getWinnersPoints();
		int* getPoints();
		int getMinWords();
		int getNbPlayers();
		int getTailleMessage();
		char* getIdGame();
		void receptionReponse(Partie* p);
		void joinPartie(Partie* p, int n);
		void pollPartie(Partie* p);
		void envoiOption();
		void exitJeu();
		void quitterPartie(Partie * p);
		void spectate(Partie * p);
	
	
	private:
		int taille;
		char* contentType;
		char* origin;
		char* userAgent;
		char* host;
		char* commande;
		char* username;
		char* password;
		char* messageATransmettre;
		char* token;
		int players;
		int minWords;
		int* points;
		int winnerPoints;
		int tailleMessage;
		char* idGame;
		char* proposition;
};

void remplissage(char* buff);

#endif
