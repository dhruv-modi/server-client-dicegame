//Dhruv Modi 
//110009086
//14-April-2020
//server.c

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/signal.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 


void servicePlayers(int TOTO,int TITI, int zs){   //function called when child process of server is created
char m1[255],m2[255];  //variables to store the value of dice 
int exi=0;
int p1=0,p2=0;	//p1= total of toto, p2= total of titi
if(zs==0)   //Display nothing on server
{
 while(exi==0){
	
	write(TOTO, "You can now play" , strlen("You can now play")+1);  //send message to client 1 for rolling the dice
	if(!read(TOTO, m1, 255)){  //read the responded dice value from the client
		close(TOTO);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
	}
	p1=p1+atoi(m1);  //add the dice value to the total value

	if(p1>=100)   //if the total value of client 1 is 100 close all the connections announcing client 1 the winner 
	{
		write(TOTO, "Game over: you won the game" , strlen("Game over: you won the game")+1); //announce client 1 winner
		write(TITI, "Game over: you lost the game" , strlen("Game over: you lost the game")+1); //announce client 2 loser
		close(TOTO); //close connection
		close(TITI); //close connection
		exit(0);  
	}
	
	write(TITI, "You can now play" , strlen("You can now play")+1); //send message to client 2 for rolling the dice
	if(!read(TITI, m2, 255)){ //read the responded dice value from the client
		close(TITI);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
	}
	p2=p2+atoi(m2);	//add the dice value to the total value

	if(p2>=100)//if the total value of client 2 is 100 close all the connections announcing client 2 the winner
	{
		write(TITI, "Game over: you won the game" , strlen("Game over: you won the game")+1); //announce client 2 winner
		write(TOTO, "Game over: you lost the game" , strlen("Game over: you lost the game")+1); //announce client 1 loser
		close(TOTO); //close connection
		close(TITI); //close connection
		exit(0);
	}
	

}	
}
else	//Display everything on server
{

while(exi==0){
	
	write(TOTO, "You can now play" , strlen("You can now play")+1);  //send message to client 1 for rolling the dice
	if(!read(TOTO, m1, 255)){	//read the responded dice value from the client
		close(TOTO);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
	}
	p1=p1+atoi(m1);	//add the dice value to the total value

	
	fprintf(stderr,"TOTO got %s\n",m1);
	if(p1>=100)	//if the total value of client 1 is 100 close all the connections announcing client 1 the winner
	{
		
		fprintf(stderr,"-------------------------------\nTOTO WON\n-----------------------------");
		write(TOTO, "Game over: you won the game" , strlen("Game over: you won the game")+1);
		write(TITI, "Game over: you lost the game" , strlen("Game over: you lost the game")+1);
		close(TOTO);
		close(TITI);
		exit(0);
	}
	
	write(TITI, "You can now play" , strlen("You can now play")+1); //send message to client 2 for rolling the dice
	if(!read(TITI, m2, 255)){	//read the responded dice value from the client
		close(TITI);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
	}
	p2=p2+atoi(m2);	//add the dice value to the total value

	
	fprintf(stderr,"TITI got %s\n\n",m2);
	fprintf(stderr,"TOTO= %d\n",p1);
	fprintf(stderr,"TITI= %d\n\n------------------------\n",p2);

	if(p2>=100)	//if the total value of client 2 is 100 close all the connections announcing client 2 the winner
	{
		
		fprintf(stderr,"-------------------------------\nTITI WON\n-----------------------------");
		write(TITI, "Game over: you won the game" , strlen("Game over: you won the game")+1);
		write(TOTO, "Game over: you lost the game" , strlen("Game over: you lost the game")+1);
		close(TOTO);
		close(TITI);
		exit(0);
	}
	

}
}
}

int main(int argc, char *argv[]){
int sd, client1, client2, portNumber;
socklen_t len;
struct sockaddr_in servAdd;
if(argc != 3){ //check if the command is written in proper format
	printf("Call model: %s <Port #>  <visiblity>\n", argv[0]);
	exit(0);
}
if ((sd=socket(AF_INET,SOCK_STREAM,0))<0){
	fprintf(stderr, "Cannot create socket\n");
	exit(1);
}
servAdd.sin_family = AF_INET;
servAdd.sin_addr.s_addr = htonl(INADDR_ANY);
sscanf(argv[1], "%d", &portNumber);
servAdd.sin_port = htons((uint16_t)portNumber);
bind(sd,(struct sockaddr*)&servAdd,sizeof(servAdd));
listen(sd, 5);
while(1){
	printf("Waiting for players to connect");
	client1=accept(sd,(struct sockaddr*)NULL,NULL);
	printf("Got TOTO\n");

	client2=accept(sd,(struct sockaddr*)NULL,NULL);
	printf("Got TITI\n");
	if(!fork())  //CREATE CHILD PROCESS
	{
		servicePlayers(client1,client2,atoi(argv[2]));
	}
	close(client1);
	close(client2);
}
}



