#include "application.h"

char file[] = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat.";

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

char* shift_string(char *string) {
	int i;
	char *shifted_string = (char*)malloc(sizeof(char) * (strlen(string)+1));

	for(i = 0; i < strlen(string); i++)
		shifted_string[i] = to_upper_case(string[i]);
	shifted_string[strlen(string)] = '\0';

	return shifted_string;
}

char* invert_string(char *string) {
	int i;
	char *inverted_string = (char*)malloc(sizeof(char) * (strlen(string)+1));

	for(i = 0; i < strlen(string); i++)
		inverted_string[i] = string[strlen(string)-1 - i];
	inverted_string[strlen(string)] = '\0';

	return inverted_string;
}

char* encrypt_caesar_cipher(char *string) {
	int i;
	char *encrypted_string = (char*)malloc(sizeof(char) * (strlen(string)+1));

	for(i = 0; i < strlen(string); i++) {
	   if (string[i] >= 97 && string[i] <= 122)
			encrypted_string[i] = 97 + (string[i]-97 + 3)%26;
	   else if (string[i] >= 65 && string[i] <= 90)
			encrypted_string[i] = 65 + (string[i]-65 + 3)%26;
		else
			encrypted_string[i] = string[i];
	}
	encrypted_string[strlen(string)] = '\0';

	return encrypted_string;
}

char* decrypt_caesar_cipher(char *string) {
	int i;
	char *decrypted_string = (char*)malloc(sizeof(char) * (strlen(string)+1));
		
	for(i = 0; i < strlen(string); i++) {
	   if (string[i] >= 97 && string[i] <= 122)
			decrypted_string[i] = 97 + (string[i]-97 - 3)%26;
	   else if (string[i] >= 65 && string[i] <= 90)
			decrypted_string[i] = 65 + (string[i]-65 - 3)%26;
		else
			decrypted_string[i] = string[i];
	}
	decrypted_string[strlen(string)] = '\0';

	return decrypted_string;
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

void char_stream(SWSpecification *swspec /*, int file*/) {
   int size = strlen(file);
   char *streaming = (char *)malloc(sizeof(char) * (size+1));

   strcpy(streaming, file);

   if (swspec->encrypt == true)
      streaming = encrypt_caesar_cipher(streaming);
      //prinf("1: %s\n", straming_char);

   if (swspec->shift == true)
      streaming = shift_string(streaming);
      //prinf("1: %s\n", straming);

   if (swspec->inverter == true)
      streaming = invert_string(streaming);
      //prinf("1: %s\n", straming);

   if (swspec->decrypt == true)
      streaming = decrypt_caesar_cipher(streaming);
      //prinf("1: %s\n", straming);
}
