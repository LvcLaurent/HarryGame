#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fstream>
#include <stdio.h>

#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../lib/rapidjson/include/rapidjson/document.h"         // rapidjson's DOM-style API
#include "../lib/rapidjson/include/rapidjson/prettywriter.h"     // for stringify JSON
#include "../lib/rapidjson/include/rapidjson/filestream.h"       // wrapper of C stream for prettywriter as output
#include "../lib/rapidjson/include/rapidjson/reader.h"
#include "../include/Partie.h"

#define CER 7
#define QUE 4

const char * Cercle[] = {"AG E U BL","GEN M BER GRI ","PO AM U LE","OI R MI R","GE TA HE RI","M E PI RE","TU VO I RE"}; 

const char * reponseCer[] = {"BLAGUE","GRIMBERGEN","AMPOULE","MIROIR","HERITAGE","EMPIRE","VOITURE"};

const char * tabIndice[] = {"Drole d'histoire","J'ai soif","Lumiere","Pour voir la bete","Testamement",
							"Napoleon","Transport"};

const char * question[] = {"Qui est Don Diego ?", "Quelle Jour on est ?", "Quelle moi on est ?", "Qui chasse les vampires ?"}; 
  
const char * reponseQue[] = {"ZORRO", "MERCREDI", "DECEMBRE", "BUFFY"};

const char * cercleQue[] = {"ZO O R R","DI E CR MER","RE B CEM DE","Y FF B U"}; 

using namespace std;

Partie::Partie(char* id ,int nbJoueurMax,char* createur,int minWord,int* points,int winnersPoints,Joueur * jou){
	/* 0 : Partie Non commencé et Non pleine
	 * 1 : Partie Non commencé mais pleine in progress
	 * 2 : Partie commencé phase 1
	 * 3 : Partie phase 1 terminé en attente de la phase 2
	 * 4 : Partie commencé phase 2
	 * */
	this->mutex = (int*) malloc (sizeof(int));
	(*this->mutex) = 0;
	this->partieCreer = (int*) malloc(sizeof(int));
	*this->partieCreer = 0;
	this->etat = 0;
	this->inProgress = 5;
	this->indice = 0;
	this->nbReponse=(int*) malloc (sizeof(int));
	(*this->nbReponse)=0;
	int i,j;
	this->createur = (char*) malloc(sizeof(char)*strlen(createur)+1);
	strcpy(this->createur,createur);
	this->id = (char*) malloc(sizeof(char)*(4 +2 +2 +2));
	sprintf(this->id,"%s",id);
	cout << id << endl ;
	this->minWords = minWord;
	this->proprio = jou;
	i=*points;
	this->points = (int*) malloc(sizeof(int) * i);
	for(j=0;j<i;j++)this->points[j] = points[j];
	this->nbJoueurMax = (int*) malloc(sizeof(int));
	(*this->nbJoueurMax) = nbJoueurMax;
	this->nbJoueur = (int*) malloc(sizeof(int));
	*this->nbJoueur = 1;
	this->winnersPoints = winnersPoints;
	this->listeJoueur = (char**) malloc (sizeof(char*) * nbJoueurMax);
	(*this->listeJoueur) = (char*) malloc(sizeof(char) * strlen(this->proprio->getLogin()) +1);
	strcpy((*this->listeJoueur),this->proprio->getLogin());
	*this->partieCreer = 1;
	this->enregistrerDonnee();
}

char* Partie::envoiInformation(){
	int i,c;
	while((*this->mutex) == 1 );
	char* buffer = (char*) malloc(sizeof(char)*(15 +28 +14+22+ 14+2048));
	sprintf(buffer,"{\"id-game\":\"%s\",",this->id);
	if((this->etat == 2) || (this->etat == 3))
		sprintf(buffer,"%s\"phase\":1,",buffer);
	if(this->etat== 3)
		sprintf(buffer,"%s\"qualified\":[\"%s\",\"%s\"],",buffer,this->tabGagnant[0],this->tabGagnant[1]);
	if((this->etat>=4) && (this->etat<=5)){
		sprintf(buffer,"%s\"phase\":2,",buffer);
		sprintf(buffer,"%s\"question\":\"%s\",",buffer,this->questionPhase2);
	}
	if((this->etat == 0) || (this->etat == 1)){
		c=this->getNbJoueurMax()-
		(*(this->nbJoueur));
		sprintf(buffer,"%s\"#players\":%d,",buffer,*this->nbJoueurMax);
		sprintf(buffer,"%s\"available-seats\":%d,",buffer,c);
	}
	if(this->etat == 3){
		sprintf(buffer,"%s\"total-points\":{\"",buffer);
		for(i=0;i<(*this->nbJoueur);i++){
			if(i<(*this->nbJoueur)-1)
				if(this->tabPoint[i]==0)
					sprintf(buffer,"%s%s\":null,\"",buffer,this->listeJoueur[i]);
				else
					sprintf(buffer,"%s%s\":%d,\"",buffer,this->listeJoueur[i],this->tabPoint[i]);
			else
				if(this->tabPoint[i]==0)
					sprintf(buffer,"%s%s\":null},",buffer,this->listeJoueur[i]);
				else
					sprintf(buffer,"%s%s\":%d},",buffer,this->listeJoueur[i],this->tabPoint[i]);
		}
	}
	if(!this->etat)
		sprintf(buffer,"%s\"status\":\"open\",\"creator\":\"%s\",",buffer,this->proprio->getLogin());
	else if (this->etat == 1)
		sprintf(buffer,"%s\"status\":\"in-progress\",\"creator\":\"%s\",",buffer,this->proprio->getLogin());
	if(this->etat==1)
		sprintf(buffer,"%s\"start-in\":%d,",buffer,this->inProgress);
	if((this->etat == 0) || (this->etat == 1)){
		sprintf(buffer,"%s\"players\":[\"",buffer);
		for(i=0;i<(*this->nbJoueur);i++)
			if(i<(*this->nbJoueur)-1)
				sprintf(buffer,"%s%s\",\"",buffer,this->listeJoueur[i]);
			else
				sprintf(buffer,"%s%s\"]}",buffer,this->listeJoueur[i]);
	}
	if(this->indice && this->etat == 2){
		sprintf(buffer,"%s\"clue\":\"%s\",",buffer,tabIndice[this->cercle]);
	}
	if((((this->etat == 2)) && ((this->inProgress) || (this->ici == 2)))){
		sprintf(buffer,"%s\"propositions\":{\"",buffer);
		for(i=0;i<(*this->nbJoueur);i++){
			if(i<((*this->nbJoueur)-1))
				if(this->tableauReponse[i])
					sprintf(buffer,"%s%s\":\"%s\",\"",buffer,this->listeJoueur[i],this->tableauReponse[i]);
				else
					sprintf(buffer,"%s%s\":null,\"",buffer,this->listeJoueur[i]);
			else
				if(this->tableauReponse[i])
					sprintf(buffer,"%s%s\":\"%s\"},",buffer,this->listeJoueur[i],this->tableauReponse[i]);
				else
					sprintf(buffer,"%s%s\":null},",buffer,this->listeJoueur[i]);		
		}
	}
	if((this->etat>=4) && (this->etat<=5)){
		sprintf(buffer,"%s\"circles\":[",buffer);
		for(i=0;i<this->indice;i++){
			if(i!=this->indice - 1)
				sprintf(buffer,"%s\"%s\",",buffer,this->phase2[i]);
			else
				sprintf(buffer,"%s\"%s\"",buffer,this->phase2[i]);
		}
		sprintf(buffer,"%s],",buffer);
		sprintf(buffer,"%s\"propositions\":{\"",buffer);
		for(i=0;i<2;i++){
			if(i<(2-1))
				if(this->tableauReponse2[i])
					sprintf(buffer,"%s%s\":\"%s\",\"",buffer,this->tabGagnant[i],this->tableauReponse2[i]);
				else
					sprintf(buffer,"%s%s\":null,\"",buffer,this->tabGagnant[i]);
					
			else
				if(this->tableauReponse2[i])
					sprintf(buffer,"%s%s\":\"%s\"},",buffer,this->tabGagnant[i],this->tableauReponse2[i]);
				else
					sprintf(buffer,"%s%s\":null},",buffer,this->tabGagnant[i]);
		}
		
		if((this->inProgress || (this->etat == 5)) || ((this->inProgress) || (this->ici ==2))){
			sprintf(buffer,"%s\"points\":{\"",buffer);
			for(i=0;i<2;i++){
				if(i<(2-1))
					if(this->tabPointPhase2[i]==0)
						sprintf(buffer,"%s%s\":0,\"",buffer,this->tabGagnant[i]);
					else
						sprintf(buffer,"%s%s\":%d,\"",buffer,this->tabGagnant[i],this->tabPointPhase2[i]);
				else
					if(this->tabPointPhase2[i]==0)
						sprintf(buffer,"%s%s\":0},",buffer,this->tabGagnant[i]);
					else
						sprintf(buffer,"%s%s\":%d},",buffer,this->tabGagnant[i],this->tabPointPhase2[i]);
			}
			if(this->etat == 4){
				sprintf(buffer,"%s\"good-answer\":\"%s\",",buffer,this->reponse);
				sprintf(buffer,"%s\"start-next-word\":%d}",buffer,this->inProgress);
			}
		}
		if(this->etat == 5){
			sprintf(buffer,"%s\"good-answer\":\"%s\",",buffer,this->reponse);
			sprintf(buffer,"%s\"time-left\":0,",buffer);
			sprintf(buffer,"%s\"closing-time\":%d}",buffer,this->closing);
		}
		
		if((this->timeLeft) || (this->ici == 1)){
			sprintf(buffer,"%s\"time-left\":%d}",buffer,this->timeLeft);
		}
	}
	
	if(this->etat==2){
		sprintf(buffer,"%s\"circles\":[\"",buffer);
		for(i=0;i<4;i++){
			if(i<3)
				sprintf(buffer,"%s%s\",\"",buffer,this->phase1[i]);
			else
				sprintf(buffer,"%s%s\"],",buffer,this->phase1[i]);
		}
		sprintf(buffer,"%s\"points\":{\"",buffer);
		for(i=0;i<(*this->nbJoueur);i++){
			if(i<(*this->nbJoueur)-1)
				if(this->tabPointPhase1[i]==0)
					sprintf(buffer,"%s%s\":null,\"",buffer,this->listeJoueur[i]);
				else
					sprintf(buffer,"%s%s\":%d,\"",buffer,this->listeJoueur[i],this->tabPointPhase1[i]);
			else
				if(this->tabPointPhase1[i]==0)
					sprintf(buffer,"%s%s\":null},",buffer,this->listeJoueur[i]);
				else
					sprintf(buffer,"%s%s\":%d},",buffer,this->listeJoueur[i],this->tabPointPhase1[i]);
		}
		if((this->inProgress) || (this->ici == 2)){
			if(this->etat == 2){
				sprintf(buffer,"%s\"good-answer\":\"%s\",",buffer,this->reponse);
				sprintf(buffer,"%s\"start-next-word\":%d}",buffer,this->inProgress);
			}
		}
		if((this->timeLeft) || (this->ici == 1)){
			sprintf(buffer,"%s\"time-left\":%d}",buffer,this->timeLeft);
		}
	}
	if(this->etat == 3){
		sprintf(buffer,"%s\"start-next-phase\":%d}",buffer,this->inProgress);
	}
	
	if(this->etat == 6){
		sprintf(buffer,"%s\"state\":\"closed\",",buffer);
		sprintf(buffer,"%s\"ranking\":{\"",buffer);
		for(i=0;i<(*this->nbJoueur);i++){
			if(i<((*this->nbJoueur)-1))
				sprintf(buffer,"%s%s\":%d,\"",buffer,this->listeJoueur[i],i);
			else
				sprintf(buffer,"%s%s\":%d}}",buffer,this->listeJoueur[i],i);	
		}
	}
	return buffer;
}

void Partie::enregistrerProposition(char* proposition,char* login){
	int i;
	if(this->etat<3){
		for(i=0;i<(*this->nbJoueur);i++){
			if(!strcmp(this->listeJoueur[i],login))
				break;
		}
		cout << i << endl;
		this->tableauReponse[i] = (char*) malloc (sizeof(char)*strlen(proposition));
		sprintf(this->tableauReponse[i],"%s",proposition);
		(*this->nbReponse)++;
		if(!strcasecmp(proposition,this->reponse))
			this->tabPointPhase1[i]=this->points[1+(*this->nbReponseBonne)++];
	}
	else{
		for(i=0;i<2;i++){
			if(!strcmp(this->listeJoueur[i],login))
				break;
		}
		cout << i << endl;
		this->tableauReponse2[i] = (char*) malloc (sizeof(char)*strlen(proposition));
		sprintf(this->tableauReponse2[i],"%s",proposition);
		(*this->nbReponse)++;
		if(!strcasecmp(proposition,this->reponse))
			this->tabPointPhase2[i]+=1;
	}
}

int Partie::inscriptionJoueur(Joueur* j){
	//cout << j->getLogin() << endl;
	if((*this->nbJoueur)<(*this->nbJoueurMax)){
		this->listeJoueur[(*this->nbJoueur)] = (char*) malloc(sizeof(char)*(strlen(j->getLogin())+1));
		sprintf(this->listeJoueur[(*this->nbJoueur)],"%s",j->getLogin());
		(*this->nbJoueur)++;
	}
	else return 1;
	return 0;
}

void Partie::enregistrerDonnee(){
	
}

void Partie::imprimPartie(){
	cout << this->id << endl;
	cout << this->createur << endl;
}

void Partie::creationTableau(){
	int i;
	this->tableauReponse = (char**) malloc(sizeof(char*)*(*this->nbJoueur));
	this->tableauReponse2 = (char**) malloc(sizeof(char*)*2);
	this->tabPointPhase1 = (int*) malloc(sizeof(int)*(*this->nbJoueurMax));
	this->tabPointPhase2 = (int*) malloc(sizeof(int)*2);
	this->tabPoint = (int*) malloc(sizeof(int)*(*this->nbJoueur));
	this->nbReponseBonne = (int*) malloc(sizeof(int));
	for(i=0;i<(*this->nbJoueur);i++) {
		this->tabPoint[i] = 0;
		this->tabPointPhase1[i] = 0;
	}
	for(i=0;i<2;i++) {
		this->tabPointPhase2[i] = 0;
	}
}

void Partie::start(){
	int cercle,i,j,k;
	this->ici =0 ;
	while(*this->nbJoueurMax-*this->nbJoueur){
		sleep(2);
	}
	this->etat = 1;
	srand (time(NULL));
	cout << envoiInformation() << endl;
	this->creationTableau();
	this->timeLeft = 0;
	printf("La partie se lance : %d mot\n",this->minWords);
	this->gagnantPhase1 = 0;
	this->inProgress = 5;
	// ================================= PHASE 1 ====================================
	while(this->inProgress){
		this->inProgress--;
		sleep(1);
		cout << envoiInformation() << endl;
		if(this->inProgress == 0 ) (*this->mutex) = 1;
	}
	while(((this->minWords)>0) && (!this->gagnantPhase1)){
		this->minWords--;
		this->nbReponse = NULL;
		this->nbReponse = (int*) malloc(sizeof(int));
		(*this->nbReponse) = 0;
		this->indice=0;
		this->cercle = rand()%CER;
		this->phase1 = NULL;
		this->reponse = NULL;
		this->phase1=(char**) realloc(this->phase1,sizeof(char*)*4);
		this->phase1[0] = NULL;
		//this->phase1=(char**) realloc(this->phase1,sizeof(char*)*4);
		for(i=0,j=0,k=0;i<strlen(Cercle[this->cercle]);i++){
			if(Cercle[this->cercle][i] == ' '){
				j++;
				k=0;
				this->phase1[j] = NULL;
			}
			else{
				this->phase1[j] = (char*) realloc(this->phase1[j],sizeof(char)*(k+2));
				this->phase1[j][k+1] = '\0';
				this->phase1[j][k] = Cercle[this->cercle][i];
				k++;
			}
		}
		this->reponse = (char*) realloc(this->reponse,sizeof(char)*((int)strlen(reponseCer[this->cercle])+1));
		sprintf(this->reponse,"%s",reponseCer[this->cercle]);
		this->reponse[strlen(reponseCer[this->cercle])] = '\0';
		this->timeLeft = 7;
		this->etat = 2;
		this->ici = 1;
		(*this->mutex) = 0;
		while(this->timeLeft){
			this->timeLeft--;
			sleep(1);
			if(this->timeLeft<=4) 
				this->indice = 1;
			cout << this->envoiInformation() << endl;
			if(this->timeLeft == 0){this->ici=0; (*this->mutex) = 1;}
		}
		for(i=0;i<4;i++){
			for(j=0;j<strlen(this->phase1[i]);j++)
				cout << phase1[i][j];
			cout << endl;	
		}
		cout << this->reponse << endl;
		if(this->minWords<=0) this->verifGagnant();
		if(!gagnantPhase1){
			cout << "mot suivant" <<  endl;
			this->inProgress = 5;
			(*this->mutex) = 0;
		}
		else {
			this->inProgress = 5;
			(*this->mutex) = 0;
		}
		this->ici = 2;
		while(this->inProgress){
			sleep(1); 
			this->inProgress--;
			cout << this->envoiInformation() << endl;
			if(this->inProgress == 0) {this->ici =0;(*this->mutex) = 1;}
		}
		
		
		this->distributionPoints();
		free(this->nbReponse);
		free(this->reponse);
		free(this->phase1);
		for(i=0;i<4;i++){
			free(this->phase1[i]);
		}
	}
	this->etat = 3;
	this->gagnantPhase2 = 0;
	/*this->inProgress = 5;
	(*this->mutex) = 0;
	while(this->inProgress){
		sleep(1); 
		this->inProgress--;
		cout << this->envoiInformation() << endl;
		if(this->inProgress == 0) (*this->mutex) = 1;
	}*/
	cout << "phase Suivante" << endl ;
	// ==============================   PHASE 2 ========================================//
	while(!gagnantPhase2){
		this->nbReponse = NULL;
		this->nbReponse = (int*) malloc(sizeof(int));
		(*this->nbReponse) = 0;
		this->indice=0;
		this->cercle = rand()%QUE;
		this->phase2 = NULL;
		this->reponse = NULL;
		this->phase2=(char**) realloc(this->phase2,sizeof(char*)*4);
		this->phase2[0] = NULL;
		for(i=0,j=0,k=0;i<strlen(cercleQue[this->cercle]);i++){
			if(cercleQue[this->cercle][i] == ' '){
				j++;
				k=0;
				this->phase2[j] = NULL;
			}
			else{
				this->phase2[j] = (char*) realloc(this->phase2[j],sizeof(char)*(k+2));
				this->phase2[j][k+1] = '\0';
				this->phase2[j][k] = cercleQue[this->cercle][i];
				k++;
			}
		}
		this->reponse = (char*) realloc(this->reponse,sizeof(char)*(strlen(reponseQue[this->cercle]))+1);
		sprintf(this->reponse,"%s",reponseQue[this->cercle]);
		this->reponse[strlen(reponseQue[this->cercle])] = '\0';
		this->questionPhase2 = (char*) realloc(questionPhase2,sizeof(char)*(strlen(question[this->cercle])+1));
		sprintf(this->questionPhase2,"%s",question[this->cercle]);
		this->questionPhase2[strlen(question[this->cercle])] = '\0';
		this->timeLeft = 20;
		this->etat = 4;
		this->ici = 1;
		(*this->mutex) = 0;
		while(this->timeLeft){
			this->timeLeft--;
			sleep(1);
			if(this->timeLeft==15) this->indice = 1;
			if(this->timeLeft==12) this->indice = 2;
			if(this->timeLeft==9) this->indice = 3;
			if(this->timeLeft==4) this->indice = 4;
			cout << this->envoiInformation() << endl;
			if(this->timeLeft == 0){this->ici = 0; (*this->mutex) = 1;}
		}
		for(i=0;i<4;i++){
			for(j=0;j<strlen(this->phase2[i]);j++)
				cout << phase2[i][j];
			cout << endl;	
		}
		this->inProgress = 5;
		cout << this->reponse << endl;
		cout << this->questionPhase2 << endl;
		this->ici=2;
		(*this->mutex) = 0;
		while(this->inProgress){
			sleep(1); 
			this->inProgress--;
			cout << this->envoiInformation() << endl;
			if(this->inProgress == 0){this->ici=0; (*this->mutex) = 1;} 
		}
		cout << "Question Suivante" <<  endl;
		this->verifGagnant2();
		if(!this->gagnantPhase2){
			free(this->nbReponse);
			free(this->questionPhase2);
			free(this->reponse);
			free(this->phase2);
		}
		else this->etat = 5;
	}
	this->closing = 5;
	(*this->mutex) = 0;
	cout << "Partie Terminée"<< endl ;
	while(this->closing){
		sleep(1); 
		this->closing--;
		cout << this->envoiInformation() << endl;
		if(this->closing == 1){cout << this->envoiInformation() << endl;}
	}
	this->etat = 6 ;
	cout << this->envoiInformation() << endl;
	sleep(3600);
}

void Partie::verifGagnant2(){
	this->gagnantPhase2 = 1;
	int i,cpt=0;
	for(i=0;i<2;i++) {
		if(this->tabPointPhase2[i] > this->winnersPoints) {
			cpt++;
			this->gagnantPhase2 = 1;
		}
	}
	if (cpt==2){
		this->gagnantPhase2 = 0;
		if((this->tabPointPhase2[1] > this->tabPointPhase2[0]) || (this->tabPointPhase2[1] < this->tabPointPhase2[0]))
			this->gagnantPhase2 = 0;
			cout << "ici2" << endl ; 
	}
}

void Partie::verifGagnant(){
	this->tabGagnant = (char**)malloc (sizeof(char*)*2);
	int i,max=0,max1=0,cpt=0,x,y;
	for(i=0;i<(*this->nbJoueur);i++) {
		if(max<this->tabPoint[i]) max =this->tabPoint[i];
	}
	for(i=0;i<(*this->nbJoueur);i++) {
		if((max!=this->tabPoint[i]) && (max1<this->tabPoint[i])) max1 =this->tabPoint[i];
	}
	for(i=0;i<(*this->nbJoueur);i++) {
		if(max==this->tabPoint[i]) {
			cpt++;
			if(cpt == 1) x = i;
			else y = i;
			}
	}
	if (cpt==2){
		this->tabGagnant[0] = (char*) malloc(sizeof(char)*strlen(this->listeJoueur[x]));
		this->tabGagnant[1] = (char*) malloc(sizeof(char)*strlen(this->listeJoueur[y]));
		sprintf(this->tabGagnant[1],"%s",this->listeJoueur[x]);
		sprintf(this->tabGagnant[0],"%s",this->listeJoueur[y]);
		this->gagnantPhase1 = 1;
	}
	for(i=0;i<(*this->nbJoueur);i++) {
		if(max1==this->tabPoint[i]) {
			cpt++;
			y = i;
		}
	}
	if (cpt==2){
		this->tabGagnant[0] = (char*) malloc(sizeof(char)*strlen(this->listeJoueur[x]));
		this->tabGagnant[1] = (char*) malloc(sizeof(char)*strlen(this->listeJoueur[y]));
		sprintf(this->tabGagnant[1],"%s",this->listeJoueur[x]);
		sprintf(this->tabGagnant[0],"%s",this->listeJoueur[y]);
		this->gagnantPhase1 = 1;
	}
	
}

void Partie::distributionPoints(){
	int i;
	for(i=0;i<(*this->nbJoueur);i++) {
		this->tabPoint[i] += this->tabPointPhase1[i];
		this->tabPointPhase2[i] = 0;
	}
}

int Partie::getNbJoueurMax(){
	return (*this->nbJoueurMax);
}

char* Partie::getId(){
	return this->id;
}

int Partie::getEtat(){
	return this->etat;
}

int Partie::getNbJoueur(){
	return *this->nbJoueur;
}

char* Partie::getCreateur(){
	return this->createur;
}

int Partie::getMinWords(){
	return this->minWords;
}

int* Partie::getPoints(){
	return this->points;
}

int Partie::getPartieCreer(){
	return *this->partieCreer;
}

int Partie::getWinnersPoints(){
	return this->winnersPoints;
}

char** Partie::getTabJoueur(){
	return this->listeJoueur;
}
