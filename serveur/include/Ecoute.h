#ifndef _ECOUTE_H
#define _ECOUTE_H

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
#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <thread>


class Ecoute
{
	public:
		//constructeur
		Ecoute(int &idSocket,struct sockaddr_in adresseClient, int port);
	
	
	private:
};


#endif
