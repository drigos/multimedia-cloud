#include <stdio.h>
#include <unistd.h>
#include "application.h"
#include "socket.h"
#include "specification.h"
#include "theory.h"

#define PORT_LISTEN 30000
#define BACKLOG 50

int main(void) {
   int socket_server, socket_client;
   int i = 0; // Teste
   char buffer_recv[MAXDATASIZE];
/*   Specification *provisioned;

   provisioned = (Specification *)malloc(sizeof(Specification));
   provisioned->mips = htonl(200000);
   provisioned->ant = htons(8520);
   for ( i = 0 ; i < 301 ; i++ )
      provisioned->text[i] = 'a';
   provisioned->text[i-1] = '\0';
   printf("%d | %hd\n", provisioned->mips, provisioned->ant);
   puts(provisioned->text);
   //printf("%s\n", (unsigned char *)provisioned);
   //puts((char*)provisioned);
*/
   socket_server = server_socket(PORT_LISTEN, BACKLOG);

   i = 0;
   for (;;) {
      printf("%d -------------------\n", i++);

      socket_client = accept_socket(socket_server);

      // iniciar a comunicação

      recv_socket(socket_client, buffer_recv);
      if (!strcmp(buffer_recv, "request")) {

         //receber struct Specification
         //chamar o Load Division Algorithm - ld_algorithm()
         send_socket(socket_client, "response");
         //send_socket(socket_client, provisioned->text);
         //enviar struct Specification com recursos provisionados

         recv_socket(socket_client, buffer_recv);
         //se for o ack, preenche Tabela de Controle
         //envia aplicação - cria aqui as threads
      }

      // comunicação iniciada

      close(socket_client);
   }
   close(socket_server);

   return 0;
}
