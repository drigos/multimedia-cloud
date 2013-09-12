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

int* to_number(char *string) {
	int i;
	int *numbers = (int*)malloc(sizeof(int) * strlen(string));

	for(i = 0; i < strlen(string); i++){
		numbers[i] = (int)string[i];
	}

	return numbers;
}

char* to_char(int *numbers, int size) {
	int i;
	char *string = (char*)malloc(sizeof(char) * size);

	for(i = 0; i < size; i++){
		string[i] = (char)numbers[i];
	}
	string[size] = '\0';

	return string;
}