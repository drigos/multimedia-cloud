#ifndef _PNR_H_
#define _PNR_H_

#include <string.h>
#include <inttypes.h>

// Tipos de mensagem
#define REQUEST 1
#define RESPONSE 2
#define ACK 3
#define NACK 4

// Tipos de erro
// Tipo de estrutura incoerente ou pré-requisito não atendido
#define SPECIFICATION_NOT_SUPPORTED 1
// MEC não tem recursos suficientes para fornecer
#define INSUFFICIENT_RESOURCE 2

// Cria string com as informações recebidas pelos parâmetros ou implícitas
void request_create(char *, short int, char *, char *);

// Cria string com as informações recebida pelos parâmetros ou implícitas
void response_create(char *, char *);

// Cria string com as informações recebida pelos parâmetros ou implícitas
void ack_create(char *);

// Cria string com as informações recebida pelos parâmetros ou implícitas
void nack_create(char *, uint8_t);

// Remove as informações da string e armazena nas variáveis recebidas como parâmetro
int request_remove(char *, short int *, char *, char *);

// Remove as informações da string e armazena nas variáveis recebidas como parâmetro
int response_remove(char *, char *);

//int ack_remove(char *);

// Remove as informações da string e armazena nas variáveis recebidas como parâmetro
int nack_remove(char *);

#endif
