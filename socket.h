#ifndef _SOCKET_H_
#define _SOCKET_H_

#define MAXDATASIZE 1000

int client_socket(int port, char *host);

int server_socket(int port, int backlog);

int accept_socket(int socket_server);

int recv_socket(int sock, char *buffer);

void send_socket(int sock, char *buffer);

#endif
