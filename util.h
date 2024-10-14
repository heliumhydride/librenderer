#define _POSIX_C_SOURCE 200112L
#ifndef UTIL_H
#define UTIL_H
#include <sodium.h>

uint32_t randint(uint32_t min, uint32_t max);
float randfloat(float min, float max);

#endif
