#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

// Tamnho máximo das mensagens enviadas pela rede
// Usada para definir o tamanho dos buffers de envio e recebimento
#define MAXDATASIZE 1000

// Cria o socket, preenche a estrutura de destino e se conecta
// Retorna o file descritor do socket cliente
int client_socket(int, char *);

// Cria o socket, preenche a estrutura local
// associa a porta da estrutra local ao socket
// e coloca em modo de escuta
// Retorna o file descritor do socket servidor
int server_socket(int, int);

// Usada pelo servidor para aceitar a próxima requisição da fila
// Retorna o file descritor do socket conectado ao cliente
// Mantém o socket do servidor inalterado
int accept_socket(int);

// Usado por ambos cliente e servidor para aceitar as mensagem que chegam
// Retorna o número de bytes da mensagem recebida
int recv_socket(int, char *);

// Usado por ambos cliente e servidor para enviar mensagens à seus peers
// Não há retorno
void send_socket(int, char *);

#endif
