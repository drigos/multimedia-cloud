#ifndef PROVISION
#define PROVISION value

#include "specification.h"

// HWSpecification *hwspec_mec = (HWSpecification *)malloc(sizeof(HWSpecification));
// hwspec_mec->mips = 100000;

float frame_time = 0.0000002;

void provision_alg (HWSpecification *hwspec_client, HWSpecification *hwspec_provisioned, char *application) {
   int expected_mips = 10 * 1.0f/frame_time * (int)application[0];
//   printf("%d\n", (int)application[0]);

   if (expected_mips <= hwspec_client->mips * 0.7) { //Cenario 1
      hwspec_provisioned->mips = expected_mips * 0.7;
      printf("1\n");
   }
   else if (expected_mips * 0.5 <= hwspec_client->mips * 0.7) { //Cenario 2
      hwspec_provisioned->mips = expected_mips - (int)(expected_mips * 0.5);
      printf("2\n");
   }
   else { //Cenario 3
      hwspec_provisioned->mips = expected_mips - (int)(hwspec_client->mips * 0.7);
      printf("3\n");
   }
}

#endif

// 26428,571428571
// 13214,285714286