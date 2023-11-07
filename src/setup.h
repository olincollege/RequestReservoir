#ifndef SETUP_H
#define SETUP_H

#include <netinet/in.h> // Required for sockaddr_in structure

int create_server_socket();
/*******************************
 * Creates a socket for the server.
 * @return: Server socket file descriptor.
 ******************************/

void bind_socket(int server_fd, struct sockaddr_in *server_address);
/*******************************
 * Binds the socket to the server address and the port.
 * @param server_fd: Server socket file descriptor.
 * @param server_address: Server address structure.
 ******************************/

void start_listening(int server_fd);
/*******************************
 * Starts listening for connections on the server socket.
 * @param server_fd: Server socket file descriptor.
 ******************************/

int accept_connection(int server_fd, struct sockaddr_in *address);
/*******************************
 * Accepts a connection from a client.
 * @param server_fd: Server socket file descriptor.
 * @param address: Client address structure.
 * @return: Client socket file descriptor.
 ******************************/

void handle_client(int client_socket);
/*******************************
 * Handles the client connection by sending and receiving messages in HTTP.
 * @param client_socket: Client socket file descriptor.
 ******************************/

void cleanup(int server_fd, int client_socket);
/*******************************
 * Closes the server and client sockets.
 * @param server_fd: Server socket file descriptor.
 * @param client_socket: Client socket file descriptor.
 ******************************/

#endif // SETUP_H
