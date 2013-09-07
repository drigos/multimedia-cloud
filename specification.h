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

char* deserialize_int(char *buffer, int *value);
char* deserialize_char(char *buffer, char *value);
HWSpecification* deserialize_hwspec(char *buffer);

#endif
