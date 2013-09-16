#include "specification.h"

void get_hwspec(HWSpecification *hwspec) {
   // hwspec->mips = 858993459; //Cenario 1
   // hwspec->mips = 51450129; //Cenario 2
   hwspec->mips = 16843009; //Cenario 3

   //hwspec->lint = 4702394921427289928;
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

   // true  - indica capacidade de executari a tarefa
   // false - indica incapacidade de executar a tarefa
   swspec->encrypt = true;
   swspec->shift = false;
   swspec->inverter = true;
   swspec->decrypt = true;
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

char* serialize_hwspec(char *buffer, HWSpecification *hwspec) {
   buffer = serialize_void(buffer, &hwspec->mips, sizeof(hwspec->mips));
   //buffer = serialize_void(buffer, &hwspec->lint, sizeof(hwspec->lint));
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

void deserialize_hwspec(char *buffer, HWSpecification *hwspec) {
   buffer = deserialize_void(buffer, &hwspec->mips, sizeof(hwspec->mips));
   //buffer = deserialize_void(buffer, &hwspec->lint, sizeof(hwspec->lint));
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
