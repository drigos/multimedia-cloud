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
   char buffer_recv[MAXDATASIZE]/*, buffer_send[MAXDATASIZE]*/;
   //char app[50];
   short int id_app;
   HWSpecification *hwspec_client;
   HWSpecification *hwspec_provisioned;
   SWSpecification *swspec_client;
   SWSpecification *swspec_provisioned;
   char string_spec[100], option[100];

   int i = 0; // Teste

   hwspec_client = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_client == NULL) exit (1);
   hwspec_provisioned = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_provisioned == NULL) exit (1);
   swspec_client = (SWSpecification *)malloc(sizeof(SWSpecification));
   if (swspec_client == NULL) exit (1);
   swspec_provisioned = (SWSpecification *)malloc(sizeof(SWSpecification));
   if (swspec_provisioned == NULL) exit (1);

   // Criando o socket
   socket_server = server_socket(PORT_LISTEN, BACKLOG);

   i = 0; // Teste
   for (;;) {
      printf("%d -------------------\n", i++); // Teste

      // Aceitando requisição
      socket_client = accept_socket(socket_server);

      // Início do Three-Way
      recv_socket(socket_client, buffer_recv);
      if (buffer_recv[0] == REQUEST) {

         request_remove(buffer_recv, &id_app, string_spec, option);
         deserialize_swspec(string_spec, swspec_client);


         if (provision_swspec(swspec_client, swspec_provisioned, option) < 0) {
            //nack_create();
            //send_socket(socket_client, buffer_send);
            puts("Estrutura não suportada");
            close(socket_client);
            continue;
         }
         serialize_swspec(string_spec, swspec_provisioned);
         //response_create();

         //provision_hwspec(hwspec_client, hwspec_provisioned, app);

         // Criando mensagem de resposta
         //encapsulation(buffer_send, RESPONSE, NULL, NULL);
         //send_socket(socket_client, buffer_send);
         send_socket(socket_client, string_spec);

         //dispara prefetch

         // Aguardando ack
         recv_socket(socket_client, buffer_recv);
         puts(buffer_recv);
         
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
