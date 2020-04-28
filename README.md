# server-client-dicegame
USAGE:-

------------------------------------------------------------------

SERVER:

OutputFile PORT //For program passing integer message

OutputFile PORT DebugFlag //For program passing string message

DebugFlag=0 if you don't want to see anything on the screen

CLIENT:

OutputFile IP PORT

i.e. For local host use 127.0.0.1



PROGRAM OVERVIEW:-

------------------------------------------------------------------

A client and a server program, to implement a simple online game. 
The server process and the client process runs on two different machines and the communication
between the two processes is achieved using Sockets.
The server goes into an infinite loop to wait for the clients. When the server gets a client, it waits for another client (two players are needed).
When the server gets the other client (now two clients), it forks and, let the child process
take care of these two clients (players) in a separate function, called servicePlayers,
while the parent process goes back to wait for the next two clients (players).
