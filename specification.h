#ifndef _SPECIFICATION_H_
#define _SPECIFICATION_H_

#include <inttypes.h>

typedef struct hw_specification {
   unsigned int mips;
   long int lint;
   int nint;
   short int sint;
   unsigned char uchar;
   char string[100];
} HWSpecification;

typedef struct sw_specification {
   uint8_t type_spec;
   uint8_t encrypt;
   uint8_t shift;
   uint8_t inverter;
   uint8_t decrypt;
} SWSpecification;

/*
typedef struct specification {
   int type;   // indica quais campos estão contidos na struct e deve ser o primeiro elemento
   int mips;   // representa as unidades de processamento (didático)
} Specification;
*/

// Preenche uma struct HWSpecification com informações do dispositivo
// Recebe como parâmetro um ponteiro HWSpecification
// Rertorno void
void get_hwspec(HWSpecification *hwspec);

// Preenche uma struct SWSpecification com informações do dispositivo
// Recebe como parâmetro um ponteiro SWSpecification
// Rertorno void
void get_swspec(SWSpecification *swspec);

// Imprime a estrutura SWSpecification
// Recebe como parâmetro um ponteiro SWSpecification
// Rertorno -1 no caso de erros
int print_swspec(SWSpecification *swspec);

// Serializa tipo primitivo genérico para o buffer
// Recebe como parâmetro
//    um tipo genérico (ponteiro)
//    o tamanho do tipo
//    o endereço onde deve armazenar o resultado
// Retorna o próximo endereço disponível do buffer
char* serialize_void(char *buffer, const void *value, int size);

//char* serialize_array(char *buffer, void *array, int size_type);

// Serializa uma string para o buffer
// Chama serialize_void() para cada caracter da string
// Recebe como parâmetro
//    uma array de caracteres
//    o endereço onde deve armazenar o resultado
// Retorna o próximo endereço disponível do buffer
char* serialize_string(char *buffer, char *string);

// Serializa um struct HWSpecification
// Recebe como parâmetro
//    o ponteiro da struct
//    o ponteiro do buffer
// Retorna o próximo endereço disponível do buffer
char* serialize_hwspec(char *buffer, HWSpecification *hwspec);

// Serializa um struct SWSpecification
// Recebe como parâmetro
//    o ponteiro da struct
//    o ponteiro do buffer
// Retorna o próximo endereço disponível do buffer
char* serialize_swspec(char *buffer, SWSpecification *swspec);

// Deserializa informação do buffer para um tipo primitivo genérico
// Recebe como parâmetro
//    um tipo genérico para ser preenchido (ponteiro)
//    o tamanho do tipo
//    o endereço onde está armazenada a informação
// Retorna o próximo endereço do buffer a ser verificado
char* deserialize_void(char *buffer, void *value, int size);

//char* deserialize_string(char *buffer, char *string);

// Deserializa um struct HWSpecification
// Recebe como parâmetro
//    o ponteiro da struct alocada para ser preenchida
//    o endereço onde está armazenada a informação
// Retorno void
void deserialize_hwspec(char *buffer, HWSpecification *hwspec);

// Deserializa um struct SWSpecification
// Recebe como parâmetro
//    o ponteiro da struct alocada para ser preenchida
//    o endereço onde está armazenada a informação
// Retorno void
void deserialize_swspec(char *buffer, SWSpecification *swspec);

#endif
