#ifndef _JOUEUR_H
#define _JOUEUR_H

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


class Joueur
{
	public:
		//constructeur
		Joueur(char* l, char* pwd,int tailleL, int tailleP);
		void createToken();
		char* getLogin();
		char* getPassword();
		char* getToken();
	
	private:
		char* login;
		char* password;
		char* token;
};


#endif
