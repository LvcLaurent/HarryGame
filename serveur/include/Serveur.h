#ifndef _SERVEUR_H
#define _SERVEUR_H

#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../lib/rapidjson/include/rapidjson/document.h"         // rapidjson's DOM-style API
#include "../lib/rapidjson/include/rapidjson/prettywriter.h"     // for stringify JSON
#include "../lib/rapidjson/include/rapidjson/filestream.h" 
#include <iostream>
#include <vector>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <thread>
#include "../include/Joueur.h"
class Partie;

//using namespace std;

class Serveur
{
	public:
		int* mutex;
		Serveur();
		void nettoyage();
		void lancer(int port);
		int creationJoueur(char* login, char* password);
		int existeJoueur(char* login);
		char* authentification(char* login, char* password);
		void parcourJoueur();
		void joinServeur(int leT);
		Partie* retrouvePartie(char* idGame);
		Partie* retrouvePartie();
		int myhandler(int n);
		Joueur* getJoueur(char* login);
		Joueur* getJoueur(int n);
		int creationPartie(char* id,Joueur* j,int nbPlayers,int winnersPoints,int* points,int minWord,char* token);
		void parcourParties();
		int partieEnfinCreer();
		void ajoutPartie(Partie* p);
		Partie** getTabPartie();
		int getNbPartie();
		char* JsonDesPartie();
		int getTailleT();
		void pushTailleT();
		
	private:
		Partie** tabPartie;
		pthread_t** threads;
		pthread_t** threadsPartie;
		int** tab;
		int* nbPartie;
		int tailleTab;
		int idSocket;
		struct sockaddr_in adresseClient;
		Joueur** tabJoueur;
		int nbUser;
		int* tailleT;
};


#endif
