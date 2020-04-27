

#include <stdio.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <time.h> 
#include <sys/signal.h>
#include <unistd.h> 
#include <stdlib.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 



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

if(read(server, message, 255)<0){ 
fprintf(stderr, "read() error\n");
exit(3);
}
if(strcmp(message,"You can now play")==0)
{
	fprintf(stderr, "Refree: You can now play\n");
	sleep(1);
	srand(time(NULL));   //used for seeding rand(), rand() would genreate same value is srand() is not used
	int num=rand()%10+1; //genrate radnom integer between 1 and 10
	fprintf(stderr, "Dice rolled %d\n\n\n",num);	
	write(server, &num, sizeof(num));  // send rolled dice to server

}
if(strcmp(message,"Game over: you won the game")==0)  // Enter if client has won
{
	printf("VICTORY\n");
	close(server);
	exit(0);
	
}

if(strcmp(message,"Game over: you lost the game")==0) //Enter if client has lost
{
	printf("LOST\n");
	close(server);
	exit(0);
}


}
}


