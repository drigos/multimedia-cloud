#include "socket.h"

int client_socket(int port, char *host) {
   int socket_client;
   struct sockaddr_in server;
   socklen_t size_sockaddr;

   // Preenche as informações do servidor
   server.sin_family = AF_INET;
   server.sin_port = htons(port);
   //server.sin_addr.s_addr = inet_addr(host);
   inet_aton(host, &(server.sin_addr));
   memset(&(server.sin_zero), '\0', 8);

//   puts("INÍCIO CLIENT_SOCKET");
//   printf("%15d: socket_client \n%15d: port \n%15s: host \n", socket_client, port, host);
//   printf("%15d: sin_family \n%15d: sin_port \n%15d: s_addr \n", server.sin_family, server.sin_port, server.sin_addr.s_addr);

   // Define o tamanho da struct sockaddr para usar no connect()
   size_sockaddr = sizeof(struct sockaddr);

//   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Cria o socket e trata os erros
   socket_client = socket(PF_INET, SOCK_STREAM, 0);
   if (socket_client < 0) {
      perror("socket");
      exit(errno);
   }

//   printf("%15d: socket_client após socket()\n", socket_client);

   // Coneta ao server e trata os erros
   if (connect(socket_client, (struct sockaddr *)&server, size_sockaddr) < 0) {
      perror("connect");
      exit(errno);
   }

//   puts("FIM CLIENT_SOCKET\n");
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
   memset(&(server.sin_zero), '\0', 8);

//   puts("INÍCIO SERVER_SOCKET");
//   printf("%15d: socket_server \n%15d: port \n%15d: backlog \n", socket_server, port, backlog);
//   printf("%15d: sin_family \n%15d: sin_port \n%15d: s_addr \n", server.sin_family, server.sin_port, server.sin_addr.s_addr);

   // Define o tamanho da struct sockaddr para usar no connect()
   size_sockaddr = sizeof(struct sockaddr);

//   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Cria o socket e trata os erros
   socket_server = socket(PF_INET, SOCK_STREAM, 0);
   if (socket_server < 0) {
      perror("socket");
      exit(errno);
   }

//   printf("%15d: socket_server após socket()\n", socket_server);

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

//   puts("FIM SERVER_SOCKET\n");
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

//   puts("INÍCIO ACCEPT_SOCKET");
//   printf("%15d: socket_server antes do accept()\n", socket_server);
//   printf("%15p: endereço de size_sockaddr\n", &size_sockaddr);
//   printf("%15d: size_sockaddr\n", size_sockaddr);

   // Armazena o descritor da conexão aceita no variável socket_client e trata erros
   socket_client = accept(socket_server, (struct sockaddr *)&client, &size_sockaddr);
   if (socket_client < 0) {
      perror("accept");
      exit(errno);
   }

//   printf("%15d: socket_client após accept()\n", socket_client);
//   puts("FIM ACCEPT_SOCKET\n");

   return socket_client;
}

int recv_socket(int sock, char *buffer) {
   size_t max_data_size;
   int num_bytes;

   // Define o tamanho máximo da mensagem que será recebida
   //max_data_size = sizeof(buffer);
   max_data_size = MAXDATASIZE;

//   puts("INÍCIO RECV_SOCKET");
//   printf("%15d: max_data_size\n", max_data_size);

   // Coloca a mensagem na string buffer e trata erros
   // O retorno dessa mensagem é o tamanho da string
   // Caso o tamanho exceda (max_data_size - 1) a mensagem será "truncada"
   if ((num_bytes = recv(sock, buffer, max_data_size - 1, 0)) < 0) {
      perror("recv");
      exit(errno);
   }
   // É inserido um caractere terminador após a mensagem
   buffer[num_bytes] = '\0';

//   printf("%15d: num_bytes\n", num_bytes);
//   printf("%15s: buffer\n", buffer);
//   puts("FIM RECV_SOCKET\n");

   return num_bytes;
}

void send_socket(int sock, char *buffer) {
   size_t data_size;

   // Atribui à data_size o tamanho da mensagem que será enviada
   data_size = strlen(buffer);

//   puts("INÍCIO SEND_SOCKET");
//   printf("%15d: data_size\n", data_size);
//   printf("%15s: buffer\n", buffer);

   // Envia a mensagem contida na variável buffer para o peer
   if (send(sock, buffer, data_size, 0) < 0) {
      perror("send");
      close(sock);
      exit(errno);
   }

//   puts("FIM SEND_SOCKET\n");
}

char* serialize_void(char *buffer, const void *value, int size) {
   //int size = sizeof(value);

   // Move cada byte desde o MSB até o LSB para a posição LSB
   // Em seguida salva como um caractere, truncando o valor original
   // Esse processo começa a partir do tamanho da variável
   // e passa por todos os estágios inferiores
   // e.g variável de 4 bytes passa pelo estágio de tamanho 4, 2 e 1, mas não pelo de 8

   // Verifca se o tamanho do tipo é 8
   if (size == 8) {
//      puts("tamanho 8");

      // O cast para uint64_t é necessária por se tratar de um endereço void
      // Observe que a conversão é executada no endereço e não no valor
      buffer[0] = *(uint64_t *)value >> 56;
      buffer[1] = *(uint64_t *)value >> 48;
      buffer[2] = *(uint64_t *)value >> 40;
      buffer[3] = *(uint64_t *)value >> 32;
//      printf("0 - %lu\n1 - %lu\n2 - %lu\n3 - %lu\n",
//      *(uint64_t *)value >> 56,
//      *(uint64_t *)value >> 48,
//      *(uint64_t *)value >> 40,
//      *(uint64_t *)value >> 32);

//      printf("%c%c%c%c\n", buffer[0], buffer[1], buffer[2], buffer[3]);

      // Incrementa o endereço, para tratar o próximo byte como buffer[0]
      // Graças a isso é possível um tipo de tamanho menor começar no nível inferior
      // bem como esse nível reaproveitar o código abaixo
      buffer += 4;
   }
   // Verifca se o tamanho do tipo é 4 ou maior
   if (size >= 4) {
//      puts("tamanho 4");

      // No caso de entrar nesse fluxo tendo tamanho superior a 32 bits (4 bytes)
      // só os primeiros 4 bytes de memória serão considerados
      // Computadores normalmente usam Little-Endian Byte Order
      // então os 4 primeiros bytes são na verdade os últimos 4 bytes
      // Ler sobre endianess - www.google.com
      buffer[0] = *(uint32_t *)value >> 24;
      buffer[1] = *(uint32_t *)value >> 16;
//      printf("4 - %u\n5 - %u\n",
//      *(uint32_t *)value >> 24,
//      *(uint32_t *)value >> 16);

//      printf("%c%c\n", buffer[0], buffer[1]);

      buffer += 2;
   }
   // Verifca se o tamanho do tipo é 2 ou maior
   if (size >= 2) {
//      puts("tamanho 2");

      buffer[0] = *(uint16_t *)value >> 8;
//      printf("6 - %hu\n",
//      *(uint16_t *)value >> 8);

//      printf("%c\n", buffer[0]);

      buffer += 1;
   }
   // Verifca se o tamanho do tipo é 1 ou maior
   if (size >= 1) {
//      puts("tamanho 1");

      buffer[0] = *(uint8_t *)value;
//      printf("7 - %u\n",
//      *(uint8_t *)value);

//      printf("%c\n", buffer[0]);

      buffer += 1;
   }

   // Se size for zero retorna o mesmo endereço recebido
   return buffer;
}

char* serialize_string(char *buffer, char *string) {
   char c;
   int size, i;
   
   i = 0;
   c = '\0';             // Caractere de fim
   size = sizeof(char);  // tamanho do elemento da array

   while (string[i] != c) {
//      printf("%c - %p\n", string[i], string+i);
      buffer = serialize_void(buffer, string+i, size);
      i++;
   }

   return buffer;
}

char* deserialize_void(char *buffer, void *value, int size) {

   // Move cada caracter do buffer em direção ao MSB de value
   // Esse processo consome tantas posições do buffer quanto é o tamanho de size
   // e.g variável de 4 bytes passa pelo estágio de tamanho 4, 2 e 1, mas não pelo de 8

   // Verifca se o tamanho do tipo é 8
   if (size == 8) {
//      puts("tamanho 8");

      // Cria variável temporária para receber os caracteres
      // A importância dessa variável se dá pelo fato do tipo char ter apenas um byte
      // e precisarmos do tamanho de size para realizarmos os shifts
      uint64_t temp64 = 0;
      // Zera os últimos 64 bits de value
      // O cast para uint64_t é necessária por se tratar de um endereço void
      // Observe que a conversão é executada no endereço e não no valor
      *(uint64_t *)value = 0;
//      printf(">>%lu\n", *(uint64_t *)value);

      // temp64 converte um caracter de um byte
      // para o respectivo valor da tabela ASCII com 8 bytes
      // Os 7 bytes extras são zerados e servem para suportar os shifts (<<)
      temp64 = buffer[0];
      // *value recebe o valor de buffer[0] deslocado para o MSB
      *(uint64_t *)value += temp64 << 56;
//      printf("%lu - %lu\n", temp64, temp64 << 56);
//      printf("%lu\n", *(uint64_t *)value);

      temp64 = buffer[1];
      *(uint64_t *)value += temp64 << 48;
//      printf("%lu - %lu\n", temp64, temp64 << 48);
//      printf("%lu\n", *(uint64_t *)value);

      temp64 = buffer[2];
      *(uint64_t *)value += temp64 << 40;
//      printf("%lu - %lu\n", temp64, temp64 << 40);
//      printf("%lu\n", *(uint64_t *)value);

      temp64 = buffer[3];
      *(uint64_t *)value += temp64 << 32;
//      printf("%lu - %lu\n", temp64, temp64 << 32);
//      printf("%lu\n", *(uint64_t *)value);

      // Incrementa o endereço, para tratar o próximo byte como buffer[0]
      // Graças a isso é possível um tipo de tamanho menor começar no nível inferior
      // bem como esse nível reaproveitar o código abaixo
      buffer += 4;
   }
   // Verifca se o tamanho do tipo é 4 ou maior
   if (size >= 4) {
//      puts("tamanho 4");

      uint32_t temp32 = 0;
      // Zera os últimos 32 bits de value
      // Para entender leia sobre endianess - www.google.com
      *(uint32_t *)value = 0;
//      printf(">>%u\n", *(uint32_t *)value);

      temp32 = buffer[0];
      *(uint32_t *)value += temp32 << 24;
//      printf("%u - %u\n", temp32, temp32 << 24);
//      printf("%u\n", *(uint32_t *)value);
      
      temp32 = buffer[1];
      *(uint32_t *)value += temp32 << 16;
//      printf("%u - %u\n", temp32, temp32 << 16);
//      printf("%u\n", *(uint32_t *)value);

      buffer += 2;
   }
   // Verifca se o tamanho do tipo é 2 ou maior
   if (size >= 2) {
//      puts("tamanho 2");

      uint16_t temp16 = 0;
      *(uint16_t *)value = 0;
//      printf(">>%u\n", *(uint32_t *)value);

      temp16 = buffer[0];
      *(uint16_t *)value += temp16 << 8;
//      printf("%u - %u\n", temp16, temp16 << 8);
//      printf("%u\n", *(uint32_t *)value);

      buffer += 1;
   }
   // Verifca se o tamanho do tipo é 1 ou maior
   if (size >= 1) {
//      puts("tamanho 1");

      uint8_t temp8 = 0;
      *(uint8_t *)value = 0;
//      printf(">>%u\n", *(uint32_t *)value);

      temp8 = buffer[0];
      *(uint8_t *)value += temp8;
//      printf("%u - %u\n", temp8, temp8);
//      printf("%u\n", *(uint32_t *)value);

      buffer += 1;
   }

   // Se size for zero retorna o mesmo endereço recebido
   return buffer;
}
