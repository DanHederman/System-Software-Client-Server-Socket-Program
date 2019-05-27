All: Client Server

Client: Client.o 
	gcc -o Client Client.o -lrt

Server: Server.o 
	gcc -o Server Server.o -lrt -pthread

Client.o: Client.c Server.o Client.o 
	gcc -c Client.c

Server.o: Server.c Server.o Client.o 
	gcc -c Server.c

Clean:
	rm Server.o Client.o