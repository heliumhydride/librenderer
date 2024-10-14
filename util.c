#define _POSIX_C_SOURCE 200112L

#include "util.h"

uint32_t randint(uint32_t min, uint32_t max) {
  return randombytes_uniform(max-min) + min;
}

float randfloat(float min, float max) {
  max = max*1000; min = min*1000;
  return (randombytes_uniform(max-min) + min) / 1000;
}

