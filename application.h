#ifndef APPLICATION
#define APPLICATION

#define DENSITY1 1
#define DENSITY2 2
#define DENSITY3 3
#define DENSITY4 4
#define DENSITY5 5
#define DENSITY6 6
#define DENSITY7 7
#define DENSITY8 8
#define DENSITY9 9

char to_upper_case(char letter) {
   if (letter >= 97 && letter <= 122)
      //'A'=65 e 'a'=97, então 'a'-'A'=32
      letter -= 32;

   return letter;
}

#endif
