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

    close(server_fd);
    return 0;
}


