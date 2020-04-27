

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <sys/signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdlib.h>



void servicePlayers(int TOTO,int TITI){   
int dice1,dice2;

int total1=0,total2=0;


while(1){
	
write(TOTO, "You can now play" , strlen("You can now play")+1); //send  message to client
if(!read(TOTO, &dice1,sizeof(dice1))){   //read message from client
		close(TOTO);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
}
total1=total1+dice1;
fprintf(stderr,"TOTO rolled %d\n",dice1);
if(total1>=100)     
	{
		
		fprintf(stderr,"\n\nTOTO  has won\n");   
		write(TOTO, "Game over: you won the game" , strlen("Game over: you won the game")+1);  //send message to toto that it has won
		write(TITI, "Game over: you lost the game" , strlen("Game over: you lost the game")+1);	//send message to titi that it has lost
		close(TOTO); 
		close(TITI);
		exit(0);
	}
write(TITI, "You can now play" , strlen("You can now play")+1);
	if(!read(TITI, &dice2, sizeof(dice2))){
		close(TITI);
		fprintf(stderr,"Bye, client dead, wait for a new client\n");
		exit(0);
	}
	total2=total2+dice2;
	fprintf(stderr,"TITI rolled %d\n\n",dice2);
	fprintf(stderr,"TOTO's total is %d\n",total1);
	fprintf(stderr,"TITI's total is %d\n\n\n",total2);
	if(total2>=100)
	{
		
		fprintf(stderr,"\nTITI has won\n");
		write(TITI, "Game over: you won the game" , strlen("Game over: you won the game")+1); //send message to titi that it has won
		write(TOTO, "Game over: you lost the game" , strlen("Game over: you lost the game")+1);	//send message to toto that it has lost
		close(TOTO);
		close(TITI);
		exit(0);
	}

}
 
}

int main(int argc, char *argv[]){
int sd, client1, client2, portNumber;
socklen_t len;
struct sockaddr_in servAdd;
if(argc != 2){
printf("Call model: %s <Port #>\n", argv[0]);
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
listen(sd, 10);
while(1){
client1=accept(sd,(struct sockaddr*)NULL,NULL);
printf("Got client 1\n");

client2=accept(sd,(struct sockaddr*)NULL,NULL);
printf("Got client 2\n");
if(!fork())
servicePlayers(client1,client2);
close(client1);
close(client2);
}
}



