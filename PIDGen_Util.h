#ifndef __PIDGEN_UTIL_H__
#define __PIDGEN_UTIL_H__
#include <stdint.h>
#include <x86intrin.h>
uint16_t randSeed(uint32_t* seed);
__m256i vrandSeed(__m256i* seed);
void shinyPrintData(int rand1, int rand2, int PID, int TID, int SID);
void printData(int rand1, int rand2, int PID, int TID, int SID);
#endif
