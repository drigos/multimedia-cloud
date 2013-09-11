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
   int socket_server, socket_client;    // descritores de sockets
   char buffer_recv[MAXDATASIZE];       // string recebida
   char buffer_send[MAXDATASIZE];       // string que será enviada
   short int id_app;                    // id da aplicação do cliente
   HWSpecification *hwspec_client;      // armazena hardware do cliente
   HWSpecification *hwspec_provisioned; // armazena hardware provisionado
   SWSpecification *swspec_client;      // armazena software do cliente
   SWSpecification *swspec_provisioned; // armazena software provisionado
   char string_spec[100];               // serialização das estruturas de especificação
   char option[100];                    // opções recebidas da aplicação cliente

   int i = 0; // Teste

   // Alocando memória para as estruturas de especificação
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

   for (;;) {
      printf("%d -------------------\n", i++); // Teste

      // Aceitando requisição
      socket_client = accept_socket(socket_server);

      // Início do Three-Way

      // Aguardando requisição
      recv_socket(socket_client, buffer_recv);
      // Verificando se é uma requisição
      if (buffer_recv[0] == REQUEST) {

         // Abrindo a mensagem
         request_remove(buffer_recv, &id_app, string_spec, option);
         deserialize_swspec(string_spec, swspec_client);

         //pode ser criado grupo de threads para realizar os provisionamentos
         // Executa algoritmo de provisionamento
         // e verifica indisponibilidade de provisionamento
         if (provision_swspec(swspec_client, swspec_provisioned, option) < 0) {
            nack_create(buffer_send, SPECIFICATION_NOT_SUPPORTED);
            send_socket(socket_client, buffer_send);
            close(socket_client);
            continue;
         }

         puts("");
         puts("Capacidades do Cliente");
         puts("----------------------");
         print_swspec(swspec_client);
         puts("");

         // Criando mensagem de resposta
         serialize_swspec(string_spec, swspec_provisioned);
         response_create(buffer_send, RESPONSE, string_spec);

         // Enviando mensagem
         send_socket(socket_client, buffer_send);

         //dispara prefetch

         // Aguardando recomhecimento
         recv_socket(socket_client, buffer_recv);

      // Fim do Three-Way

         if (buffer_recv[0] == ACK) {
            //se for recebido o ACK, preenche Tabela de Controle
            //envia aplicação - cria aqui as threads
         }
      }

      close(socket_client);
   }
   
   close(socket_server);
   free(hwspec_client);
   free(hwspec_provisioned);
   free(swspec_client);
   free(swspec_provisioned);

   return 0;
}
