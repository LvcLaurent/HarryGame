#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>


int fd, fdClient;

void handler_close(){
	close(fdClient);
	close(fd);
}

int main(void){
	socklen_t sizeAccept;
	struct sockaddr addresseClient;
	signal(SIGINT, handler_close);
	if((fd = socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("problème d'initialisation socket");
		exit(1);
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1664);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(fd, (struct sockaddr*)& addr, sizeof(struct sockaddr_in))){
		perror("problème de liaison");
		exit(2);
	}
	if(listen(fd, 0)==-1){
		perror("problème lors de l'écoute");
		exit(3);
	}
	memset(&addresseClient, 0, sizeof(struct sockaddr));
	if((fdClient = accept(fd, &addresseClient, &sizeAccept )) ==-1){
		perror("problème lors de l'appel à accept");
		exit(4);
	}
	close(fdClient);
	close(fd);
}
