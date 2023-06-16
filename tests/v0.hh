

#ifndef OCTETOS_AVERSO_V0_TESTING_HH
#define OCTETOS_AVERSO_V0_TESTING_HH

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#define infimium 0.0001

int v0_init(void);
int v0_clean(void);

void v0_developing();
void v0_math();
void v0_opnegl_compatible();
void v0_cpp_features();

#endif
