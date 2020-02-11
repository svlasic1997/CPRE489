
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){

	struct sockaddr_in serveraddr, clientaddr;
	int serversock, consock;
	int len = sizeof(clientaddr);
	char buffer[1024] = {0};
	int readVal;

	FILE *uptime;
	uptime = popen("uptime", "r");
		
	char* IP_ADDRESS = "192.168.254.11";

	if( (serversock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket() error:\n");
		exit(1);
	}

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(10007);
	serveraddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	if( (bind(serversock, (struct sockaddr *) &serveraddr, sizeof(serveraddr))) < 0){
		perror("bind() error:\n");
		exit(1);
	}

	
	if( listen(serversock, 10) < 0){
		perror("listen() error:\n");
		exit(1);
	}

	while(1){
	
		
		if( (consock = accept(serversock, (struct sockaddr *) &clientaddr, &len)) < 0){
			perror("accept() error:\n");
			exit(1);
		}
		
		fgets(buffer, 1024, uptime);
		write(consock, buffer, 1024);
		readVal = read(consock, buffer, 1024);
	
		close(consock);
	}

	close(serversock);
}
	 

