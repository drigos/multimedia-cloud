#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <stdlib.h>
#include <string.h>

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

int* to_number(char *letter);

char* to_char(int *numbers, int size);

#endif
