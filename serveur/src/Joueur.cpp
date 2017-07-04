
#include "../include/Joueur.h"

using namespace std;

Joueur::Joueur(char* l, char* pwd,int tailleL, int tailleP){
	cout << pwd << endl;
	this->login = (char*) malloc (sizeof(char) * tailleL+1);
	this->password = (char*) malloc (sizeof(char) * tailleP+1);
	strcpy(this->login,l);
	strcpy(this->password,pwd);
	this->createToken();
}

void Joueur::createToken(){
	struct tm Today;
	time_t maintenant;
	time(&maintenant);
	Today = *(localtime(&maintenant));
	this->token = (char*) malloc(sizeof(char)*11);
	sprintf(this->token,"%d%c%c%02u%02u%02u",Today.tm_wday,'c','t',Today.tm_hour, Today.tm_min, Today.tm_sec);
}



char* Joueur::getLogin(){
	return this->login;
}

char* Joueur::getPassword(){
	return this->password; 	
}

char* Joueur::getToken(){
	return this->token;
}
