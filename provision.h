#ifndef _PROVISION_H_
#define _PROVISION_H_

#include "specification.h"

int provision_swspec(SWSpecification *swspec_client, SWSpecification *swspec_provisioned, char *app);


void provision_alg(HWSpecification *hwspec_client, HWSpecification *hwspec_provisioned, char *application);

#endif
