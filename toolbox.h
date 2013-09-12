#ifndef _TOOLBOX_H_
#define _TOOLBOX_H_

#include <stdio.h>
#include <time.h>

// Valor de Pi elevado ao quadrado
#define PI_SQR 9.869604f

enum bool {
   true = 1,
   false
};

// Imprime um número em binário
void bprint(long int var, int size);

// Obtém um número aleatório entre min e max
int get_rand(int min, int max);

#endif
