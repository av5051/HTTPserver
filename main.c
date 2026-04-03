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

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_size = sizeof(client_addr);
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
        
        if (client_fd == -1) {
            continue;
        }

        char buffer[2048] = {0};
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received <= 0) {
            close(client_fd);
            continue;
        }

        buffer[bytes_received] = '\0';

        char method[10], path[255], protocol[20];
        sscanf(buffer, "%s %s %s", method, path, protocol);

        char *status_line;
        char *response_body;

        if (strcmp(path, "/") == 0 || strcmp(path, "/index.html") == 0) {
            status_line = "HTTP/1.1 200 OK";
            response_body = "<html><body><h1>Welcome Home!</h1><p>Arpit's Server is running.</p></body></html>";
        } else if (strcmp(path, "/about") == 0) {
            status_line = "HTTP/1.1 200 OK";
            response_body = "<html><body><h1>About Page</h1><p>First-year engineering project.</p></body></html>";
        } else {
            status_line = "HTTP/1.1 404 Not Found";
            response_body = "<html><body><h1>404</h1><p>Page not found!</p></body></html>";
        }

        char response_full[4096];
        int response_len = sprintf(response_full,
            "%s\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %ld\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            status_line, strlen(response_body), response_body);

        int total_sent = 0;
        int bytes_left = response_len;
        while (total_sent < response_len) {
            int n = send(client_fd, response_full + total_sent, bytes_left, 0);
            if (n == -1) {
                break;
            }
            total_sent += n;
            bytes_left -= n;
        }

        close(client_fd);
}
  


    return 0;

}




