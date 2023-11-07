#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>// Provides access to the POSIX operation system API
#include <arpa/inet.h> //Contains definitions for internet operations like network address translation
#include <sys/socket.h> //Contains definitions for socket and its API calls
#include <netinet/in.h> //Contains definitions for internet protocol family like sockaddr_in structure

#include "setup.h"

#define PORT 8080

int create_server_socket(){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    //socket(domain, type, protocol)
    //AF_INET: Address Family - Internet. IPv4 Internet protocols
    //SOCK_STREAM: TCP
    //protocol: 0 default (IP)
    if (server_fd == -1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void bind_server_socket(int server_fd, struct sockaddr_in *address){
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(PORT);
    int bind_status = bind(server_fd, (struct sockaddr *)address, sizeof(*address));
    //bind(socket, address, address_len)
    //socketfd: socket descriptor
    //address: pointer to sockaddr structure representing the address to bind to
    //address_len: length in bytes of the address
    if (bind_status < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
}

void start_listening(int server_fd){
    short listen_status = listen(server_fd, 10);
    //listen(socket, backlog)
    //socket: socket file descriptor
    //backlog: maximum length to which the queue of pending connections for socket may grow
    if (listen_status < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
}

int accept_connection(int server_fd, struct sockaddr_in *address){
    socklen_t addrlen = sizeof(*address);
    int new_socket = accept(server_fd, (struct sockaddr *)address, &addrlen);
    //accept(socket, address, address_len)
    if (new_socket < 0) {
        perror("Socket accept failed");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}


void handle_client(int client_socket){
    char buffer[1024];
    int bytes_read;
    bytes_read = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_read < 0){
        perror("Read failed");
        close(client_socket);
        return;
    }    

    buffer[bytes_read] = '\0';

    char method[10], path[100], version[10];
    sscanf(buffer, "%s %s %s", method, path, version);

    char *header_line = buffer;
    while ((header_line = strstr(header_line, "\r\n")) != NULL){
        header_line += 2;

        if (*header_line == '\r' || *header_line == '\n'){
            break;
        }
    }

    if (strcmp(path, "/") == 0){
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Alexis's Server</h1>";
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
        send(client_socket, response, strlen(response), 0);
    }

    char *file_content;
    int file_content_length;
    char *response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    send(client_socket, response_header, strlen(response_header), 0);

    //optional
    close(client_socket);
}

void cleanup(int server_fd, int client_socket){
    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;

    server_fd = create_server_socket();
    bind_server_socket(server_fd, &address);
    start_listening(server_fd);

    while (1) {
        client_socket = accept_connection(server_fd, &address);
        handle_client(client_socket);
        cleanup(server_fd, client_socket);
    }

    // Close the server socket before we exit
    close(server_fd);
    return 0;
}