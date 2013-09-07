#include <stdio.h>
#include <unistd.h>
#include "socket.h"
#include "application.h"
#include "specification.h"
#include "pnr.h"

#define PORT_CONNECT 30000

int main(void) {
   //char text_lower[100], text_upper[100];
   int socket_client;
   char buffer_recv[MAXDATASIZE], buffer_send[MAXDATASIZE];
   HWSpecification *hwspec;
   //int i = 0;

   // Criando estrutura para conter informação do hardware
   hwspec = (HWSpecification *)malloc(sizeof(HWSpecification));
   get_hwspec(hwspec);

   socket_client = client_socket(PORT_CONNECT, "127.0.0.1");

   // iniciar a comunicação

   encapsulation(buffer_send, REQUEST, hwspec, "to_upper_case");

   send_socket(socket_client, buffer_send);
   //enviar pedido de aplicação

   recv_socket(socket_client, buffer_recv);
   if (!strcmp(buffer_recv, "response")) {
      send_socket(socket_client, "ack");
   }

   // comunicação iniciada

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

   return 0;
}
