//Client-side TCP Programming
#include <stdio.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> 
#include <netinet/in.h>

int main(int argc, char const **argv) 
{
	if(argc != 3){
		printf("Needs two arguments \n");
		return -1;
	}
	

	struct sockaddr_in remoteaddr;
	int clisock, servread, localread;
	char *test = "Hello, test from client";
	char buffer[1024] = {0};
	char buffer2[1024] = {0};

	int i = 2;

	if((clisock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("socket() error: \n");
		return -1;
	}

	char* LOCAL_ADDR = argv[1];
	char* SERVER_ADDR = argv[2];

	remoteaddr.sin_family = PF_INET;
	remoteaddr.sin_port = htons(10007);
	remoteaddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	if(connect(clisock, (struct sockaddr *) &remoteaddr, sizeof(remoteaddr)) < 0){
		perror("connect() error: \n");
		return -1;
	}


	servread = read(clisock, buffer, 1024);

	printf("%s: %s\n", SERVER_ADDR, buffer);
	close(clisock);

	remoteaddr.sin_family = PF_INET;
	remoteaddr.sin_port = htons(10007);
	remoteaddr.sin_addr.s_addr = inet_addr(LOCAL_ADDR);

	if((clisock = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){
		perror("socket() error: \n");
		return -1;
	}
	if(connect(clisock, (struct sockaddr *) &remoteaddr, sizeof(remoteaddr)) < 0){
		perror("connect() error: \n");
		return -1;
	}



	localread = read(clisock, buffer2, 1024);

	printf("localhost: %s\n", buffer2);
	close(clisock);
}

