#include "specification.h"
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "toolbox.h"

void get_hwspec(HWSpecification *hwspec) {
   // hwspec->mips = 858993459; //Cenario 1
   // hwspec->mips = 51450129; //Cenario 2
   hwspec->mips = 16843009; //Cenario 3

   hwspec->lint = 4702394921427289928;
   /*
   01000001 01000010 01000011 01000100 01000101 01000110 01000111 01001000 - em oporação
   01001000 01000111 01000110 01000101 01000100 01000011 01000010 01000001 - na memória (invertido)
   0 - 65                  - A
   1 - 16706               - B
   2 - 4276803             - C
   3 - 1094861636          - D
   4 - 280284578885        - E
   5 - 71752852194630      - F
   6 - 18368730161825351   - G
   7 - 4702394921427289928 - H
   */
   hwspec->nint = 1229605708;
   /*
   01001001 01001010 01001011 01001100 
   4 - 73         - I
   5 - 18762      - J
   6 - 4803147    - K
   7 - 1229605708 - L
   */
   hwspec->sint = 19790;
   /*
   01001101 01001110
   6 - 77    - M
   7 - 19790 - N
   */
   hwspec->uchar = 79;
   /*
   01001111
   7 - 79 - O
   */
   strcpy(hwspec->string, "PQRSTUVWXYZ");
}

void get_swspec(SWSpecification *swspec) {
   swspec->type_spec = 2;
   swspec->encrypt = false;   // 1 = verdadeiro e 2 = falso
   swspec->shift = false;              // 1 = verdadeiro e 2 = falso
   swspec->inverter = false;           // 1 = verdadeiro e 2 = falso
   swspec->decrypt = true;  // 1 = verdadeiro e 2 = falso
}

int print_swspec(SWSpecification *swspec) {
   if (swspec->type_spec != 2) return -1;

   printf("Tipo de estrutura: %d\n", swspec->type_spec);
   puts("Capacidades:");
   printf("   %d : encrypt\n"  , swspec->encrypt % 2);
   printf("   %d : shift\n"             , swspec->shift % 2);
   printf("   %d : inverter\n"          , swspec->inverter % 2);
   printf("   %d : decrypt\n", swspec->decrypt % 2);

   return 0;
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

//char* serialize_string(char *buffer, void *array, int size_type);

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

char* serialize_hwspec(char *buffer, HWSpecification *hwspec) {
   buffer = serialize_void(buffer, &hwspec->mips, sizeof(hwspec->mips));
   buffer = serialize_void(buffer, &hwspec->lint, sizeof(hwspec->lint));
   buffer = serialize_void(buffer, &hwspec->nint, sizeof(hwspec->nint));
   buffer = serialize_void(buffer, &hwspec->sint, sizeof(hwspec->sint));
   buffer = serialize_void(buffer, &hwspec->uchar, sizeof(hwspec->uchar));
   buffer = serialize_string(buffer, hwspec->string);
   buffer[0] = '\0';

   return buffer;
}

char* serialize_swspec(char *buffer, SWSpecification *swspec) {
   buffer = serialize_void(buffer, &swspec->type_spec, sizeof(swspec->type_spec));
   buffer = serialize_void(buffer, &swspec->encrypt, sizeof(swspec->encrypt));
   buffer = serialize_void(buffer, &swspec->shift, sizeof(swspec->shift));
   buffer = serialize_void(buffer, &swspec->inverter, sizeof(swspec->inverter));
   buffer = serialize_void(buffer, &swspec->decrypt, sizeof(swspec->decrypt));
   buffer[0] = '\0';

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

void deserialize_hwspec(char *buffer, HWSpecification *hwspec) {
   buffer = deserialize_void(buffer, &hwspec->mips, sizeof(hwspec->mips));
   buffer = deserialize_void(buffer, &hwspec->lint, sizeof(hwspec->lint));
   buffer = deserialize_void(buffer, &hwspec->nint, sizeof(hwspec->nint));
   buffer = deserialize_void(buffer, &hwspec->sint, sizeof(hwspec->sint));
   buffer = deserialize_void(buffer, &hwspec->uchar, sizeof(hwspec->uchar));
   //buffer = deserialize_string(buffer, hwspec->string);
   buffer[0] = '\0';
}

void deserialize_swspec(char *buffer, SWSpecification *swspec) {
   buffer = deserialize_void(buffer, &swspec->type_spec, sizeof(swspec->type_spec));
   buffer = deserialize_void(buffer, &swspec->encrypt, sizeof(swspec->encrypt));
   buffer = deserialize_void(buffer, &swspec->shift, sizeof(swspec->shift));
   buffer = deserialize_void(buffer, &swspec->inverter, sizeof(swspec->inverter));
   buffer = deserialize_void(buffer, &swspec->decrypt, sizeof(swspec->decrypt));
   buffer[0] = '\0';
}
