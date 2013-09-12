#ifndef _PROVISION_H_
#define _PROVISION_H_

#include "specification.h"
#include "toolbox.h"

// Algoritmo para provisionar recursos baseado nas caractirísticas de software do cliente
int provision_swspec(SWSpecification *swspec_client, SWSpecification *swspec_provisioned, char *app);

// Algoritmo para provisionar recursos baseado nas caractirísticas de hardware do cliente
void provision_alg(HWSpecification *hwspec_client, HWSpecification *hwspec_provisioned, char *application);

#endif
