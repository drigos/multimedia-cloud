#ifndef _PNR_H_
#define _PNR_H_

#include "specification.h"

// Tipos de mensagem
#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

// Tipo de estrutura incoerente ou pré-requisito não atendido
#define SPECIFICATION_NOT_SUPPORTED 1
// MEC não tem recursos suficientes para fornecer
#define INSUFFICIENT_RESOURCE 2

void request_create(char *buffer, short int id_app, char *spec, char *option);

void response_create(char *buffer, char *spec);

void ack_create(char *buffer);

void nack_create(char *buffer, uint8_t error);

//int encapsulation(char *buffer, int flag, HWSpecification *hwspec, char *option);

int request_remove(char *buffer, short int *id_app, char *spec, char *option);

int response_remove(char *buffer, char *spec);

//int ack_remove(char *buffer);

int nack_remove(char *buffer);

//int decapsulation(char *buffer, HWSpecification *hwspec, char *option);

#endif
