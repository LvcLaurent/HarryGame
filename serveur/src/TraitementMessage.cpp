#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../include/TraitementMessage.h"

const char * NomJourSemaine[] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"}; 
  
const char * NomMois[] = {"jan", "fev", "mar"     , "avr"  , "mai" , "jui", 
                          "jui", "aou"   , "sep", "oct", "nov", "dec"}; 

using namespace rapidjson;
using namespace std;

TraitementMessage::TraitementMessage(){
}

void TraitementMessage::traitementHead(char* head,int taille){
	int i,c;
	this->commande = NULL;
	for(i = 0; i<taille; i++){
		if ((!strncmp(head+i,"Content-Length",14)) || (!strncmp(head+i,"content-Length",14)) 
				|| (!strncmp(head+i,"Content-length",14)) || (!strncmp(head+i,"content-length",14)))  if(!(this->taille = atoi(head+i+15))) this->taille = atoi(head+i+16);
		if (!strncmp(head+i,"Content-Type",12))  ;
		if (!strncmp(head+i,"Origin",6))  ;
		if (!strncmp(head+i,"User-Agent",10))  ;
		if (!strncmp(head+i,"Host",4))  ;
		if (!strncmp(head+i,"POST",4))  for(c=0;;c++){if(*(head+i+6+c)==' ') break; 
													this->commande = (char*) realloc(this->commande,c+2*sizeof(char));
													*(this->commande+c)=*(head+i+6+c);*(this->commande+c+1)='\0';}
		if (!strncmp(head+i,"OPTION",6))  {for(c=0;;c++){if((*(head+i+c)==' ') || (*(head+i+c-1)=='N')) break; 
													this->commande = (char*) realloc(this->commande,c+2*sizeof(char));
													*(this->commande+c)=*(head+i+c);*(this->commande+c+1)='\0';}
													this->taille=0;
		}
	}
}

void TraitementMessage::envoiOption(){
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 512);
	sprintf(this->messageATransmettre,"Access-Control-Allow-Credentials: true");
	sprintf(this->messageATransmettre,"%s\r\nAccess-Control-Allow-Origin: *",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%s\r\nAccess-Control-Allow-Methods: POST, GET, OPTIONS",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%s\r\nAccess-Control-Allow-Headers: Origin, Content-Type, Accept, X-Requested-With",this->messageATransmettre);
	this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\nAccess-Control-Max-Age: 86400\r\n\r\n",this->messageATransmettre);
}

int TraitementMessage::traitementCommande(char* tabJson){
	Document document;
	int i=0,j;
	if (document.Parse<0>(tabJson).HasParseError())
                i=3;
	if(!document.IsObject()) return 1;
    if(!strcmp(this->commande,"identification")){
        this->username = (char*) malloc(sizeof(char)*((1+strlen(document["username"].GetString()))));
        for(j=0;j<strlen(document["username"].GetString());j++)this->username[j] = document["username"].GetString()[j] ;
        this->username[j] = '\0';
        this->password = (char*) malloc(sizeof(char)*(1+(strlen(document["password"].GetString()))));
        for(j=0;j<strlen(document["password"].GetString());j++)this->password[j] = document["password"].GetString()[j] ;
        this->password[j] = '\0';
	}
    else if(!strcmp(this->commande,"account/create")){
        this->username = (char*) malloc(sizeof(char)*((1+strlen(document["username"].GetString()))));
        for(j=0;j<strlen(document["username"].GetString());j++)this->username[j] = document["username"].GetString()[j] ;
        this->username[j] = '\0';
		//assert(document.HasMember("password"));
        //assert(document["password"].IsString());
        this->password = (char*) malloc(sizeof(char)*(1+(strlen(document["password"].GetString()))));
        for(j=0;j<strlen(document["password"].GetString());j++)this->password[j] = document["password"].GetString()[j] ;
        this->password[j] = '\0';
        
	}
    else if(!strcmp(this->commande,"games/create")){
		int cpt = 2;
        this->token = (char*) malloc(sizeof(char)*((1+strlen(document["token"].GetString()))));
        for(j=0;j<strlen(document["token"].GetString());j++)this->token[j] = document["token"].GetString()[j] ;
        this->token[j] = '\0';
        this->players = document["#players"].GetInt() ;
        const Value& a = document["phase-1"];
        this->minWords = a["min-#words"].GetInt();
        const Value& b = a["points"];
        this->points = NULL;
        for (Value::ConstValueIterator itr = b.Begin(); itr != b.End(); ++itr){
			this->points = (int*) realloc(this->points,sizeof(int)*cpt++);
			this->points[cpt-2] = itr->GetInt();
			printf("%d\n",this->points[cpt-2]);
		}
		this->points[0]=cpt-1;
		const Value& c = document["phase-2"];
        this->winnerPoints = c["winner-#points"].GetInt() ;
        cout << this->token << this->players << this->minWords << this->points << this->winnerPoints << endl ;
        printf("%d : %d",this->points[0],this->points[1]);
        
	}
	else if(!strcmp(this->commande,"games/list")){
		this->token = (char*) malloc(sizeof(char)*((1+strlen(document["token"].GetString()))));
        for(j=0;j<strlen(document["token"].GetString());j++)this->token[j] = document["token"].GetString()[j] ;
        this->token[j] = '\0';
		
	}
	else if (!strcmp(this->commande,"games/join")){
		this->token = (char*) malloc(sizeof(char)*((1+strlen(document["token"].GetString()))));
        for(j=0;j<strlen(document["token"].GetString());j++)this->token[j] = document["token"].GetString()[j] ;
        this->token[j] = '\0';
        this->idGame = (char*) malloc(sizeof(char)*((1+strlen(document["id-game"].GetString()))));
        for(j=0;j<strlen(document["id-game"].GetString());j++)this->idGame[j] = document["id-game"].GetString()[j] ;
        this->idGame[j] = '\0';
		
	}
	else if (!strcmp(this->commande,"game/poll")){
		this->token = (char*) malloc(sizeof(char)*((1+strlen(document["token"].GetString()))));
        for(j=0;j<strlen(document["token"].GetString());j++)this->token[j] = document["token"].GetString()[j] ;
        this->token[j] = '\0';
        this->idGame = (char*) malloc(sizeof(char)*((1+strlen(document["id-game"].GetString()))));
        for(j=0;j<strlen(document["id-game"].GetString());j++)this->idGame[j] = document["id-game"].GetString()[j] ;
        this->idGame[j] = '\0';
	}
	else if (!strcmp(this->commande,"game/answer")){
		this->token = (char*) malloc(sizeof(char)*((1+strlen(document["token"].GetString()))));
        for(j=0;j<strlen(document["token"].GetString());j++)this->token[j] = document["token"].GetString()[j] ;
        this->token[j] = '\0';
        this->idGame = (char*) malloc(sizeof(char)*((1+strlen(document["id-game"].GetString()))));
        for(j=0;j<strlen(document["id-game"].GetString());j++)this->idGame[j] = document["id-game"].GetString()[j] ;
        this->idGame[j] = '\0';
        this->proposition = (char*) malloc(sizeof(char)*((1+strlen(document["proposition"].GetString()))));
        for(j=0;j<strlen(document["proposition"].GetString());j++)this->proposition[j] = document["proposition"].GetString()[j] ;
        this->proposition[j] = '\0';
	}
	else i = 2;
    return i;
}

void TraitementMessage::envoiLesPartie(Serveur *s){
	int tailleJson;
	int i;
	this->tailleMessage = 0;
	char* json;
	json = s->JsonDesPartie();
	i=strlen(json);
	char tampon[4];
	sprintf (tampon, "%d", i) ;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char) * 512+i);
	char*  buff = NULL;
	buff = (char*) malloc(sizeof(char) * 38);
	buff = this->retourneHeure(buff);
	sprintf(this->messageATransmettre,"HTTP/1.1 200 /games/list\r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,tampon);
	sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,json);
	free(buff);
}

void TraitementMessage::envoiAuthentifier(char* reponseServeur){
	int tailleJson;
	tailleJson = strlen(reponseServeur) + 10;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char) * 512);//(18+36+17+18+14+22+24+16+4+2+tailleJson));
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 38);
	buff = this->retourneHeure(buff);
	if(!strcmp(reponseServeur,"error")){
		cout << "Pas inscrit ou mal noté" << endl ;
		sprintf(this->messageATransmettre,"HTTP/1.1 401 Connection False\r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	}
	else {
		cout << "User inscrit et co" << endl ;
		strcpy(this->messageATransmettre,"HTTP/1.1 200 Connection OK\r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		sprintf(this->messageATransmettre,"%s24",this->messageATransmettre);
		sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		sprintf(this->messageATransmettre,"%s{\n\t\"token\":\"",this->messageATransmettre);
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,reponseServeur);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s\"\n}",this->messageATransmettre);
	}
	free(buff);
}

void TraitementMessage::badRequest(){
	cout << "bad Request" << endl;
	int tailleJson = 0;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 512);
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 36);
	buff = this->retourneHeure(buff);
	strcpy(this->messageATransmettre,"HTTP/1.1 666 Bad Request \r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	free(buff);
}

void TraitementMessage::quitterPartie(Partie * p){
	int tailleJson = 0;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 512);
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 36);
	buff = this->retourneHeure(buff);
	if(p!=NULL){
		strcpy(this->messageATransmettre,"HTTP/1.1 200 Games quit \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	}
	else{
		strcpy(this->messageATransmettre,"HTTP/1.1 404 Partie Inexistante \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	}
	free(buff);
}


void TraitementMessage::exitJeu(){
	int tailleJson = 0;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 512);
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 36);
	buff = this->retourneHeure(buff);
	strcpy(this->messageATransmettre,"HTTP/1.1 200 Connection:close \r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
	this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	free(buff);
}

void TraitementMessage::envoiPartieCreer(char* id,char* login,Partie* p){
	cout << "Partie Créer" << endl;
	int i;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 2043);
	char*  buff = NULL;
	char* buffer = NULL;
	buff = (char*) malloc(sizeof(char) * 38);
	buff = this->retourneHeure(buff);
	strcpy(this->messageATransmettre,"HTTP/1.1 200 Game Create \r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	free(buff);
	buffer = (char*) malloc(sizeof(char)*((strlen(login)*3) +15 +28 +14+22+ 14+512));
	sprintf(buffer,"{\"id-game\":\"%s\",",id);
	sprintf(buffer,"%s\"#players\":%d,",buffer,this->players);
	sprintf(buffer,"%s\"available-seats\":%d,",buffer,this->players-1);
	sprintf(buffer,"%s\"status\":\"open\",\"creator\":\"%s\",",buffer,login);
	i=sprintf(buffer,"%s\"players\":[\"%s\"]}",buffer,login);
	
	sprintf(this->messageATransmettre,"%s%d",this->messageATransmettre,i);
	sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buffer);
	free(buffer);
}

void TraitementMessage::envoiInscrit(){
	int tailleJson = 0;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char) * 512);// (18+36+17+18+14+22+24+16+4+2+tailleJson));
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 38);
	buff = this->retourneHeure(buff);
	cout << "Voilà l'utilisateur inscrit sur le serveur" << endl;
	strcpy(this->messageATransmettre,"HTTP/1.1 200 Inscription OK\r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
	this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	free(buff);
}

void TraitementMessage::pollPartie(Partie* p){
	if(p!=NULL){
		cout << "Partie Rejoins" << endl;
		int i;
		this->messageATransmettre = NULL;
		this->messageATransmettre = (char*) malloc(sizeof(char)* 5043);
		char*  buff = NULL;
		char* buffer = NULL;
		buff = (char*) malloc(sizeof(char) * 38);
		buff = this->retourneHeure(buff);
		strcpy(this->messageATransmettre,"HTTP/1.1 200 Game Poll \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		free(buff);
		buffer = p->envoiInformation();
		i = (int)strlen(buffer);
		sprintf(this->messageATransmettre,"%s%d",this->messageATransmettre,i);
		sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buffer);
		free(buffer);
	}
}

void TraitementMessage::receptionReponse(Partie* p){
	if(p!=NULL){
		cout << "Reponse Enregistrer" << endl;
		int i;
		p->enregistrerProposition(this->proposition,this->username);
		this->messageATransmettre = NULL;
		this->messageATransmettre = (char*) malloc(sizeof(char)* 2043);
		char*  buff = NULL;
		char* buffer = NULL;
		buff = (char*) malloc(sizeof(char) * 36);
		buff = this->retourneHeure(buff);
		strcpy(this->messageATransmettre,"HTTP/1.1 200 Reception OK \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		free(buff);
		buffer = p->envoiInformation();
		sprintf(this->messageATransmettre,"%s%d",this->messageATransmettre,(int)strlen(buffer));
		sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buffer);
		free(buffer);
	}
}

void TraitementMessage::envoiPasInscrit(){
	cout << "Deja existant" << endl;
	int tailleJson = 0;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char) * 512);// * (18+36+17+18+14+22+24+16+4+2+tailleJson));
	char*  buff = NULL;
	buff = (char*) realloc(buff,sizeof(char) * 36);
	buff = this->retourneHeure(buff);
	cout << "Voilà l'utilisateur inscrit sur le serveur" << endl;
	strcpy(this->messageATransmettre,"HTTP/1.1 404 Identification False\r\n");
	sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
	this->remplissage();
	sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
	free(buff);
}

char* TraitementMessage::retourneHeure(char *buff){
	struct tm Today;
	time_t maintenant;

	time(&maintenant);
	Today = *(localtime(&maintenant));
	//sprintf(buff, "Date : ven, 27 nov 2015 22:00:12 GMT\n");
	sprintf(buff, "Date : %s, %d %s %d %02u:%02u:%02u GMT\n", 
	NomJourSemaine[Today.tm_wday], Today.tm_mday, NomMois[Today.tm_mon], Today.tm_year + 1900,Today.tm_hour, Today.tm_min, Today.tm_sec);
	return buff;
}

void TraitementMessage::nettoyageT(){
	if(this->messageATransmettre != NULL) {free(this->messageATransmettre);this->messageATransmettre = NULL;}
	/*if(this->contentType != NULL) free(this->contentType);
	if(this->origin != NULL) free(this->origin);
	if(this->userAgent != NULL) free(this->userAgent);
	if(this->host != NULL) free(this->host);
	if(this->commande != NULL) free(this->commande);
	if(this->username != NULL) free(this->username);
	if(this->password != NULL) free(this->password);*/
}

void TraitementMessage::spectate(Partie* p){
	if(p!=NULL){
		cout << "Partie Spectate" << endl;
		int i;
		this->messageATransmettre = NULL;
		this->messageATransmettre = (char*) malloc(sizeof(char)* 2043);
		char*  buff = NULL;
		char* buffer = NULL;
		buff = (char*) malloc(sizeof(char) * 36);
		buff = this->retourneHeure(buff);
		strcpy(this->messageATransmettre,"HTTP/1.1 200 Game Spectate \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		free(buff);
		buffer = p->envoiInformation();
		int plop = sprintf(buffer,"%s",buffer);
		sprintf(this->messageATransmettre,"%s%d",this->messageATransmettre,plop);
		sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buffer);
		free(buffer);
	}
	else{
		
	}
}


void TraitementMessage::remplissage(){
	sprintf(this->messageATransmettre,"%sServer: fablag_server/1.0\r\n",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%sPragma: no-cache\r\n",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%sConnection: keep-alive\r\n",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%sAccess-Control-Allow-Origin: *\r\n",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%sContent-Type: application/json\r\n",this->messageATransmettre);
	sprintf(this->messageATransmettre,"%sContent-Length: ",this->messageATransmettre);
}

void TraitementMessage::joinPartie(Partie* p,int n){
	int i;
	this->messageATransmettre = NULL;
	this->messageATransmettre = (char*) malloc(sizeof(char)* 2043);
	char*  buff = NULL;
	char* buffer = NULL;
	buff = (char*) malloc(sizeof(char) * 38);
	buff = this->retourneHeure(buff);
	if(p!=NULL){
		if (n==0){
			cout << "Partie Rejoins" << endl;
			strcpy(this->messageATransmettre,"HTTP/1.1 200 Game Join \r\n");
			sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
			this->remplissage();
			free(buff);
			buffer = p->envoiInformation();
			int plop = sprintf(buffer,"%s",buffer);
			sprintf(this->messageATransmettre,"%s%d",this->messageATransmettre,plop);
			sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
			this->tailleMessage = sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buffer);
			free(buffer);
		}
		else{
			strcpy(this->messageATransmettre,"HTTP/1.1 410 Plus de place \r\n");
			sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
			this->remplissage();
			sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
			this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		}
	}
	else{
		strcpy(this->messageATransmettre,"HTTP/1.1 404 Game no Exist \r\n");
		sprintf(this->messageATransmettre,"%s%s",this->messageATransmettre,buff);
		this->remplissage();
		sprintf(this->messageATransmettre,"%s0",this->messageATransmettre);
		this->tailleMessage = sprintf(this->messageATransmettre,"%s\r\n\r\n",this->messageATransmettre);
		
	}
}

int TraitementMessage::getContentLength(){
	return this->taille;
}

char* TraitementMessage::getCommande(){
	return this->commande;
}

char* TraitementMessage::getLogin(){
	return this->username;
}

char* TraitementMessage::getPassword(){
	return this->password;
}

char* TraitementMessage::getMessageATransmettre(){
	return this->messageATransmettre;
}

int TraitementMessage::getTailleMessage(){
	return this->tailleMessage;
}

int TraitementMessage::getWinnersPoints(){
	return this->winnerPoints;
}
int* TraitementMessage::getPoints(){
	return this->points;
}
int TraitementMessage::getMinWords(){
	return this->minWords;
}
int TraitementMessage::getNbPlayers(){
	return this->players;
}

char* TraitementMessage::getIdGame(){
	return this->idGame;
}
