#ifndef _PNR_H_
#define _PNR_H_

#include "specification.h"

#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

int encapsulation(char *buffer, int flag, HWSpecification *hwspec, char *option);

int decapsulation(char *buffer, HWSpecification *hwspec, char *option);

#endif
