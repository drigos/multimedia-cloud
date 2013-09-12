#include "application.h"

char to_upper_case(char letter) {
   if (letter >= 97 && letter <= 122)
      //'A'=65 e 'a'=97, então 'a'-'A'=32
      letter -= 32;

   return letter;
}

char to_lower_case(char letter) {
   if (letter >= 65 && letter <= 90)
      //'A'=65 e 'a'=97, então 'a'-'A'=32
      letter += 32;

   return letter;
}

int* to_number(char *letter) {
	int i;
	int *numbers = (int*)malloc(sizeof(int) * strlen(letter));

	for(i = 0; i < strlen(letter); i++){
		numbers[i] = (int)letter[i];
	}

	return numbers;
}