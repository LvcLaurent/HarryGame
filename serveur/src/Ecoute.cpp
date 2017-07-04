
#include "../include/Ecoute.h"


using namespace std;

Ecoute::Ecoute(int& idSocket,struct sockaddr_in adresseClient, int port){
	struct sockaddr_in mon_address, client_address;
	int mon_address_longueur, lg;
	memset(&adresseClient, 0, sizeof(struct sockaddr_in));
	adresseClient.sin_family = AF_INET;
	adresseClient.sin_port = htons(port);
	adresseClient.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/* creation de socket */
	if ((idSocket = socket(AF_INET,SOCK_STREAM,0))== -1){
	  perror("la creation rate\n");
	  exit(1);
	}
	/*signal(SIGINT,fin);*/
	struct timeval tv;

	tv.tv_sec = 10;  /* 10 Secs Timeout */
	tv.tv_usec = 0;  // Not init'ing this can cause strange errors

	//setsockopt(idSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
		
	/* bind serveur - socket */
	if(bind(idSocket, (struct sockaddr*)& adresseClient, sizeof(struct sockaddr_in))){
		perror("bind error");
		exit(2);
	}
	
	/* ecoute sur la socket */
	if(listen(idSocket, 0)==-1){
		perror("listen error");
		exit(3);
	}
	
	memset(&adresseClient, 0, sizeof(struct sockaddr));
	
}

	
