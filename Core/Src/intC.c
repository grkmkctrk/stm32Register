/*
 * intC.c
 *
 *  Created on: 18 Kas 2021
 *      Author: grkm
 */

#include "intC.h"

extern int flag;

void interruptC(void){

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // 1UL << 14U
	SYSCFG->EXTICR[0] &= ~(0xFUL << 4U);  // PortA pin1 activated as allowed interrupt
	EXTI->IMR |= EXTI_IMR_IM1; 			  // not masked
	EXTI->RTSR |= EXTI_RTSR_TR1;          // (1UL << 1U) | enable rising edge
	EXTI->FTSR &= ~EXTI_FTSR_TR1; 		  // ~(1UL << 1U) | disable falling edge
	NVIC_SetPriority(EXTI1_IRQn, 1);	  // setting of priority of interrupt
	NVIC_EnableIRQ(EXTI1_IRQn);			  // enabling
}

void intTest_GPIO(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // (1UL << 0U)  // PortA activated
	GPIOA->MODER &= ~GPIO_MODER_MODE1;   // ~(11UL < 2U) // pin 1 of PortA adjusted as output
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD1_0;  // (1UL << 2U)  // pull-up
}

// SPECIAL FUNCTION FOR INTERRUPT
void EXTI1_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR1){ // is it enable
		EXTI->PR |= EXTI_PR_PR1; // clear it first
		flag = 1;
	}
}
