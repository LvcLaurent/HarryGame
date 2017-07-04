#ifndef _GESTIONPARTIE_H
#define _GESTIONPARTIE_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>


class GestionPartie
{
	public:
		//constructeur
		GestionPartie();
		void start(int idClient, char* buffer, int idSocket);
	
	private:
		
};


#endif
