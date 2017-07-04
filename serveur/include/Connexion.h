#ifndef _CONNEXION_H
#define _CONNEXION_H

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
#include "../include/Serveur.h"
#include "../include/Client.h"

using namespace std;


class Connexion
{
	public:
		Connexion(int idSocket, struct sockaddr_in &adresseClient, pthread_t** threads, Serveur* s);
		
	private:
	 int idClient;
	 socklen_t sizeAccept;
};


#endif
