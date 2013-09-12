#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <stdlib.h>
#include <string.h>
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

char to_upper_case(char letter);

char to_lower_case(char letter);

void shift_string(char *string);

void invert_string(char *string);

void encrypt_caesar_cipher(char *string);

void decrypt_caesar_cipher(char *string);

// int* to_number(char *letter);

// char* to_char(int *numbers, int size);

// void char_stream(SWSpecification *swspec /*, int file*/)

#endif
