#include "../include/Connexion.h"

using namespace std;


typedef struct data data;
struct data
{
	/* paramètres */
	int idClient;
	Serveur *s;
	int placeVectorThread;
};

static void *lancementClient(void* p){ //int idClient,Serveur* s,int placeVectorThread){
	data *p_data ;//= (data*) malloc(sizeof(data));
	p_data = (data*)p;
	Client* c = new Client(p_data->idClient,p_data->s,p_data->placeVectorThread);
	//free(p_data);
	c->start();
	free(c);
	free(p_data);
}

Connexion::Connexion (int idSocket, struct sockaddr_in &adresseClient, pthread_t** threads,Serveur* s){
	int i=0;
	int taille = s->getTailleT();
	s->pushTailleT();
	
	while(1){
		data *don = (data*) malloc(sizeof(data));
		if((idClient = accept(idSocket,(struct sockaddr *) &adresseClient, &this->sizeAccept )) == -1){
				perror("accept error");
				exit(4);
		}
		s->nettoyage();
		
		don->idClient = idClient;
		don->s = s;
		don->placeVectorThread = taille;
		threads=(pthread_t**) realloc(threads,sizeof(pthread_t*)*taille);
		threads[taille-1]=(pthread_t*) realloc(threads,sizeof(pthread_t*)*taille);
		pthread_create (threads[taille-1],NULL,lancementClient, don);
		
	}
}
