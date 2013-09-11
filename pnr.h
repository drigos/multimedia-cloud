#ifndef _PNR_H_
#define _PNR_H_

#include "specification.h"

#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

int request_create(char *buffer, uint8_t type_msg, short int id_app, char *spec, char *option);

int response_create(char *buffer, uint8_t type_msg, char *spec);

int encapsulation(char *buffer, int flag, HWSpecification *hwspec, char *option);

int request_remove(char *buffer, short int *id_app, char *spec, char *option);

int decapsulation(char *buffer, HWSpecification *hwspec, char *option);

#endif
