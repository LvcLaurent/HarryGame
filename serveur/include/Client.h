#ifndef _CLIENT_H
#define _CLIENT_H

#include <thread>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "../include/TraitementMessage.h"
#include "../include/Serveur.h"
#include "../include/Partie.h"

using namespace std;


class Client
{
	public:
		void timeOutSocket(int n);
		Client(int idClient, Serveur* s,int placeVectorThread);
		void start();
		void gestionMessage();
		
	private:
		int compteurPull;
		int placeVectorThread;
		int idClient;
		Partie* partie;
		Joueur* joueur;
		Serveur* serveur;
		TraitementMessage* t;
		char* token;
		int fermetureDuClient;
};


#endif
