#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> 
#include <netinet/in.h>
int main(int argc, char const **argv) {
	struct sockaddr_in servaddr, cliaddr, forwardaddr;
	char buffer[2048];
	int sersock, clisock;
	int clilen = sizeof(cliaddr);
	int forwardlen = sizeof(forwardaddr);

	srand(time(NULL));

	if(argc!=6){
		perror("Missing parameters\n");
		return -1;
	}
	
	const char* listenerIP = argv[1];
	int listenerPort = atoi(argv[2]);
	const char* destinationIP = argv[3];
	int destinationPort = atoi(argv[4]);
	int packetLoss = atoi(argv[5]);

	printf("%s %d %s %d %d", listenerIP, listenerPort, destinationIP, destinationPort, packetLoss);
	
	if((sersock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket() error: \n");
		return -1;
	}
	
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(listenerPort);
	servaddr.sin_addr.s_addr = inet_addr(listenerIP);
	
	if((bind(sersock, (struct sockaddr*) &servaddr, sizeof(servaddr))) < 0){
		perror("bind() error: \n");
		return -1;
	}

	forwardaddr.sin_family = PF_INET;
	forwardaddr.sin_port = htons(destinationPort);
	forwardaddr.sin_addr.s_addr = inet_addr(destinationIP);
	
	int result; 
	while(1){
		result = recvfrom(sersock, buffer, 2048, 0, (struct sockaddr*)&cliaddr, &clilen);
		printf("Data received: %s\n", buffer);
		int r = rand() % 100 + 1;
		if(r > packetLoss){
			sendto(sersock, buffer, result, 0, (struct sockaddr*)&forwardaddr, forwardlen);
		}
	}
	close(sersock);
}
