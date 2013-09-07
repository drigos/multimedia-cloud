#ifndef PNR
#define PNR

#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

void encapsulation(char *buffer, int flag, HWSpecification *hwspec, char *option) {
   char string_hwspec[100], *ptr;  // Adaptar o tamanho

   //string_hwspec = (unsigned char *)malloc(100*sizeof(unsigned char));
   ptr = serialize_hwspec(string_hwspec, hwspec);
   ptr[0] = '\0';
   strcpy(buffer, "request\r\n");
   strcat(buffer, string_hwspec); // ptr - string_hwspec = strlen(string_hwspec)
   strcat(buffer, "\r\n");
   strcat(buffer, option);
   strcat(buffer, "\r\n\r\n");
}

void decapsulation();

#endif
