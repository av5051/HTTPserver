#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    int server_fd = socket(AF_INET, SOCK_STREAM,0);
    if(server_fd==-1){
        perror("server failed to start");
        return 1;

    }
    printf("socket created: %d\n" , server_fd);

    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;


    if(bind(server_fd , (struct sockaddr*)&server_addr,sizeof(server_addr)) == -1){

        perror("bind failed");
        return 1;

    }
    printf("bind successful");


    return 0;
}


