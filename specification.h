#ifndef SPECIFICATION
#define SPECIFICATION

typedef struct hw_specification {
   unsigned int mips;
   long int lint;
   int nint;
   short int sint;
   unsigned char uchar;
   char string[100];
} HWSpecification;

/*
typedef struct specification {
   int mips;
   short int ant;
   char text[300];
} Specification;
*/

void get_hwspec(HWSpecification *hwspec) {
   hwspec->mips = 1076374128;
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

char* serialize_void(char *buffer, const void *value, int size) {
   //int size = sizeof(value);

   if (size == 8) {
//      puts("tamanho 8");

      buffer[0] = *(uint64_t *)value >> 56;
      buffer[1] = *(uint64_t *)value >> 48;
      buffer[2] = *(uint64_t *)value >> 40;
      buffer[3] = *(uint64_t *)value >> 32;
/*
      printf("0 - %lu\n1 - %lu\n2 - %lu\n3 - %lu\n",
      *(uint64_t *)value >> 56,
      *(uint64_t *)value >> 48,
      *(uint64_t *)value >> 40,
      *(uint64_t *)value >> 32);

      printf("%c%c%c%c\n", buffer[0], buffer[1], buffer[2], buffer[3]);
*/
      buffer += 4;
   }
   if (size >= 4) {
//      puts("tamanho 4");

      buffer[0] = *(uint32_t *)value >> 24;
      buffer[1] = *(uint32_t *)value >> 16;
/*
      printf("4 - %u\n5 - %u\n",
      *(uint32_t *)value >> 24,
      *(uint32_t *)value >> 16);

      printf("%c%c\n", buffer[0], buffer[1]);
*/
      buffer += 2;
   }
   if (size >= 2) {
//      puts("tamanho 2");

      buffer[0] = *(uint16_t *)value >> 8;
/*
      printf("6 - %hu\n",
      *(uint16_t *)value >> 8);

      printf("%c\n", buffer[0]);
*/
      buffer += 1;
   }
   if (size >= 1) {
//      puts("tamanho 1");

      buffer[0] = *(uint8_t *)value;
/*
      printf("7 - %u\n",
      *(uint8_t *)value);

      printf("%c\n", buffer[0]);
*/
      buffer += 1;
   }

   return buffer;
}
/*
char* serialize_int(char *buffer, int value) {
   buffer[0] = value >> 24;
   buffer[1] = value >> 16;
   buffer[2] = value >> 8;
   buffer[3] = value;

   return buffer + 4;
}

char* serialize_char(char *buffer, char value) {
   buffer[0] = value;

   return buffer + 1;
}
*/
//char* serialize_string(char *buffer, void *array, int size_type);

char* serialize_string(char *buffer, char *string) {
   char c;
   int size, i;
   
   c = '\0';
   size = sizeof(char);
   i = 0;

   while (string[i] != c) {
      //printf("%c - %p\n", string[i], string+i);
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
   printf("%p\n", buffer);
   buffer = serialize_string(buffer, hwspec->string);
   printf("%p\n", buffer);
   buffer[0] = '\0';

   return buffer;
}

char* deserialize_int(char *buffer, int *value) {
   *value = 0;
   *value += buffer[0] << 24;
   *value += buffer[1] << 16;
   *value += buffer[2] << 8;
   *value += buffer[3];

   return buffer + 4;
}

char* deserialize_char(char *buffer, char *value) {
   *value = buffer[0];

   return buffer + 1;
}

HWSpecification* deserialize_hwspec(char *buffer) {
   HWSpecification *hwspec;
   hwspec = (HWSpecification *)malloc(sizeof(HWSpecification));
   if (hwspec == NULL) exit (1);

   buffer = deserialize_int(buffer, (int *)&(hwspec->mips));

   return hwspec;
}

// snprintf para serializar C++11
// passar estrutura com ponteiro void para send()
// adaptar funções de serialize para funcionar com string

#endif
