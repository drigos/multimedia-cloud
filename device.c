#include <stdio.h>
#include <unistd.h>
#include "application.h"
#include "socket.h"
#include "specification.h"

#define PORT_CONNECT 30000
#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

int main(void) {
   //char text_lower[100], text_upper[100];
   int socket_client;
   char buffer_recv[MAXDATASIZE], buffer_send[MAXDATASIZE];
   HWSpecification *hwspec;
   unsigned char *string_hwspec, *ptr;  // Adaptar o tamanho
   //int i = 0;
   //Specification *provisioned;

   // Criando estrutura para conter informação do hardware
   hwspec = (HWSpecification *)malloc(sizeof(HWSpecification));
   get_hwspec(hwspec);

   socket_client = client_socket(PORT_CONNECT, "127.0.0.1");

   // iniciar a comunicação

   string_hwspec = (unsigned char *)malloc(100*sizeof(unsigned char));
   ptr = serialize_hwspec(string_hwspec, hwspec);
   ptr[0] = '\0';
   strcpy(buffer_send, "request\r\n");
   strcat(buffer_send, string_hwspec);
   strcat(buffer_send, "\r\n\r\n");

   send_socket(socket_client, buffer_send);
   //enviar struct Specification
   //criar payload - converter struct para string
   //enviar pedido de aplicação

   recv_socket(socket_client, buffer_recv);
   //provisioned = (Specification*)buffer_recv;
   //printf("%d-%hd\n", provisioned->mips, provisioned->ant);
   //puts(provisioned->text);

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
