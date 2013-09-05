#include <stdio.h>
#include <unistd.h>
#include "aplication.h"
#include "socket.h"
#include "specification.h"
#include "theory.h"

#define PORT_LISTEN 30000
#define BACKLOG 50

int main(void) {
   int socket_server, socket_client;
   int i = 0; // Teste
   char buffer[MAXDATASIZE];
/* Specification *provisioned;

   provisioned = (Specification*)malloc(sizeof(Specification));
   provisioned->mips = 1000;
   provisioned->ant = 962072674304001;
   for ( i = 0 ; i < 3000 ; i++ )
      provisioned->text[i] = 'a';
   provisioned->text[i] = '\0';
   printf("%d-%lld\n", provisioned->mips, provisioned->ant);
   //puts(provisioned->text);
   //printf("%s\n", (char*)provisioned);
   //puts((char*)provisioned);
*/

   socket_server = server_socket(PORT_LISTEN, BACKLOG);

   i = 0;
   for (;;) {
      printf("%d -------------------\n", i++);

      socket_client = accept_socket(socket_server);

      // iniciar a comunicação

      recv_socket(socket_client, buffer);
      if (!strcmp(buffer, "request")) {

         //receber struct Specification
         //chamar o Load Division Algorithm - ld_algorithm()
         send_socket(socket_client, "response");
         //send_socket(socket_client, provisioned->text);
         //enviar struct Specification com recursos provisionados

         recv_socket(socket_client, buffer);
         //se for o ack, preenche Tabela de Controle
         //envia aplicação - cria aqui as threads
      }

      // comunicação iniciada

      close(socket_client);
   }
   close(socket_server);

   return 0;
}
