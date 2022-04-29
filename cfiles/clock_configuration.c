#include "../headers/clock_configuration.h"
#include "stm32f3xx.h"                  // Device header

void Clock_configuration_PLL_72MHz(void){
		RCC->CR |= RCC_CR_HSEBYP; // HSE bypass on
		RCC->CR |= RCC_CR_HSEON; //HSE on
		while(!(RCC->CR & RCC_CR_HSERDY)); // wait untill HSERDY is cleared
		RCC->CR |= RCC_CR_CSSON;// switch on clock security system (recommended)	
		RCC->CR &= ~RCC_CR_PLLON; //PLL off
		RCC->CFGR |= RCC_CFGR_PLLSRC_HSE_PREDIV; //PLLSRC config
		RCC->CFGR |= RCC_CFGR_PLLMUL9; //PLL input clock x9
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1; //AHB prescaler - SYSCLK divided by 1
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1: 72MHz/2 = 36MHz
		RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; //APB2: 72MHz
		RCC->CR |= RCC_CR_PLLON; //PLL on
		while(!(RCC->CR & RCC_CR_PLLRDY)); // wait untill PLLRDY is ready
		FLASH->ACR |= FLASH_ACR_PRFTBE; //Prefetch buffer enable
		FLASH->ACR &= ~FLASH_ACR_HLFCYA; // Half cycle is disabled
		FLASH->ACR &= ~FLASH_ACR_LATENCY_0; //Latency: 010: Two wait sates, if 48 < HCLK =< 72 MHz
		FLASH->ACR |= FLASH_ACR_LATENCY_1; 
		FLASH->ACR &= ~FLASH_ACR_LATENCY_2;	
		RCC->CFGR &= ~RCC_CFGR_SW_0; //system clock switch config
		RCC->CFGR |= RCC_CFGR_SW_1;
}
