#ifndef SPECIFICATION
#define SPECIFICATION

typedef struct hw_specification {
   unsigned int mips;
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
   //64-16424-4204586
}

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

char* serialize_hwspec(char *buffer, HWSpecification *hwspec) {
   buffer = serialize_int(buffer, hwspec->mips);
   buffer[0] = '\0';

   return buffer;
}

char* deserialize_int(char *buffer, int *value) {
   *value = 0;
   *value += buffer[0] << 24;
   *value += buffer[1] << 16;
   *value += buffer[2] << 8;
   *value += buffer[3];
/*
01000000 00101000 00101010 01110000 - 1076374128
01110000 00101010 00101000 01000000 - 1881810976
----------------------------------- >>
00000000 00000000 00000000 01000000 - 01000000 [0]
00000000 00000000 01000000 00101000 - 00101000 [1]
00000000 01000000 00101000 00101010 - 00101010 [2]
01000000 00101000 00101010 01110000 - 01110000 [3]
----------------------------------- <<
01000000 00000000 00000000 00000000 - 01000000 [0]
         00101000 00000000 00000000 - 00101000 [1]
                  00101010 00000000 - 00101010 [2]
                           01110000 - 01110000 [3]
*/
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

// verificar endianess com mensagem simples
// snprintf para serializar C++11
// inverter serialização
// passar estrutura com ponteiro void para send()
// adaptar funções de serialize para funcionar por tamanho

#endif
