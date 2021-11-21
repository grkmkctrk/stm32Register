/*
 * adc.c
 *
 *  Created on: 19 Kas 2021
 *      Author: grkm
 */

#include "adc.h"
#include "tim6Config.h"

void ADCInit(void){

	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  // (1UL << 8U) : ADC Clock Enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // (1UL << 0U) : GPIOA Clock Enable
	ADC->CCR |= ADC_CCR_ADCPRE_0; // (1UL << 16U) : PLCK2 divided by 4
	ADC1->CR1 |= ADC_CR1_SCAN; // (1UL << 8U) : Scan mode activated since i am using two channels
	ADC1->CR1 &= ~ADC_CR1_RES; // ~(3UL << 24U) : RES bits are 00 means 12-bit resolution
	ADC1->CR2 = ADC_CR2_CONT; 	// (1UL << 1)    : Continuous conversion mode enabled
	ADC1->CR2 |= ADC_CR2_EOCS;   // (1UL << 10U)  : End of each conversion this bit has to be set.
	ADC1->CR2 &= ~ADC_CR2_ALIGN; // ~(1UL << 11U) : ALING bit is 0 means it will be right alignment
	ADC1->SMPR2 &= ~(((7UL << 3U) | (7UL << 12U))); // 1. and 4. channels are adjusted as 3 cycle
	ADC1->SQR1 |= (1UL << 20U); // SQR1_L = 0001 : 2 conversions
	GPIOA->MODER |= GPIO_MODER_MODER1; // (3UL << 2U) : pin 1 of portA is in analog mode
	GPIOA->MODER |= GPIO_MODER_MODER4; // (3UL << 8U) : pin 4 of portA is in analog mode

}

void ADCEnable(void){
	ADC1->CR2 |= ADC_CR2_ADON; // (1UL << 0U) : Enable ADC
	waitUS(100);
}

void ADCStart(uint8_t chan){
	ADC1->SQR3 = 0; 		     // clear
	ADC1->SQR3 = (chan << 0);    // i am using two channel in one sequence
	ADC1->SR = 0;
	ADC1->CR2 |= ADC_CR2_SWSTART; // start conversion

	// wait for conv
	while(!(ADC1->SR & ADC_SR_EOC));
}


uint16_t getValue(void){ return ADC1->DR; }

void ADCDisable(void){ ADC1->CR2 &= ~(ADC_CR2_ADON); }

