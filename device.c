#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "application.h"
#include "specification.h"
#include "pnr.h"

#define PORT_CONNECT 30000

int main(void) {
   int socket_client;                   // descritores de sockets
   char buffer_recv[MAXDATASIZE];       // string recebida
   char buffer_send[MAXDATASIZE];       // string que será enviada
   HWSpecification *hwspec_client;      // armazena hardware do cliente
   HWSpecification *hwspec_provisioned; // armazena hardware provisionado
   SWSpecification *swspec_client;      // armazena software do cliente
   SWSpecification *swspec_provisioned; // armazena software provisionado
   char string_spec[100];               // serialização das estruturas de especificação
   int error;

   // Alocando memória para as estruturas de especificação
   hwspec_client = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_client == NULL) exit (1);
   hwspec_provisioned = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_provisioned == NULL) exit (1);
   swspec_client = (SWSpecification *)malloc(sizeof(SWSpecification));
   if (swspec_client == NULL) exit (1);
   swspec_provisioned = (SWSpecification *)malloc(sizeof(SWSpecification));
   if (swspec_provisioned == NULL) exit (1);

   // Obtendo informações do dispositivo local
   get_hwspec(hwspec_client);
   get_swspec(swspec_client);

   // Criando o socket
   socket_client = client_socket(PORT_CONNECT, "127.0.0.1");

   // Início do Three-Way

   // Criando mensagem a ser enviada
   serialize_swspec(string_spec, swspec_client);
   request_create(buffer_send, 4369, string_spec, "login");

   // Enviando mensagem
   send_socket(socket_client, buffer_send);

   // Aguardando reposta
   recv_socket(socket_client, buffer_recv);
   // Verificando se é a resposta
   if (buffer_recv[0] == RESPONSE) {

      // Abrindo a mensagem
      response_remove(buffer_recv, string_spec);
      deserialize_swspec(string_spec, swspec_provisioned);

      puts("");
      puts("Capacidades Provisionadas");
      puts("-------------------------");
      print_swspec(swspec_provisioned);
      puts("");

      // Criando mensagem de reconhecimento
      ack_create(buffer_send);
      send_socket(socket_client, buffer_send);

      recv_socket(socket_client, buffer_recv);
      printf("Mensagem recebida:   %s\n\n", buffer_recv);

      char_stream(buffer_recv, swspec_client, buffer_recv);
      printf("\nMensagem processada: %s\n", buffer_recv);
   }
   // Verificando se o provisionamento foi negado
   else if (buffer_recv[0] == NACK) {
      error = nack_remove(buffer_recv);
      printf("Recebido NACK, erro: %d\n", error);
   }

   // Fim do Three-Way

   // Lipando a memória
   close(socket_client);
   free(hwspec_client);
   free(hwspec_provisioned);
   free(swspec_client);
   free(swspec_provisioned);

   return 0;
}
