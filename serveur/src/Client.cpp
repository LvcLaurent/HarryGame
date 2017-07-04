
#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdexcept> 
#include <fstream>

#include "../include/Client.h"



using namespace std;


void Client::timeOutSocket(int signal){
	
}

Client::Client(int idClient, Serveur* s, int placeVectorThread){
	this->idClient = idClient;
	this->joueur = s->getJoueur(0);
	this->serveur = s;
	cout << "connecté" << endl ;
	this->t = new TraitementMessage();
	this->placeVectorThread = placeVectorThread;
	this->fermetureDuClient = 1;
	this->compteurPull = 0;
	this->partie = NULL;
}

void Client::start(){
	char buffer[1];
	char* tabJson;
	char *line = NULL;
	int lg,i,cpt,n;
	char* message;
	try{
		while (this->fermetureDuClient){
			line = NULL;
			//if(line != NULL) {cout << "ici" << endl ;free(line);}
			//line = (char*) malloc(sizeof(char));
			line = (char*) malloc (sizeof(char));
			i=0;
			cpt=1;
			buffer[0] = '\0';
			tabJson = NULL;
			cout << "Je lis" << endl;
			while(cpt != 0){
				//==============================================
				
				
				
				//==============================================
				lg = read(idClient,buffer, 1);
				line[i++] = buffer[0];
				line = (char*) realloc (line,sizeof(char)*i+2);
				line[i]='\0';
				if((i>4) && (!strcmp(line+i-4,"\r\n\r\n"))) { break;i=i-4;line[i]='\0'; break;}
				if(!strcmp(line+i-1,"}")) break ;
			}
			cout << "head : " << line << endl;
			this->t->traitementHead(line, i);
			tabJson=(char*) malloc(sizeof(char)*(this->t->getContentLength()+1));
			lg = read(idClient,tabJson, this->t->getContentLength());
			tabJson[this->t->getContentLength()] = '\0';
			cout << "\n\nJson de taille " << this->t->getContentLength() << " et Commande " << this->t->getCommande()<< " : " 
								<< tabJson << endl;
			if(! (n=this->t->traitementCommande(tabJson))) printf("\nParsing to document succeeded.\n");
			else printf("\nParsing to document no succeeded. %d\n",n);
			this->gestionMessage();
			message = this->t->getMessageATransmettre();
			printf(" j'écris : %s\n",message);
			if (this->fermetureDuClient) write(idClient,message,sizeof(char)*this->t->getTailleMessage());
			this->serveur->parcourJoueur();
			this->serveur->parcourParties();
			
			free(tabJson);
			t->nettoyageT();
			free(line);
		}
	}
	catch (ifstream::failure e) {
		cout << "Exception opening/reading file";
	}
	shutdown(idClient,2);
	close(idClient);
	cout << "fermeture socket" << endl;
	this->serveur->joinServeur(this->placeVectorThread);
	free(this->t);
}

void Client::gestionMessage(){
	char* buff;
	if(this->t->getCommande() != NULL ){
		if(!strcmp(this->t->getCommande(),"identification")){
			this->t->envoiAuthentifier((this->token = this->serveur->authentification(t->getLogin(),this->t->getPassword())));
			if(strcmp(this->token,"error")){
				this->joueur = this->serveur->getJoueur(this->t->getLogin());
			}
		}
		else if(!strcmp(t->getCommande(),"account/create")){
			if(this->serveur->creationJoueur(this->t->getLogin(),this->t->getPassword())){
				this->t->envoiInscrit();
				this->joueur = this->serveur->getJoueur(this->t->getLogin());
			}
			else
				this->t->envoiPasInscrit();	
		}
		else if(!strcmp(t->getCommande(),"exit")){
			this->fermetureDuClient = 0;
			this->t->exitJeu();
		}
		else if(!strcmp(t->getCommande(),"games/create")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			struct tm Today;
			time_t maintenant;
			time(&maintenant);
			Today = *(localtime(&maintenant));
			char* bufferNom= (char*) malloc(sizeof(char)*(4 +2 +2 +2));
			sprintf(bufferNom,"%c%c%c%02u%02u%02u",this->joueur->getLogin()[0],this->joueur->getLogin()[1],this->joueur->getLogin()[2],Today.tm_hour, Today.tm_min, Today.tm_sec);
			if(!this->serveur->creationPartie(bufferNom,this->joueur,this->t->getNbPlayers(),this->t->getWinnersPoints(),this->t->getPoints(),this->t->getMinWords(),this->joueur->getToken()))
				this->t->envoiPartieCreer(bufferNom,this->joueur->getLogin(),(this->partie = this->serveur->retrouvePartie()));
		}
		else if(!strcmp(t->getCommande(),"games/list")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			this->t->envoiLesPartie(this->serveur);
		}
		else if(!strcmp(t->getCommande(),"games/join")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			this->partie = this->serveur->retrouvePartie(this->t->getIdGame());
			this->t->joinPartie(this->partie,this->partie->inscriptionJoueur(this->joueur));
		}
		else if(!strcmp(t->getCommande(),"game/poll")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			cout << this->t->getIdGame() << endl ;
			this->partie = this->serveur->retrouvePartie(this->t->getIdGame());
			if(this->partie != NULL)
				this->t->pollPartie(this->partie);
			else this->t->badRequest();
		}
		else if(!strcmp(t->getCommande(),"game/answer")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			if(this->partie != NULL)
				this->t->receptionReponse(this->partie);
			else this->t->badRequest();
		}
		else if(!strcmp(t->getCommande(),"games/quit")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			this->partie = this->serveur->retrouvePartie(this->t->getIdGame());
			this->t->quitterPartie(this->partie);
		}
		else if(!strcmp(t->getCommande(),"games/spectate")){
			this->joueur = this->serveur->getJoueur(this->t->getLogin());
			this->partie = this->serveur->retrouvePartie(this->t->getIdGame());
			this->t->spectate(this->partie);
		}
		else if(!strcmp(t->getCommande(),"OPTION")){
			this->t->envoiOption();
		}
		else
			{cout << "icci" << endl;this->t->badRequest();}
	}
	else
		{cout << "ici" << endl;this->t->badRequest();}
}
