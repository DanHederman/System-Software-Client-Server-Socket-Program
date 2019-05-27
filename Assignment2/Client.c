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

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define PORT 4444

void snd_fname(int socket, void *buff, size_t len)
{
    char *ptr = (char*) buff;
    while(len > 0)
    {
        int i = send(socket, ptr, len, 0);
    
        if(i < 1)
            printf("Error\n");
    
        ptr += i;
        len -= i;
    }
}

int main(){

    int sfd = 0, n = 0, b;
    char rbuff[1024];
    char sendbuffer[100];
    char file[300];
    int server_path;
    char file_name[300];
    FILE *fp;

    //Names of the directorys that can be written to
    char root[] = "root/";
    char sales[] = "sales/";
    char promotions[] = "promotions/";
    char offers[] = "offers/";
    char marketing[] = "marketing/";

    struct sockaddr_in serverAddr;

    memset(rbuff, '0', sizeof(rbuff));
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    b = connect(sfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    if (b ==- 1) {
        perror("Connect");
        return 1;
    }

    printf("Please enter the file name\n");
    scanf("%s", file);

    //Run loop till valid option selected.
    do
        {
            printf("\nPlease enter the files destination\n1) root\n2) sales\n3) promotions\n4) offers\n5) marketing\n6) exit\n");

            scanf("%d", &server_path);

            switch(server_path)
            {
                case 1 :
                    strcat(root, file);
                    strcpy(file_name, root);
                    break;

                case 2 :
                    strcat(sales, file);
                    strcpy(file_name, sales);
                    break;

                case 3 :
                    strcat(promotions, file);
                    strcpy(file_name, promotions);
                    break;

                case 4 :
                    strcat(offers, file);
                    strcpy(file_name, offers);
                    break;

                case 5 :
                    strcat(marketing, file);
                    strcpy(file_name, marketing);
                    break;
                
                case 6 :
                    printf("Client terminated\n");
                    exit(1);

                default :
                    printf("Invalid option\n");
                    break;
            }
        } while ((server_path != 1) && (server_path != 2) && (server_path != 3) && (server_path != 4) && (server_path != 5) && (server_path != 6));

    fp = fopen(file, "r");
    if(fp == NULL){
        perror("File");
        return 2;
    }
    strcat(file, "?");

    strcpy(sendbuffer, file_name);
    send(sfd, sendbuffer, sizeof(sendbuffer), 0);
    bzero(sendbuffer, sizeof(sendbuffer));

    recv(sfd, sendbuffer,300, 0);
    printf("\nReceieved response from server\n");

    bzero(sendbuffer, sizeof(sendbuffer));

    while((b = fread(sendbuffer, sizeof(char), sizeof(sendbuffer), fp))>0 ){
        send(sfd, sendbuffer, b, 0);
        bzero(sendbuffer, sizeof(sendbuffer));
    }

    printf("File transfered\n");

    fclose(fp);
    return 0;
}