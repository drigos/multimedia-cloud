#ifndef APLICATION
#define APLICATION

char to_upper_case(char letter) {
   if (letter >= 97 && letter <= 122)
      //'A'=65 e 'a'=97, então 'a'-'A'=32
      letter -= 32;

   return letter;
}

#endif
