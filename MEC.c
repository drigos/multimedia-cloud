#include <stdio.h>
#include <unistd.h>
#include "socket.h"
#include "application.h"
#include "specification.h"
#include "pnr.h"

#define PORT_LISTEN 30000
#define BACKLOG 50

int main(void) {
   int socket_server, socket_client;
   char buffer_recv[MAXDATASIZE], buffer_send[MAXDATASIZE];
   //HWSpecification *hwspec_client;
   HWSpecification *hwspec_provisioned;
   int i = 0; // Teste

   socket_server = server_socket(PORT_LISTEN, BACKLOG);

   i = 0;
   for (;;) {
      printf("%d -------------------\n", i++);

      socket_client = accept_socket(socket_server);

      // iniciar a comunicação

      recv_socket(socket_client, buffer_recv);
      puts(buffer_recv);
      //if (!strcmp(buffer_recv, "request")) {

         //receber struct Specification
         //chamar o Load Division Algorithm - ld_algorithm()

         // Teste
         hwspec_provisioned = (HWSpecification *)malloc(sizeof(HWSpecification));
         get_hwspec(hwspec_provisioned);

         encapsulation(buffer_send, RESPONSE, hwspec_provisioned, NULL);
         send_socket(socket_client, buffer_send);

         recv_socket(socket_client, buffer_recv);
         //se for o ack, preenche Tabela de Controle
         //envia aplicação - cria aqui as threads
      //}

      // comunicação iniciada

      close(socket_client);
   }
   close(socket_server);

   return 0;
}
