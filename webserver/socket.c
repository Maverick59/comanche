#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>

int creer_serveur(int port){
    int socket_server;
    socket_server=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_server==-1){
        perror("socket_server");
        return -1;
    }
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(port);
    saddr.sin_addr.s_addr=INADDR_ANY;
    if(bind(socket_server, (struct sockaddr *)&saddr, sizeof(saddr))==-1){
        perror("bind socket_server");
        return -1;
    }
    if(listen(socket_server, 10)==-1){
        perror("listen socket_server");
        return -1;
    }
    return socket_server;
}