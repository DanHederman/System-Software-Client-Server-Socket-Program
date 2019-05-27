/**
 * 
 * Description: DT211C/4 System Software Assignment 2
 * 
 * Author: Dan Hederman
 * Student Number: C15410232
 * 
 * Date: 03/05/19
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
 
#define PORT 4444

// globals
int count = 0;
pthread_mutex_t lock;

char delimiter[] = "?";

//Handle Connections

void *connection_handler(void *socket_desc)
{
    //Variables for connection handler function
    pthread_mutex_lock(&lock);
    int socket = *(int*)socket_desc;
    int read_size;
    FILE *fp;
    char file_name[300];
    char client_message[2000];
    //Base path for saving files to server
    char base_path[200] = "/home/dan/Assignment2/ServerFiles/";
    int name_recieved = 0;
    int writing = 0;

    count += 1;
    printf("\n\nJob %d started\n\n", count);
    
    printf("Recieving filename from client\n");
    recv(socket, client_message, sizeof(client_message), 0);
    char testFileName[20];
    strcpy(testFileName, client_message);

    client_message[0] = 1;
    send(socket, client_message, sizeof(client_message), 0);
    bzero(client_message, sizeof(client_message));
    
    while((read_size = recv(socket, client_message, 2000, 0)) > 0)
    {
        char *ptr = strtok(client_message, delimiter);
    

        strcat(base_path, testFileName);

        fp = fopen(base_path, "w");
        
        if(fp != NULL)
        {
            fwrite(client_message, sizeof(char), read_size, fp);
            printf("\nSuccessfully transfered file\n");
            printf("\nClient Disconnecting\n");
        }
        else
        {
            perror("File Write");
        }

        fclose(fp);

        name_recieved = 1;
        write(socket, client_message, strlen(client_message));
        memset(client_message, 0, 2000);
        pthread_mutex_unlock(&lock);
    
    }// end while

    return NULL;
}

int main()
{
    pthread_t tid[count];
    int socket_desc, client_sock , c;
    struct sockaddr_in server, client;
     
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    printf("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
     
    //Bind
    if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Bind");
        return 1;
    }
     
    //Listen
    listen(socket_desc , 3);
    
    printf("\n\nServer running\n\n");
    printf("Listening for connections......\n\n");
    c = sizeof(struct sockaddr_in);
		pthread_t thread_id;

     if (pthread_mutex_init(&lock, NULL) != 0){

        printf("\n mutex init failed\n");
        return 1;
    }

    //Accept new connections
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        printf("\nNew connection accepted\n\n");
         
        if( pthread_create( &thread_id, NULL, connection_handler, (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
        
        printf("Handler assigned\n");
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}