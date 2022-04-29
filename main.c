#include <stdio.h>
#include <stdbool.h>
#include "stm32f3xx.h"                  // Device header
#include "headers/system_utilities.h"
#include "headers/preprocessor_directives.h"
#include "headers/GPIO_configuration.h"


int main(){
	firstRunConfiguration();
	while(1){
		/* performy */
		GPIO_configuration_displayPerform();		// ten perform dba o wyswietlanie numeru na wyswietlaczach 7seg 
		/* koniec performow */
		
		GPIO_configuration_counter();
	}
}

//this comment is for 2nd commit to gitgub (test)



