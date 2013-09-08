#ifndef DEBUG_H
#define DEBUG_H value

#include <stdio.h>

void bprint(long int var, int size)
{
	int i;
	for (i = size; i >= 0; i--)
		fprintf(stdout, "%d", (var>>i)%2);
}

#endif