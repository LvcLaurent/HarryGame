#ifndef _PARTIE_H
#define _PARTIE_H

#include <thread>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <cstdio>
#include <set>
#include <vector>
#include <string>

#include "../include/Joueur.h"


using namespace std;

class Partie
{
	public:
		//constructeur
		Partie(char* id,int nbJoueurMax,char* createur,int minWord,int* points,int winnersPoints, Joueur* jou);
		void start();
		int getNbJoueurMax();
		int getEtat();
		int getNbJoueur();
		char* getId();
		char* getCreateur();
		int getMinWords();
		int* getPoints();
		int getWinnersPoints();
		char** getTabJoueur();
		char* envoiInformation();
		int inscriptionJoueur(Joueur *j);
		void enregistrerDonnee();
		void enregistrerProposition(char* proposition,char* login);
		void creationTableau();
		void distributionPoints();
		void imprimPartie();
		int getPartieCreer();
		void verifGagnant();
		void verifGagnant2();
	
	private:
		int closing;
		int* mutex;
		int* nbIndice;
		int* partieCreer;
		char* createur;
		int indice;
		int* nbReponse;
		int cercle;
		char* id;
		int minWords;
		char* reponse;
		int etat;
		Joueur* proprio;
		int* points;
		int winnersPoints;
		int ici;
		char* questionPhase2;
		int* nbJoueur;
		int* nbJoueurMax;
		char** tabGagnant;
		int gagnantPhase1;
		int gagnantPhase2;
		char** listeJoueur;
		int inProgress;
		char** phase1;
		char** phase2;
		char** tableauReponse;
		char** tableauReponse2;
		int* tabPoint;
		int* tabPointPhase2;
		int* tabPointPhase1;
		int* nbReponseBonne;
		int timeLeft;
};


#endif
