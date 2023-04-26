#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void error(const char *msg){
    perror(msg);
    exit(1);
}
int main(int argc, char *argv[]){
    // we are taking port number as command line argument.
    if(argc<2){
        printf("Please provide port number.\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[255];
    struct sockaddr_in server_addr, client_addr; // server and client address
    socklen_t clilen;

    sockfd = socket(AF_INET,SOCK_STREAM, 0);
    if(sockfd<0){
        error("Error opening Socket.\n");
    }
    bzero((char *) &server_addr,sizeof(server_addr));
    portno = atoi(argv[1]); // extracting the port number.

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno);

    if(bind(sockfd,(struct sockaddr * ) &server_addr,sizeof(server_addr))<0){
        error("Error in port binding.");
    }
    listen(sockfd,5); // listen function
    clilen = sizeof(client_addr);

    newsockfd = accept(sockfd,(struct sockaddr *) &client_addr, &clilen); // accepting connection

    if(newsockfd<0){
        error("Error on accepting the connection.");
    }
    while (1){
        bzero(buffer,255); // clearing buffer
        n = read(newsockfd,buffer,255); // reading msg from client
        if(n<0){
            error("Error on reading.");
        }
        printf("Client: %s",buffer); // printing client message.

        bzero(buffer,255); // clearing buffer

        fgets(buffer,255,stdin); // asking client reply.

        n = write(newsockfd,buffer, strlen(buffer)); // writing msg to client

        if(n<0){
            error("Error on writing.");
        }

        if(strncmp("Bye",buffer,3) == 0){
            break;
        } // loop break

    }
    close(newsockfd);
    close(sockfd);



}

