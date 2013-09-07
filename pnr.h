#ifndef PNR
#define PNR

#include "specification.h"

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

int decapsulation(char *buffer, HWSpecification *hwspec, char *option) {
	char *pch;
	int flag;

   flag = buffer[0];
	buffer += 3;
	
	switch(flag) {
		case REQUEST:
			pch = strstr(buffer, "\r\n");
			pch = "\0";
			hwspec = deserialize_hwspec(buffer);
			
			buffer = pch+2;
			pch = strstr(buffer, "\r\n");
			pch = "\0";
			strcpy(option, buffer);
			break;
		case RESPONSE:
			pch = strstr(buffer, "\r\n");
			pch = "\0";
			hwspec = deserialize_hwspec(buffer);
			break;
		case ACK:
			break;
		case NACK:
			break;
	}
	
	return flag;
}

#endif
