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
#include "../include/GestionPartie.h"

using namespace std;

GestionPartie::GestionPartie(){
	
}

void GestionPartie::start(int idClient, char* buffer, int idSocket){
	printf("yolo on est ici avec %s",buffer);
}
