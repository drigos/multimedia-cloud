#include "application.h"

char to_upper_case(char letter) {
   if (letter >= 97 && letter <= 122)
      //'A'==65 e 'a'==97, então ('a'-'A')==32
      letter -= 32;

   return letter;
}

char to_lower_case(char letter) {
   if (letter >= 65 && letter <= 90)
      //'A'==65 e 'a'==97, então ('a'-'A')==32
      letter += 32;

   return letter;
}

void shift_string(char *string) {
   int i, size_str;

   size_str = strlen(string);

   for(i = 0 ; i < size_str ; i++)
      // Se for um caractere alfabético minúsculo
      // converte para maiúsculo e substitui o original
      if (string[i] >= 97 && string[i] <= 122)
         string[i] -= 32;
}

void invert_string(char *string) {
   int i, middle, size_str, last_char;
   char temp;

   size_str = strlen(string);
   middle = size_str / 2;
   last_char = size_str - 1;

   // A inversão só deve ser feito até o meio, para não desenverter
   for(i = 0 ; i < middle ; i++) {
      temp = string[i];
      string[i] = string[last_char - i];
      string[last_char - i] = temp;
   }
}

void encrypt_caesar_cipher(char *string) {
   int i, size_str;

   size_str = strlen(string);

   for(i = 0 ; i < size_str ; i++) {
      // Letras minúsculas
      if (string[i] >= 97 && string[i] <= 122)
         // string[i]-97, coloca a letra 'a' como 0 e 'z' como 25
         // isso é necessário para que se possa fazer o %26
         // que garante que as últimas letras virem as primeiras
         // + 3, é a "criptografia" em si
         // 97 +, volta a letra para a faixa original da tabel ASCII
         string[i] = 97 + (string[i]-97 + 3) % 26;
      // Letras maiúsculas
      else if (string[i] >= 65 && string[i] <= 90)
         string[i] = 65 + (string[i]-65 + 3) % 26;
   }
}

void decrypt_caesar_cipher(char *string) {
   int i, size_str;

   size_str = strlen(string);

   for(i = 0 ; i < size_str ; i++) {
      if (string[i] >= 97 && string[i] <= 122)
         // Nesse caso é necessário executar o mod duas vezes,
         // pois quando convertentdo as letras 'a', 'b' e 'c'
         // a subtração - 3 gera um valor negativo e o mod não
         // é o suficiente para corrigir a faixa, por isso fazemos
         // a adição + 26 e reexecutamos o mod 26
         string[i] = 97 + ((string[i]-97 - 3)%26 + 26)%26;
      else if (string[i] >= 65 && string[i] <= 90)
         string[i] = 65 + ((string[i]-65 - 3)%26 + 26)%26;
   }
}

void char_stream(char *buffer, SWSpecification *swspec, char *text) {

   strcpy(buffer, text);

   // Caso a estrutura especificada suporte a tarefa, essa será executada

   if (swspec->encrypt == true) {
      encrypt_caesar_cipher(buffer);
      printf("encrypt:  %s\n", buffer);
      //sleep(1);
   }
   if (swspec->shift == true) {
      shift_string(buffer);
      printf("shift:    %s\n", buffer);
      //sleep(1);
   }

   if (swspec->inverter == true) {
      invert_string(buffer);
      printf("inverter: %s\n", buffer);
      //sleep(1);
   }

   if (swspec->decrypt == true) {
      decrypt_caesar_cipher(buffer);
      printf("decrypt:  %s\n", buffer);
      //sleep(1);
   }
}
