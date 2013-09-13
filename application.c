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

void shift_string(char *string) {
   int i;
   for(i = 0; i < strlen(string); i++)
      string[i] = to_upper_case(string[i]);
}

void invert_string(char *string) {
   int i;
   for(i = 0; i < strlen(string)/2; i++) {
      char temp = string[i];
      string[i] = string[strlen(string)-1 - i];
      string[strlen(string)-1 - i] = temp;
   }
}

void encrypt_caesar_cipher(char *string) {
   int i;
   for(i = 0; i < strlen(string); i++) {
      if (string[i] >= 97 && string[i] <= 122)
         string[i] = 97 + ((string[i]-97 + 3)%26 + 26)%26;
      else if (string[i] >= 65 && string[i] <= 90)
         string[i] = 65 + ((string[i]-65 + 3)%26 + 26)%26;
   }
}

void decrypt_caesar_cipher(char *string) {
   int i;      
   for(i = 0; i < strlen(string); i++) {
      if (string[i] >= 97 && string[i] <= 122)
         string[i] = 97 + ((string[i]-97 - 3)%26 + 26)%26;
      else if (string[i] >= 65 && string[i] <= 90)
         string[i] = 65 + ((string[i]-65 - 3)%26 + 26)%26;
   }
}

/*int* to_number(char *string) {
	int i;
	int *numbers = (int*)malloc(sizeof(int) * strlen(string));

	for(i = 0; i < strlen(string); i++)
		numbers[i] = (int)string[i];

	return numbers;
}

char* to_char(int *numbers, int size) {
	int i;
	char *string = (char*)malloc(sizeof(char) * size);

	for(i = 0; i < size; i++)
		string[i] = (char)numbers[i];
	string[size] = '\0';

	return string;
}
*/

void char_stream(char *buffer, SWSpecification *swspec, char *text) {
   int size = strlen(text);
   //char *streaming = (char *)malloc(sizeof(char) * (size+1));

   strcpy(buffer, text);

   if (swspec->encrypt == true) {
      encrypt_caesar_cipher(buffer);
      printf("encrypt:  %s\n", buffer);
   }
   if (swspec->shift == true) {
      shift_string(buffer);
      printf("shift:    %s\n", buffer);
   }

   if (swspec->inverter == true) {
      invert_string(buffer);
      printf("inverter: %s\n", buffer);
   }

   if (swspec->decrypt == true) {
      decrypt_caesar_cipher(buffer);
      printf("decrypt:  %s\n", buffer);
   }
}
