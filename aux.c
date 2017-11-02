#include "aux.h"

#define AUX_BASE       0x20215000UL

volatile unsigned int* aux = (unsigned int *) AUX_BASE;
