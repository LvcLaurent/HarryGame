#include <iostream>
#include <thread>
#include <time.h>
#include "../include/Serveur.h"
#include "../include/Ecoute.h"
#include "../include/Connexion.h"
#include "../include/Partie.h"
#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../include/sha256.h"

using namespace std;
using std::string;
using std::cout;
using std::endl;

#define NB_PARTIE_MAX 50
#define NB_JOUEUR_MAX 50

typedef struct dataa dataa;
struct dataa
{
	/* paramètres */
	Joueur* joueur;
	int nbPlayer;
	int winnersPoints;
	int minWords;
	int* points;
	char* id;
	char* token;
	Serveur* s;
};

static void *lancementPartie(void* p){ 
	dataa *p_data ;
	p_data = (dataa*)p;
	Partie* partie = new Partie(p_data->id,p_data->nbPlayer,p_data->joueur->getLogin(),p_data->minWords,p_data->points,p_data->winnersPoints,p_data->joueur);
	p_data->s->ajoutPartie(partie);
	*(p_data->s->mutex) = 0;
	partie->start();
	free(p_data->id);
	free(p_data->token);
	free(p_data->points);
	free(p_data);
	free(partie);
	partie = NULL;
}


int Serveur::myhandler(int n){
	
}

void Serveur::ajoutPartie(Partie* p){
	(*this->nbPartie) = (*this->nbPartie) + 1;
	this->tabPartie[(*this->nbPartie) - 1] = p;
}

int main(int argc, char *argv[]){
	int i;
	char* admin = (char*) malloc(sizeof(char)*10);
	strcpy(admin,"anonymous");
	char* mdadmin = (char*) malloc(sizeof(char)*10);
	strcpy(mdadmin,"anonymous");
	Serveur* s = new Serveur();
	s->creationJoueur(admin,mdadmin);
	strcpy(admin,"modus");
	free(mdadmin);
	mdadmin = (char*) malloc(sizeof(char)*7);
	strcpy(mdadmin,"ponens");
	s->creationJoueur(admin,mdadmin);
	i = atoi(argv[1]);
	s->parcourJoueur();
	s->lancer(i);
	
}

Serveur::Serveur(){
	this->nbUser = 0;
	this->tailleTab=0;
	this->mutex = (int*) malloc(sizeof(int));
	*this->mutex = 0;
	Joueur* j;
	this->tabJoueur =(Joueur**) malloc (sizeof(Joueur*) * NB_JOUEUR_MAX);
	(*this->tabJoueur) = NULL;
	this->tab = (int**) malloc (sizeof(int*));
	(*this->tab) = NULL;
	this->threads = (pthread_t**) malloc(sizeof(pthread_t*));
	(*this->threads) = NULL;
	this->tabPartie = (Partie**) malloc(sizeof(Partie*) * NB_PARTIE_MAX);
	(*this->tabPartie) = NULL;
	//this->threadsPartie = (pthread_t**) malloc(sizeof(pthread_t*));
	this->threadsPartie = NULL;
	this->nbPartie = (int*) malloc(sizeof(int));
	*this->nbPartie = 0;
	this->tailleT = (int*) malloc(sizeof(int));
	(*this->tailleT) = 1;
	
}

int Serveur::getTailleT(){
	return *this->tailleT;
}

void Serveur::pushTailleT(){
	(*this->tailleT) =(*this->tailleT) + 1;
}

void Serveur::nettoyage(){
	/*int i,j;
	for(i=0;i<this->tailleTab;i++)
		pthread_cancel(this->threads[this->tab[i]]);
	free(this->tab);
	this->tab = NULL;
	this->tailleTab = 0;*/
}

void Serveur::joinServeur(int leT){
	//this->tab = (int*) realloc(this->tab,sizeof(int)*(this->tailleTab+2));
	//this->tab[this->tailleTab++]=leT;
}

void Serveur::lancer(int port){
	int i;
	int* z=(int*) malloc(sizeof(int)*3);
	z[0]=2;z[1]=2;z[2]=4;
	char* token = (char*) malloc(sizeof(char)*10);
	strcpy(token,"anonymous");
	char* bufferNom= (char*) malloc(sizeof(char)*(4 +2 +2 +2));
	sprintf(bufferNom,"456465LOC");
	this->creationPartie(bufferNom,(*this->tabJoueur),2,2,z,2,token);
	sprintf(bufferNom,"456465LUC");
	//this->creationPartie(bufferNom,(*this->tabJoueur),2,10,z,4,token);
	sprintf(bufferNom,"456465LEC");
	//this->creationPartie(bufferNom,(*this->tabJoueur),2,10,z,4,token);
	sprintf(bufferNom,"456465LYC");
	//this->creationPartie(bufferNom,(*this->tabJoueur),2,10,z,4,token);
	free(token);
	free(bufferNom);
	Ecoute* e = new Ecoute(this->idSocket,this->adresseClient,port);
	Connexion* c;
	printf("J'écoute\n");
	c = new Connexion(this->idSocket, this->adresseClient,this->threads,this);
	
	shutdown(this->idSocket,2);
	close(this->idSocket);
}

int Serveur::existeJoueur(char* login){
	int i;
	for(i=0;i<this->nbUser;i++){
		if(!strcmp(this->tabJoueur[i]->getLogin(),login)) return 1;
	}
	return 0;
}

char* Serveur::authentification(char* login, char* password){
	int i;
	int taille = strlen(login);
	if(taille < 6 ) taille = 6;
	char* buff = (char*) malloc(sizeof(char)*taille);
	strcpy(buff,"error");
	if(this->existeJoueur(login))
		for(i=0;i<this->nbUser;i++)
			if(!strcmp(this->tabJoueur[i]->getLogin(),login))
				if(!strcasecmp(this->tabJoueur[i]->getPassword(),password)) return this->tabJoueur[i]->getToken();
	return buff;
		
}

int Serveur::creationJoueur(char* login, char* password){
	int tailleL = strlen(login);
	char* buff;
	int i;
	cout << login << endl;
	if(!(this->existeJoueur(password))){
		//(*this->tabJoueur) = (Joueur*) realloc((*this->tabJoueur),sizeof(Joueur)*(1+this->nbUser));
		this->tabJoueur[this->nbUser] = (Joueur*) malloc(sizeof(Joueur *));
		string output = sha256(password);
		cout << output << endl ;
		buff = (char*) malloc(sizeof(char)*output.size()+1);
		for(i=0;i<output.size();i++)
			buff[i] = output[i];
		buff[output.size()]='\0';
		cout << buff << endl;
		int tailleP = strlen(buff);
		this->tabJoueur[this->nbUser++] = new Joueur(login,buff,tailleL,tailleP);
		return 1;
	}
	else{
		return 0;
	}
}

void Serveur::parcourJoueur(){
	int i;
	cout << "Joueur : \n" ;
	for(i=0;i<this->nbUser;i++) printf("Log : %s => pwd : %s \n",this->tabJoueur[i]->getLogin(),this->tabJoueur[i]->getPassword());
}

void Serveur::parcourParties(){
	int i;
	cout << "Partie : \n" ;
	for(i=0;i<(*this->nbPartie);i++) if(this->tabPartie[i] != NULL) printf("ID : %s || nbJoueur : %d \n",this->tabPartie[i]->getId(),this->tabPartie[i]->getNbJoueurMax());
}

int Serveur::partieEnfinCreer(){
	if(*this->mutex)
		return 1;
	return 0;
}

Joueur* Serveur::getJoueur(int n){
	return this->tabJoueur[n];
}

Partie** Serveur::getTabPartie(){
	return this->tabPartie;
}

int Serveur::getNbPartie(){
	return *this->nbPartie;
}

int Serveur::creationPartie(char* id,Joueur* j,int nbPlayers,int winnersPoints,int* points,int minWord,char* token){
	int i;
	dataa *don = (dataa*) malloc(sizeof(dataa));
	don->nbPlayer = nbPlayers;
	don->joueur = j;
	don->id = id;
	don->winnersPoints = winnersPoints;
	don->points = (int*) malloc (sizeof(int) * points[0]);
	for(i = 1;i<points[0];i++) 
		don->points[i-1] = points[i];
	don->points = points;
	don->minWords=minWord;
	don->token = token;
	don->s = this;
	this->threadsPartie = (pthread_t**) realloc(this->threadsPartie,sizeof(pthread_t*)*((*this->nbPartie)+1));
	this->threadsPartie[(*this->nbPartie)] = (pthread_t*) malloc(sizeof(pthread_t*)*((*this->nbPartie)+1));
	while (*this->mutex);
	*this->mutex = 1;
	pthread_create (this->threadsPartie[(*this->nbPartie)],NULL,lancementPartie, don);
	while (*this->mutex);
	return 0;
}

Partie* Serveur::retrouvePartie(char* idGame){
	int i;
	for(i=0;i<(*this->nbPartie);i++) 
		if(!strcmp(idGame,this->tabPartie[i]->getId()))
			return this->tabPartie[i];

}

Partie* Serveur::retrouvePartie(){
	return (this->tabPartie[(*this->nbPartie)-1]);
}

Joueur* Serveur::getJoueur(char* login){
	int i;
	for(i=0;i<this->nbUser;i++) if(!strcmp(login,this->tabJoueur[i]->getLogin())) return this->tabJoueur[i];
}

char* Serveur::JsonDesPartie(){
	int c,i,j,cpt=12;
	char* temp;
	char * buff = NULL;
	buff = (char*) malloc(sizeof(char)*cpt);
	strcpy(buff,"{\"games\": [");
	for(i = 0;i<(*this->nbPartie);i++){
		cout << "i debut :" << i << endl;
		temp = NULL;
		cpt=cpt + 12 + 2 + 12 + 3 +1 +19 + strlen(this->tabPartie[i]->getId()) 
		+16 + 13+26+11 +31+1+1+3+1+1+11+strlen(this->tabPartie[i]->getCreateur()) 
		+ (2*sizeof(this->tabPartie[i]->getPoints())/4);
		buff = (char*) realloc(buff,sizeof(char)*cpt);
		sprintf(buff,"%s{\"id-game\":",buff);
		temp = (char*)realloc(temp,sizeof(char)*strlen(this->tabPartie[i]->getId())+1);
		sprintf (temp, "%s", this->tabPartie[i]->getId()) ;
		sprintf(buff,"%s\"%s\"",buff,temp);
		sprintf(buff,"%s,\"#players\":",buff);
		c=this->tabPartie[i]->getNbJoueurMax();
		sprintf (temp, "%d", c) ;
		sprintf(buff,"%s%s",buff,temp);
		c=this->tabPartie[i]->getNbJoueurMax() - this->tabPartie[i]->getNbJoueur();
		sprintf (temp, "%d", c) ;
		sprintf(buff,"%s,\"available-seats\":%s",buff,temp);
		if(!this->tabPartie[i]->getEtat()) sprintf(buff,"%s,\"status\":\"open\"",buff);
		else sprintf(buff,"%s,\"status\":\"in-progress\"",buff);
		sprintf(buff,"%s,\"creator\":\"%s\"",buff,this->tabPartie[i]->getCreateur());
		printf("%d %d\n",i,*this->nbPartie);
		sprintf(buff,"%s,\"phase-1\":{\"min-#words\":%d",buff,this->tabPartie[i]->getMinWords());
		sprintf(buff,"%s,\"points\":[",buff);
		c=this->tabPartie[i]->getPoints()[0];
		for(j=1;j<c;j++){
			sprintf(buff,"%s%d",buff,this->tabPartie[i]->getPoints()[j]);
			if(j!=c-1) sprintf(buff,"%s,",buff);
		}
		sprintf(buff,"%s]}",buff);
		sprintf(buff,"%s,\"phase-2\":{\"winner-#points\":%d}",buff,this->tabPartie[i]->getWinnersPoints());
		sprintf(buff,"%s,\"players\":[",buff);
		for(j=0;j<this->tabPartie[i]->getNbJoueur();j++){
			cpt = cpt + strlen(this->tabPartie[i]->getTabJoueur()[j])+2+1;
			buff = (char*) realloc(buff,sizeof(char)*cpt);
			sprintf(buff,"%s\"%s\"",buff,this->tabPartie[i]->getTabJoueur()[j]);
			if(j!=this->tabPartie[i]->getNbJoueur()-1) sprintf(buff,"%s,",buff);
		}
		sprintf(buff,"%s]",buff);
		sprintf(buff,"%s}",buff);
		if(i != (*this->nbPartie)-1) sprintf(buff,"%s,",buff);
		free(temp);
		cout << "i fin :" << i << endl;
	}
	sprintf(buff,"%s]}",buff);
	//strcat(buff,"]}");
	return buff;
	/*int i;
	rapidjson::Document jsonDoc;
	jsonDoc.SetObject();
	rapidjson::Value myArray(rapidjson::kArrayType);
	rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
	for(i = 0;i<this->nbPartie;i++){
		rapidjson::Value objValue;
		objValue.SetObject();
		objValue.AddMember("id-game", (*this->tabPartie)[i].getId(), allocator); 
		objValue.AddMember("#players",  (*this->tabPartie)[i].getNbJoueurMax(), allocator);

		myArray.PushBack(objValue, allocator);
	}
	jsonDoc.AddMember("games", myArray, allocator);

	const char *jsonString = jsonDoc.GetString();
	char * buff = (char*) malloc(sizeof(char)*strlen(jsonString));
	return buff;*/
}
