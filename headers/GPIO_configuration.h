#ifndef _GPIO_configuration
#define _GPIO_configuration
#include <stdint.h>


typedef enum DigitPosition{
	DIG1,
	DIG2,
	DIG3,
	DIG4,
	DisplaysOff
}DigitPosition_e;

void GPIO_configuration_Init(void);
void GPIO_configuration_ShowNumber (uint8_t Number, DigitPosition_e DigitPos);
void GPIO_configuration_setAllLedOff (void);
void GPIO_configuration_counter (void);

void GPIO_configuration_displayPerform(void);


#endif

