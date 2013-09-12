#include "pnr.h"

void request_create(char *buffer, short int id_app, char *spec, char *option) {

   buffer[0] = REQUEST;
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
}

void response_create(char *buffer, char *spec) {

   buffer[0] = RESPONSE;
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
}

void ack_create(char *buffer) {

   buffer[0] = ACK;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = '\r';
   buffer[4] = '\n';
   buffer[5] = '\0';
}

void nack_create(char *buffer, uint8_t error) {

   buffer[0] = NACK;
   buffer[1] = '\r';
   buffer[2] = '\n';
   buffer[3] = error;
   buffer[4] = '\r';
   buffer[5] = '\n';
   buffer[6] = '\r';
   buffer[7] = '\n';
   buffer[8] = '\0';
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
