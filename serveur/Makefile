CC=g++
CFLAGS= -g -pthread -std=c++11 -I/opt/ssl/include/ -L/opt/ssl/lib/

OBJS= bin/Partie.o bin/Joueur.o bin/TraitementMessage.o bin/Ecoute.o bin/Connexion.o bin/Client.o bin/sha256.o bin/Serveur.o

.PHONY: clean

serveur: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o serveur
	
bin/Serveur.o: include/Serveur.h src/Serveur.cpp
	$(CC) $(CFLAGS) -c src/Serveur.cpp -o bin/Serveur.o 
	
#bin/GestionPartie.o: include/GestionPartie.h src/GestionPartie.cpp
#	$(CC) $(CFLAGS) -c src/GestionPartie.cpp -o bin/GestionPartie.o 
	
bin/sha256.o: include/sha256.h src/sha256.cpp
	$(CC) $(CFLAGS) -c src/sha256.cpp -o bin/sha256.o  
	
bin/Partie.o: include/Partie.h src/Partie.cpp
	$(CC) $(CFLAGS) -c src/Partie.cpp -o bin/Partie.o  
	
bin/Joueur.o: include/Joueur.h src/Joueur.cpp
	$(CC) $(CFLAGS) -c src/Joueur.cpp -o bin/Joueur.o 
	
bin/TraitementMessage.o: include/Partie.h include/TraitementMessage.h src/TraitementMessage.cpp
	$(CC) $(CFLAGS) -c src/TraitementMessage.cpp -o bin/TraitementMessage.o 
	
bin/Ecoute.o: include/Ecoute.h src/Ecoute.cpp
	$(CC) $(CFLAGS) -c src/Ecoute.cpp -o bin/Ecoute.o 
	
bin/Connexion.o: include/Connexion.h src/Connexion.cpp
	$(CC) $(CFLAGS) -c src/Connexion.cpp -o bin/Connexion.o 
	
bin/Client.o: include/Client.h src/Client.cpp
	$(CC) $(CFLAGS) -c src/Client.cpp -o bin/Client.o 

clean :
	@rm -f bin/*.o serveur
