#ifndef PNR
#define PNR

#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

int encapsulation(char *buffer, int flag, HWSpecification *hwspec, char *option) {
   char string_hwspec[100];  // Adaptar o tamanho

   if (flag < 1 || flag > 4)
      return -1;

   buffer[0] = flag;
   buffer[1] = '\0';
   strcat(buffer, "\r\n");

   switch (flag) {
      case REQUEST:
         serialize_hwspec(string_hwspec, hwspec);

         strcat(buffer, string_hwspec); // ptr - string_hwspec = strlen(string_hwspec)
         strcat(buffer, "\r\n");
         strcat(buffer, option);
         strcat(buffer, "\r\n\r\n");

         break;

      case RESPONSE:
         serialize_hwspec(string_hwspec, hwspec);

         strcat(buffer, string_hwspec); // ptr - string_hwspec = strlen(string_hwspec)
         strcat(buffer, "\r\n\r\n");

         break;

      case ACK:
         break;

      case NACK:
         break;
   }

   return 0;
}

void decapsulation();

#endif
