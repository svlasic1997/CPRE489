#include <stdio.h> 
#include <string.h>    
#include <sys/socket.h>    
#include <stdlib.h>
#include "ccitt16.h"
#include "utilities.h"
#include "introduceerror.h"

void primary(int sockfd, double ber) {
	int readSize;
    char msg[DATA_LENGTH], srvReply[150];
	unsigned char packet[PACKET_SIZE];
	unsigned int packetNum = 0;
	int window[WINDOW_SIZE];
	char buffer[150];
	int flag = 0;
	int counter = 0;

	int i;
	for(i=0; i<WINDOW_SIZE; i++){
		window[i] = i;
	}
	
	for(i=0; i<150; i++){
		buffer[i] = 0;
	}

    //keep communicating with server
    while(1)
    {
		int start = window[0];
		if(start==13){
			printf("Total count: %d\n", counter);
			break;
		}
		int end = window[WINDOW_SIZE-1];

		for(i=start; i<=end; i++){
			if(i==13)
				break;
			if(buffer[DATA_LENGTH*i]==0){
				fgets(msg, DATA_LENGTH+1, stdin);
				buildPacket(packet, DATA_PACKET, msg, i);
				IntroduceError(packet, ber);
				buffer[i*DATA_LENGTH] = msg[0];
				buffer[(i*DATA_LENGTH) + 1] = msg[1];
				printf("Buffer[%d]: %2s\n", i, buffer + (DATA_LENGTH*i));
			}else{
				buildPacket(packet, DATA_PACKET, buffer + (DATA_LENGTH*i), i);
				IntroduceError(packet, ber);
			}
			
			if( send(sockfd , packet, PACKET_SIZE, 0) < 0)
					perror("Send failed");
				else{
					counter++;
					printf("Sending message: %.2s\n", buffer + (DATA_LENGTH*i));
				}
		}
				
		for(i=start, flag=0; i<=end; i++){
			if(i==13)
				break;
			readSize = recv(sockfd , packet , PACKET_SIZE , 0);
			if(flag==1)
				continue;
			if(readSize < 0)
				perror("recv failed");
			else{
				if(packet[0]==ACK_PACKET){
					shiftWindow(window, WINDOW_SIZE, packet[1]-i);
					printf("ACK(%d)\n", packet[1]);
					printf("Shift amount: %d\n", packet[1]-i);
				}else if(packet[0]==NAK_PACKET){
					//shiftWindow(window, WINDOW_SIZE, packet[1]-i);
					printf("NAK(%d)\n", packet[1]);
					flag = 1;
				}
			}
		}
    }
  
}

