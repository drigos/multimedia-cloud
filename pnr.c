#include "pnr.h"
#include "specification.h"
#include <string.h>
#include <inttypes.h>

int request_create(char *buffer, uint8_t type_msg, short int id_app, char *spec, char *option) {

   if (type_msg != REQUEST) return -1;

   buffer[0] = type_msg;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = 255;
   buffer[4] = '\r';
   buffer[5] = '\n';
   buffer[6] = id_app >> 8;
   buffer[7] = id_app;
   buffer[8] = '\r';
   buffer[9] = '\n';
   buffer[10] = '\0';

   strcat(buffer, spec);
   strcat(buffer, "\r\n");
   strcat(buffer, option);
   strcat(buffer, "\r\n\r\n");

   return 0;   
}

int response_create(char *buffer, uint8_t type_msg, char *spec) {

   if (type_msg != RESPONSE) return -1;

   buffer[0] = type_msg;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = 255;
   buffer[4] = 255;
   buffer[5] = 255;
   buffer[6] = '\r';
   buffer[7] = '\n';
   buffer[8] = '\0';

   strcat(buffer, spec);
   strcat(buffer, "\r\n\r\n");

   return 0;   
}

int ack_create(char *buffer, uint8_t type_msg) {

   if (type_msg != ACK) return -1;

   buffer[0] = type_msg;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = '\r';
   buffer[4] = '\n';
   buffer[5] = '\0';

   return 0;
}

int nack_create(char *buffer, uint8_t error) {

   buffer[0] = NACK;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = error;
   buffer[4] = '\r';
   buffer[5] = '\n';
   buffer[6] = '\r';
   buffer[7] = '\n';
   buffer[8] = '\0';

   return 0;
}

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

int request_remove(char *buffer, short int *id_app, char *spec, char *option) {
	char *pch;

   if (buffer[0] != REQUEST) return -1;

   *id_app = buffer[6];
   *id_app <<= 8;
   *id_app += buffer[7];

   buffer += 10;
   pch = strstr(buffer, "\r\n");
   *pch = '\0';
   strcpy(spec, buffer);

   buffer = pch + 2;
   pch = strstr(buffer, "\r\n");
   *pch = '\0';
   strcpy(option, buffer);

   return 0;
}

int response_remove(char *buffer, char *spec) {
	char *pch;

   if (buffer[0] != RESPONSE) return -1;

   buffer += 8;
   pch = strstr(buffer, "\r\n");
   *pch = '\0';
   strcpy(spec, buffer);

   return 0;
}

int nack_remove(char *buffer) {
   
   if (buffer[0] != NACK) return -1;

   return buffer[3];
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

