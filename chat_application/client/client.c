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
    int sockfd, port, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
    if(argc<3){
        printf("Please provide port number.\n");
        exit(1);
    }
}