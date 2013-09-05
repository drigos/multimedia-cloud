#ifndef SPECIFICATION
#define SPECIFICATION

typedef struct specification {
   int mips;
   long long ant;
   char text[3000];
} Specification;
/*
char* spec_to_str(const struct *Specification) {
   char *catenate;

   catenate = (char*)malloc(100*sizeof(char));

   return catenate;
}
*/
#endif
