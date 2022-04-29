#ifndef _SystemUtilites
#define _SystemUtilites

#include <stdbool.h>
#include "stm32f3xx.h"                  // Device header

void SysTick_Handler(void); //przy nadpisanej funkcji weak nie grzebac w nazwie; jesli funkcja nie bedzie uzywana nigdzie indziej, nie wpisuje jej w plik naglowkowy;
bool system_utilities_TimeExpired (uint32_t , uint32_t*);
uint32_t system_utilities_getActualMsCounter (void);
void firstRunConfiguration (void);

#endif


