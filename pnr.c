#include "pnr.h"
#include "specification.h"
#include <string.h>

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

int decapsulation(char *buffer, HWSpecification *hwspec, char *option) {
	char *pch;
	int flag;

   flag = buffer[0];
//   printf("%d: flag - %p: buffer - %d - *buffer\n", flag, buffer, *buffer);
	buffer += 3;
//   printf("%p: buffer - %d: *buffer\n", buffer, *buffer);
	
	switch (flag) {
		case REQUEST:
//         printf("%p: buffer\n", buffer);
			pch = strstr(buffer, "\r\n");
//         printf("%p: pch - %d: *pch\n", pch, *pch);
			*pch = '\0';
//         printf("%p: pch - %d: *pch\n", pch, *pch);
			deserialize_hwspec(buffer, hwspec);
//         puts(buffer);
			
			buffer = pch + 2;
//         printf("%p: buffer - %d: *buffer\n", buffer, *buffer);
			pch = strstr(buffer, "\r\n");
//         printf("%p: pch - %d: *pch\n", pch, *pch);
			*pch = '\0';
//         printf("%p: pch - %d: *pch\n", pch, *pch);
			strcpy(option, buffer);
//         puts(option);

			break;
		case RESPONSE:
			pch = strstr(buffer, "\r\n");
			pch = "\0";
			deserialize_hwspec(buffer, hwspec);
			break;
		case ACK:
			break;
		case NACK:
			break;
	}
	
	return flag;
}

