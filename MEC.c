#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "application.h"
#include "specification.h"
#include "provision.h"
#include "pnr.h"

#define PORT_LISTEN 30000
#define BACKLOG 50

int main(void) {
   int socket_server, socket_client;
   char buffer_recv[MAXDATASIZE], buffer_send[MAXDATASIZE];
   char app[50];
   HWSpecification *hwspec_client;
   HWSpecification *hwspec_provisioned;

   int i = 0; // Teste

   hwspec_client = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_client == NULL) exit (1);
   hwspec_provisioned = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_provisioned == NULL) exit (1);

   // Criando o socket
   socket_server = server_socket(PORT_LISTEN, BACKLOG);

   i = 0; // Teste
   for (;;) {
      printf("%d -------------------\n", i++); // Teste

      // Aceitando requisição
      socket_client = accept_socket(socket_server);

      // Início do Three-Way
      recv_socket(socket_client, buffer_recv);
      if (decapsulation(buffer_recv, hwspec_client, app) == REQUEST) {

         printf("hwspec_client: %d\n", hwspec_client->mips);
         //se o retorto for null, não foi possível provisionar - send(NACK), close(socket), continue
         provision_alg(hwspec_client, hwspec_provisioned, app);

         // Criando mensagem de resposta
         encapsulation(buffer_send, RESPONSE, hwspec_provisioned, NULL);
         send_socket(socket_client, buffer_send);

         //dispara prefetch

         // Aguardando ack
         recv_socket(socket_client, buffer_recv);
         
      // Fim do Three-Way

         //se for recebido o ACK, preenche Tabela de Controle
         //envia aplicação - cria aqui as threads
      }

      close(socket_client);
   }
   
   close(socket_server);
   free(hwspec_client);
   free(hwspec_provisioned);

   return 0;
}
