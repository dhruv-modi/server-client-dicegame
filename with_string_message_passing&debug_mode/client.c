//Dhruv Modi 
//110009086
//14-April-2020
//client.c

#include <stdio.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/signal.h>
#include <unistd.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <time.h> 


int main(int argc, char *argv[]){
char message[255];

int server, portNumber;
long int ss = 0;
socklen_t len;
struct sockaddr_in servAdd;
if(argc != 3){
	printf("Call model:%s <IP> <Port#>\n",argv[0]);
	exit(0);
}
if((server = socket(AF_INET, SOCK_STREAM, 0))<0){
	fprintf(stderr, "Cannot create socket\n");
	exit(1);
}
servAdd.sin_family = AF_INET;
sscanf(argv[2], "%d", &portNumber);
servAdd.sin_port = htons((uint16_t)portNumber);
if(inet_pton(AF_INET,argv[1],&servAdd.sin_addr)<0){
	fprintf(stderr, " inet_pton() has failed\n");
	exit(2);
}


if(connect(server,(struct sockaddr *)&servAdd,sizeof(servAdd))<0){
	fprintf(stderr, "connect() has failed, exiting\n");
	exit(3);
}

while(1){

	if(read(server, message, 255)<0){  //READ THE MESSAGE FROM SERVER
		fprintf(stderr, "read() error\n");
		exit(3);
	}

	if(strcmp(message,"You can now play")==0) //ENTER IF SERVER IS ASKING TO PLAY THE DICE
	{
		fprintf(stderr, "Refree: You can now play\n"); 
		sleep(1);
		srand(time(NULL)); //SEED VALUE FOR rand()
		char numb[3]; 
		sprintf(numb,"%d",rand()%6+1); //STORE GENERATED RANDOM INTEGER TO STRING
		fprintf(stderr, "Obtained value is :- %s\n\n\n",numb);	
		write(server, numb, strlen(numb)+1);  //SEND THE ROLLED VALUE TO SERVER
	}	

	if(strcmp(message,"Game over: you won the game")==0) //ENTER IF SERVER DECALRES YOU THE WINNER
	{
		printf("I won the game\n");
		close(server);  //CLOSE CONNECTION
		exit(0);	
	}

	if(strcmp(message,"Game over: you lost the game")==0) //ENTER IF SERVER DECLARES YOU THE LOSER
	{
		printf("I lost the game\n");
		close(server); //CLOSE CONNECTION
		exit(0);
	}


}


}


