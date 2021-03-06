#include "provision.h"

float frame_time = 0.0000002;

int provision_swspec(SWSpecification *swspec_client, SWSpecification *swspec_provisioned, char *app) {
   // Se o tipo não for 2, retorna erro
   if (swspec_client->type_spec != 2) return -1;
   // Se o cliente não suportar a etapa final da aplicação, retorna erro
   if (swspec_client->decrypt != true) return -1;

   // O estrutura provisionada é igual a recebida do cliente
   swspec_provisioned->type_spec = 2;
   // A última etapa da aplicação não é provisionada
   // Essa é um requisito mínimo
   swspec_provisioned->decrypt = false;

   // Verifica se explicitamente o clinte informa a carência
   // de capacidade para executar alguma etapa da aplicação
   // Se sim, a mesma é provisionada
   // Para qualquer outro caso não será provisionada
   if (swspec_client->encrypt == false)
      swspec_provisioned->encrypt = true;
   else
      swspec_provisioned->encrypt = false;

   if (swspec_client->shift == false)
      swspec_provisioned->shift = true;
   else
      swspec_provisioned->shift = false;

   if (swspec_client->inverter == false)
      swspec_provisioned->inverter = true;
   else
      swspec_provisioned->inverter = false;

   return 0;
}

void provision_hwspec(HWSpecification *hwspec_client, HWSpecification *hwspec_provisioned, char *app) {
   int expected_mips = 10 * 1.0f/frame_time * (int)app[0];
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
