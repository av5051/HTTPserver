#include <stdio.h> // common c import
#include <stdlib.h> //standard library functions like write
#include <string.h> // string manipulation functions
#include <unistd.h>  // unix standard lib
#include <errno.h> // error handling

#include <sys/socket.h>  // creating and managing sockets
#include <netinet/in.h>  //human readable ip adresses to machine ones and vice versa
#include <arpa/inet.h> //

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

        perror("bind failed \n");
        return 1;

    }
    printf("bind successful \n");


    if(listen(server_fd,10) == -1){
        perror("listening to server requests failed some error mightve occured please try again \n");
        close(server_fd);
        return 1;
    }

    printf("listen worked \n");

    while(1){
        printf("waiting for new connection");
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);
        

        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr,&addr_size);

        if(client_fd == -1){
            perror("accept failed");
            continue;

        }
        printf("connected to a client");

        close(client_fd);
    }
    char buffer[1024];
    int bytes_recieved = recv(server_fd,buffer,sizeof(buffer)-1,0);
    if (bytes_recieved <0){
        perror("recieve failed");
    }
    else if(bytes_recieved ==0){
        printf(" \n client connected successfully\n");
    }
    else if (bytes_recieved >= 0){
        printf("\nrequest recieved succesfully\n");
        buffer[bytes_recieved] = '\0';
        printf(" \nthe request was %c \n", buffer);
    }

=
    return 0;

}




