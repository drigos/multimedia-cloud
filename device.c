#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "toolbox.h"
#include "application.h"
#include "specification.h"
#include "pnr.h"

#define PORT_CONNECT 30000

int main(void) {
   //char text_lower[100], text_upper[100];
   int socket_client;
   char buffer_recv[MAXDATASIZE], buffer_send[MAXDATASIZE];
   HWSpecification *hwspec_client;
   HWSpecification *hwspec_provisioned;
   SWSpecification *swspec_client;
   int flag;
   char string_spec[100];
   char app[2];
//   int i = 0;

   app[0] = DENSITY1;
   app[1] = '\0';

   hwspec_client = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_client == NULL) exit (1);
   hwspec_provisioned = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec_provisioned == NULL) exit (1);
   swspec_client = (SWSpecification *)malloc(sizeof(SWSpecification));
   if (swspec_client == NULL) exit (1);

   // Obtendo informações do hardware local
   get_hwspec(hwspec_client);
   get_swspec(swspec_client);

   serialize_swspec(string_spec, swspec_client);
//   for (i = 0 ; i < 6 ; i++ ) {
//      printf("%d ", string_spec[i]);
//   }
//   puts("");
   request_create(buffer_send, REQUEST, 4369, string_spec, "login");
//   for (i = 0 ; i < 27 ; i++ ) {
//      printf("%d ", buffer_send[i]);
//   }
//   puts("");

   // Criando o socket
   socket_client = client_socket(PORT_CONNECT, "127.0.0.1");

   // Início do Three-Way

   // Criando mensagem a ser enviada
   encapsulation(buffer_send, REQUEST, hwspec_client, app);
   send_socket(socket_client, buffer_send);

   // Aguardando reposta
   recv_socket(socket_client, buffer_recv);
   flag = decapsulation(buffer_recv, hwspec_provisioned, NULL);

   if (flag == RESPONSE) {
      printf("hwspec_prvisioned: %d\n", hwspec_provisioned->mips);

      encapsulation(buffer_send, ACK, NULL, NULL);
      send_socket(socket_client, buffer_send);
   }
   //else if (flag == NACK) { tratamento especial } (socket deve ser fechado)

   // Fim do Three-Way

/*
   printf("Digite o texto para ser convertido: ");
   scanf("%s", &text_lower);

   while (text_lower[i] != '\0') {
      text_upper[i] = to_upper_case(text_lower[i]);

      i++;
   }

   puts(text_upper);
*/

   close(socket_client);
   free(hwspec_client);
   free(hwspec_provisioned);

   return 0;
}
