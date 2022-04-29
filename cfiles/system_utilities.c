#include "../headers/system_utilities.h"
#include "../headers/clock_configuration.h"
#include "../headers/GPIO_configuration.h"

/*prototipes*/

void system_utilities_privSysTick_Configuration(void);

/*variables*/

static volatile uint32_t ms_systick_counter;

bool system_utilities_TimeExpired (uint32_t ms, uint32_t* tempTimer){
		if ((*tempTimer) == 0){
			*tempTimer = ms_systick_counter;
		}
			else {
				if ((ms_systick_counter - (*tempTimer)) > ms){
					*tempTimer = 0;
				return true;
				}
			}
			return false;		
}

void SysTick_Handler(void){
    ms_systick_counter++;
}

uint32_t system_utilities_getActualMsCounter (void){
	return ms_systick_counter;
}

void system_utilities_privSysTick_Configuration(void){
   SysTick->LOAD = 72000-1; 
   SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void firstRunConfiguration (void){
	Clock_configuration_PLL_72MHz();
	system_utilities_privSysTick_Configuration();
	GPIO_configuration_Init();
}

		
		
