#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include "specification.h"
#include "toolbox.h"

#define DENSITY1 1
#define DENSITY2 2
#define DENSITY3 3
#define DENSITY4 4
#define DENSITY5 5
#define DENSITY6 6
#define DENSITY7 7
#define DENSITY8 8
#define DENSITY9 9

// Converte uma letra minúscula para maiúscula
// Outros caracteres retornam inalterados
char to_upper_case(char letter);

// Converte uma letra maiúscula para minúscula
// Outros caracteres retornam inalterados
char to_lower_case(char letter);

// Converte as letras minúsculas da string para maiúsculas
// Outros caracteres retornam inalterados
void shift_string(char *string);

// Recebe uma string e a retorna de trás para frente
void invert_string(char *string);

// Criptografa um texto com a Cifra de César
void encrypt_caesar_cipher(char *string);

// Decriptografa um texto com a Cifra de César
void decrypt_caesar_cipher(char *string);

// Aplicação que usa:
//    encrypt_caesar_cipher()
//    shift_string()
//    invert_string()
//    decrypt_caesar_cipher()
// Recebe como parâmetro
//    uma string onde será armazenado o resultado
//    uma estrutura com as capacidades de execução de host
//    uma string a ser manipulada
// Retorno void
void char_stream(char *buffer, SWSpecification *swspec, char *text);

#endif
