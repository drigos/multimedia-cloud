#ifndef _SPECIFICATION_H_
#define _SPECIFICATION_H_

typedef struct hw_specification {
   unsigned int mips;
   long int lint;
   int nint;
   short int sint;
   unsigned char uchar;
   char string[100];
} HWSpecification;

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

// Serializa tipo primitivo genérico para o buffer
// Recebe como parâmetro
//    um tipo genérico (ponteiro)
//    o tamanho do tipo
//    o endereço onde deve armazenar o resultado
// Retorna o próximo endereço disponível do buffer
char* serialize_void(char *buffer, const void *value, int size);

//char* serialize_string(char *buffer, void *array, int size_type);

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

// Deserializa informação do buffer para um tipo primitivo genérico
// Recebe como parâmetro
//    um tipo genérico para ser preenchido (ponteiro)
//    o tamanho do tipo
//    o endereço onde está armazenada a informação
// Retorna o próximo endereço do buffer a ser verificado
char* deserialize_void(char *buffer, void *value, int size);

// Deserializa um struct HWSpecification
// Recebe como parâmetro
//    o ponteiro da struct alocada para ser preenchida
//    o endereço onde está armazenada a informação
// Retorno void
void deserialize_hwspec(char *buffer, HWSpecification *hwspec);

#endif
