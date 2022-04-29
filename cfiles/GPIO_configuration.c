#include "../headers/GPIO_configuration.h"
#include "../headers/system_utilities.h"
#include "stm32f3xx.h"                  // Device header
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

/* global/local variable */
typedef struct SevenSegData {
	bool DisplaysOn;//Wyswietlacz wlaczony czy wylaczony? -> patrz funkcje SetDisplaysOn/off
	uint8_t actualNumber;//actualNumber
	uint8_t TempDig1;
	uint8_t TempDig4;	
}SevenSegsData_t;


static SevenSegsData_t SevenSegsData;
static SevenSegsData_t * pSevenSegsData = &SevenSegsData;

/*prototipes*/

void GPIO_configuration_privLedsInit (void);
void GPIO_Controller_privButtonInit(void);
void GPIO_configuration_privSetZero(void);
void GPIO_Controller_privsetDisplayDigit(DigitPosition_e displayNumber);
//pod perform
void GPIO_configuration_privSetDefaultValuesToSegStruc(SevenSegsData_t * );
void GPIO_configuration_setNumber(uint8_t );
uint8_t GPIO_configuration_Priv_getNumber(void);
void GPIO_configuration_setDisplaysOn(void);
void GPIO_configuration_setDisplaysOff(void);
void GPIO_configuration_privNumberToDigitConvert(SevenSegsData_t * SegStruct);
typedef enum SegOnOff {
	SegOff,
	SegOn,
}SegOnOff_e;

typedef struct DigitStruct{
	SegOnOff_e segA;
	SegOnOff_e segB;
	SegOnOff_e segC;
	SegOnOff_e segD;
	SegOnOff_e segE;
	SegOnOff_e segF;
	SegOnOff_e segG;
}DigitStruct_t;


void GPIO_configuration_privLedsInit (void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //turn on clock GPIOC
	
	GPIOC->MODER |= GPIO_MODER_MODER0_0; //PC0 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER0_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR0_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR0_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER1_0; //PC1 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER1_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR1_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR1_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER2_0; //PC2 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER2_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_2;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR2_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR2_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER3_0; //PC3 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER3_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_3;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR3_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR3_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER4_0; //PC4 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER4_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_4;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR4_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR4_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER5_0; //PC5 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER5_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_5;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR5_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR5_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER6_0; //PC6 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER6_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_6;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER7_0; //PC7 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER7_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_7;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR7_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR7_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER8_0; //PC8 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER8_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_8;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR8_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR8_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER9_0; //PC9 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER9_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_9;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR9_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER10_0; //PC10 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER10_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_10;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR10_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR10_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR10_1;
	
	GPIOC->MODER |= GPIO_MODER_MODER11_0; //PC11 configuration
	GPIOC->MODER &= ~GPIO_MODER_MODER11_1;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_11;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_0;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11_1;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR11_0;
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR11_1;
	

}

void GPIO_configuration_Init(void){	
	GPIO_configuration_privLedsInit();
	GPIO_Controller_privButtonInit();
	GPIO_configuration_privSetDefaultValuesToSegStruc(pSevenSegsData);
}

void GPIO_Controller_privButtonInit(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; //turn on the clock GPIOA
	GPIOA->MODER &= ~GPIO_MODER_MODER0_0; //button configuration
	GPIOA->MODER &= ~GPIO_MODER_MODER0_1;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_1;
}

static DigitStruct_t ConfigDigit []=
{
	{SegOn, SegOn, SegOn, SegOn, SegOn, SegOn, SegOff},							// 0
	{SegOff, SegOn, SegOn, SegOff, SegOff, SegOff, SegOff},					// 1
	{SegOn, SegOn, SegOff, SegOn, SegOn, SegOff, SegOn},						// 2
	{SegOn, SegOn, SegOn, SegOn, SegOff, SegOff, SegOn},						// 3
	{SegOff, SegOn, SegOn, SegOff, SegOff, SegOn, SegOn},						// 4
	{SegOn, SegOff, SegOn, SegOn, SegOff, SegOn, SegOn},						// 5
	{SegOn, SegOff, SegOn, SegOn, SegOn, SegOn, SegOn},							// 6
	{SegOn, SegOn, SegOn, SegOff, SegOff, SegOff, SegOff},					// 7
	{SegOn, SegOn, SegOn, SegOn, SegOn, SegOn, SegOn},							// 8
	{SegOn, SegOn, SegOn, SegOn, SegOff, SegOn, SegOn},							// 9
};

void GPIO_Controller_privsetDisplayDigit(DigitPosition_e displayNumber){
	if (displayNumber == DIG1){
		GPIOC->ODR &= ~GPIO_ODR_0;
		GPIOC->ODR |= GPIO_ODR_1;
		GPIOC->ODR |= GPIO_ODR_2;
		GPIOC->ODR |= GPIO_ODR_3;
	}
	else if (displayNumber == DIG2){
		GPIOC->ODR |= GPIO_ODR_0;
		GPIOC->ODR &= ~GPIO_ODR_1;
		GPIOC->ODR |= GPIO_ODR_2;
		GPIOC->ODR |= GPIO_ODR_3;
	}
	else if (displayNumber == DIG3){
		GPIOC->ODR |= GPIO_ODR_0;
		GPIOC->ODR |= GPIO_ODR_1;
		GPIOC->ODR &= ~GPIO_ODR_2;
		GPIOC->ODR |= GPIO_ODR_3;
	}
	else if (displayNumber == DIG4){
		GPIOC->ODR |= GPIO_ODR_0;
		GPIOC->ODR |= GPIO_ODR_1;
		GPIOC->ODR |= GPIO_ODR_2;
		GPIOC->ODR &= ~GPIO_ODR_3;
	} 
	else if (displayNumber == DisplaysOff){
		GPIOC->ODR |= GPIO_ODR_0;
		GPIOC->ODR |= GPIO_ODR_1;
		GPIOC->ODR |= GPIO_ODR_2;
		GPIOC->ODR |= GPIO_ODR_3;		
	}
}

void GPIO_configuration_setAllLedOff (void){
	(GPIOC->ODR &= ~GPIO_ODR_4);
	(GPIOC->ODR &= ~GPIO_ODR_5);
	(GPIOC->ODR &= ~GPIO_ODR_6);
	(GPIOC->ODR &= ~GPIO_ODR_7);
	(GPIOC->ODR &= ~GPIO_ODR_8);
	(GPIOC->ODR &= ~GPIO_ODR_9);
	(GPIOC->ODR &= ~GPIO_ODR_10);
}

void GPIO_configuration_ShowNumber (uint8_t Number, DigitPosition_e DigitPos){ // to nie number(numer to 13322) a digit (cyfra - 1,2,3,4 itd.)
	
	GPIO_configuration_setAllLedOff(); // segments ??
	GPIO_Controller_privsetDisplayDigit(DigitPos); //wybor wyswietlacza
	
	if ( Number <=9 ){
	ConfigDigit[Number].segA == SegOn ? (GPIOC->ODR |= GPIO_ODR_4) : (GPIOC->ODR &= ~GPIO_ODR_4);
	ConfigDigit[Number].segB == SegOn ? (GPIOC->ODR |= GPIO_ODR_5) : (GPIOC->ODR &= ~GPIO_ODR_5);
	ConfigDigit[Number].segC == SegOn ? (GPIOC->ODR |= GPIO_ODR_6) : (GPIOC->ODR &= ~GPIO_ODR_6);
	ConfigDigit[Number].segD == SegOn ? (GPIOC->ODR |= GPIO_ODR_7) : (GPIOC->ODR &= ~GPIO_ODR_7);
	ConfigDigit[Number].segE == SegOn ? (GPIOC->ODR |= GPIO_ODR_8) : (GPIOC->ODR &= ~GPIO_ODR_8);
	ConfigDigit[Number].segF == SegOn ? (GPIOC->ODR |= GPIO_ODR_9) : (GPIOC->ODR &= ~GPIO_ODR_9);
	ConfigDigit[Number].segG == SegOn ? (GPIOC->ODR |= GPIO_ODR_10) : (GPIOC->ODR &= ~GPIO_ODR_10);
	}
}

	

void GPIO_configuration_counter (void){
	/*
	static uint32_t Temptime = 0;
	static uint8_t timeDIG4 = 0;
	static uint8_t timeDIG1 = 0;
	
		if (system_utilities_TimeExpired(1000,&Temptime)){
			timeDIG4++;
		}
		GPIO_configuration_ShowNumber(timeDIG4, DIG4);
		GPIO_configuration_ShowNumber(timeDIG1, DIG1);
		if (timeDIG4>9){		
			timeDIG4 = 0;
			timeDIG1++;
		}		
		if (timeDIG1>9){
			timeDIG1 = 0;
		}
	*/
	
	/* tu wersja z performem */	
	static uint32_t Temptime = 0;
	static uint8_t timeCounter = 0;
	
	GPIO_configuration_setDisplaysOn();
	
	if (system_utilities_TimeExpired(1000,&Temptime)){
		timeCounter++;
	}
	GPIO_configuration_setNumber ((timeCounter*GPIOC->ODR)/2);
	
	
}

void GPIO_configuration_setDisplaysOn(void){
	pSevenSegsData->DisplaysOn = true;
	GPIO_configuration_setNumber(0u);
}

void GPIO_configuration_setDisplaysOff(void){
	pSevenSegsData->DisplaysOn = false;
}

void GPIO_configuration_setNumber(uint8_t number){
	pSevenSegsData->actualNumber = number;	
}

uint8_t GPIO_configuration_Priv_getNumber(void){
	return pSevenSegsData->actualNumber;	
}
// brakuje jednej funkcj - bierze acutalNumber i dokonuje obliczen tak aby zapisac kazda cyfre kolejno do TempDig1 i tempDig4
void GPIO_configuration_privNumberToDigitConvert(SevenSegsData_t * SegStruct){
	uint8_t temp = 0;	
	uint8_t number = SegStruct->actualNumber;
	temp = number%10;
	SegStruct->TempDig4 = temp;
	number = number - temp;
	temp = (number/10)%10;
	SegStruct->TempDig1 = temp;
}


void GPIO_configuration_displayPerform(void){	
	if ( pSevenSegsData->DisplaysOn == true )
	{
		
	GPIO_configuration_privNumberToDigitConvert(pSevenSegsData);
	GPIO_configuration_ShowNumber(pSevenSegsData->TempDig1/*tu ma byc funckja ktora zwraca cyfre dla DIG1*/, DIG1);
	GPIO_configuration_ShowNumber(pSevenSegsData->TempDig4/*tu ma byc funckja ktora zwraca cyfre dla DIG4*/, DIG4);
	}
	else{
		GPIO_Controller_privsetDisplayDigit(DisplaysOff);
	}
}


void GPIO_configuration_privSetDefaultValuesToSegStruc(SevenSegsData_t * SegStruct){
	SegStruct->actualNumber = 0U;
	SegStruct->DisplaysOn = false;
	SegStruct->TempDig1 = 0U;
	SegStruct->TempDig4 = 0U;
}
