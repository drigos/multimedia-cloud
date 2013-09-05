#include <stdio.h>
#include <unistd.h>
#include "aplication.h"
#include "socket.h"
#include "specification.h"

#define PORT_CONNECT 30000

int main(void) {
   //char text_lower[100], text_upper[100];
   int socket_client;
   char buffer[MAXDATASIZE];
   //int i = 0;
   //Specification *provisioned;

   socket_client = client_socket(PORT_CONNECT, "127.0.0.1");

   // iniciar a comunicação

   send_socket(socket_client, "request");
   //enviar struct Specification
   //criar payload - converter struct para string
   //enviar pedido de aplicação

   recv_socket(socket_client, buffer);
   //provisioned = (Specification*)buffer;
   //printf("%d-%lld\n", provisioned->mips, provisioned->ant);
   puts(buffer);

   if (!strcmp(buffer, "response")) {
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
