#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define MAXDATASIZE 1000

int client_socket(int port, char *host) {
   int socket_client;
   struct sockaddr_in server;
   socklen_t size_sockaddr;

   // Preenche as informações do servidor
   server.sin_family = AF_INET;
   server.sin_port = htons(port);
   server.sin_addr.s_addr = inet_addr(host);
   bzero(&(server.sin_zero), 8);

   puts("INÍCIO CLIENT_SOCKET");
   printf("%15d: socket_client \n%15d: port \n%15s: host \n", socket_client, port, host);
   printf("%15d: sin_family \n%15d: sin_port \n%15d: s_addr \n", server.sin_family, server.sin_port, server.sin_addr.s_addr);

   // Define o tamanho da struct sockaddr para usar no connect()
   size_sockaddr = sizeof(struct sockaddr);

   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Cria o socket e trata os erros
   socket_client = socket(AF_INET, SOCK_STREAM, 0);
   if (socket_client < 0) {
      perror("socket");
      exit(errno);
   }

   printf("%15d: socket_client após socket()\n", socket_client);

   // Coneta ao server e trata os erros
   if (connect(socket_client, (struct sockaddr *)&server, size_sockaddr) < 0) {
      perror("connect");
      exit(errno);
   }

   puts("FIM CLIENT_SOCKET\n");

   return socket_client;
}

int server_socket(int port, int backlog) {
   int socket_server;
   struct sockaddr_in server;
   socklen_t size_sockaddr;

   // Preenche as informações do servidor
   server.sin_family = AF_INET;
   server.sin_port = htons(port);
   server.sin_addr.s_addr = INADDR_ANY;
   bzero(&(server.sin_zero), 8);

   puts("INÍCIO SERVER_SOCKET");
   printf("%15d: socket_server \n%15d: port \n%15d: backlog \n", socket_server, port, backlog);
   printf("%15d: sin_family \n%15d: sin_port \n%15d: s_addr \n", server.sin_family, server.sin_port, server.sin_addr.s_addr);

   // Define o tamanho da struct sockaddr para usar no connect()
   size_sockaddr = sizeof(struct sockaddr);

   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Cria o socket e trata os erros
   socket_server = socket(AF_INET, SOCK_STREAM, 0);
   if (socket_server < 0) {
      perror("socket");
      exit(errno);
   }

   printf("%15d: socket_server após socket()\n", socket_server);

   // Associa uma porta ao socket e trata erros
   if (bind(socket_server, (struct sockaddr *)&server, size_sockaddr) < 0) {
      perror("bind");
      exit(errno);
   }

   // Coloca a porta em modo de escuta e trata erros
   if (listen(socket_server, backlog) < 0) {
      perror("listen");
      exit(errno);
   }

   puts("FIM SERVER_SOCKET\n");

   return socket_server;
}

int accept_socket(int socket_server) {
   int socket_client;
   struct sockaddr_in client;
   socklen_t size_sockaddr;

   // Define o tamanho da struct sockaddr para usar no accept()
   // O accept() altera o valor dessa struct por isso é passado o endereço
   // mas ainda sim é necessário esse atribuição
   size_sockaddr = sizeof(struct sockaddr);

   puts("INÍCIO ACCEPT_SOCKET");
   printf("%15d: socket_server antes do accept()\n", socket_server);
   printf("%15p: endereço de size_sockaddr\n", &size_sockaddr);
   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Armazena o descritor da conexão aceita no variável socket_client e trata erros
   socket_client = accept(socket_server, (struct sockaddr *)&client, &size_sockaddr);
   if (socket_client < 0) {
      perror("accept");
      exit(errno);
   }

   printf("%15d: socket_client após accept()\n", socket_client);
   puts("FIM ACCEPT_SOCKET\n");

   return socket_client;
}

int recv_socket(int sock, char *buffer) {
   size_t max_data_size;
   int num_bytes;

   // Define o tamanho máximo da mensagem que será recebida
   //max_data_size = sizeof(buffer);
   max_data_size = MAXDATASIZE;

   puts("INÍCIO RECV_SOCKET");
   printf("%15d: max_data_size\n", max_data_size);

   // Coloca a mensagem na string buffer e trata erros
   // O retorno dessa mensagem é o tamanho da string
   // Caso o tamanho exceda (max_data_size - 1) a mensagem será "truncada"
   if ((num_bytes = recv(sock, buffer, max_data_size - 1, 0)) < 0) {
      perror("recv");
      exit(errno);
   }
   // É inserido um caractere terminador após a mensagem
   buffer[num_bytes] = '\0';

   printf("%15d: num_bytes\n", num_bytes);
   printf("%15s: buffer\n", buffer);
   puts("FIM RECV_SOCKET\n");

   return num_bytes;
}

void send_socket(int sock, char *buffer) {
   size_t data_size;

   // Atribui à data_size o tamanho da mensagem que será enviada
   data_size = strlen(buffer);

   puts("INÍCIO SEND_SOCKET");
   printf("%15d: data_size\n", data_size);
   printf("%15s: buffer\n", buffer);

   // Envia a mensagem contida na variável buffer para o peer
   if (send(sock, buffer, data_size, 0) < 0) {
      perror("send");
      close(sock);
      exit(errno);
   }

   puts("FIM SEND_SOCKET\n");

}

/* Criar uma nova thread
 * Thread herda socket_local e socket_remoto
 * O contador de referência de socket_local e socket_remoto são incrementados de 1 para 2
 * Essa thread deve fechar o socket_local reduzindo seu contador de referência para 1
 * Dessa maneira o socket_local fica dependente apenas da thread original
 * A thread original deve fechar o socket_remoto reduzindo seu contador também para 1
 * Dessa maneira o socket_remoto fica dependente apenas da thread nova
 */

/*
      if ((pid = fork()) < 0) {
         perror("fork");
         exit(errno);
      }
      else if (!pid) {
         if (send(socket_remoto, "Seja bem vindo!\n", 16, 0) < 0) {
            perror("send");
            close(socket_remoto);
            exit(0);
         }
         break;
      }
*/






