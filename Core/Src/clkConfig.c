/*
 * clkConfig.c
 *
 *  Created on: Nov 14, 2021
 *      Author: grkm
 */

#include "clkConfig.h"
#include "tim6Config.h"

void ClockControl(void){

	RCC->CR |= RCC_CR_HSEON;             // HSE on
	while (!(RCC->CR & RCC_CR_HSERDY));  // is ready ?

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;   // power enable
	PWR->CR |= PWR_CR_VOS;               // scale 1 mode (it is also reset value)

	FLASH->ACR =
			FLASH_ACR_ICEN |        // I found out that these bits need to be set
			FLASH_ACR_DCEN |		// i am just doing it
			FLASH_ACR_PRFTEN |
			FLASH_ACR_LATENCY_5WS;

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // Calculated by CubeMX

	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; // Calculated by CubeMX

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2; // Calculated by CubeMX


	RCC->PLLCFGR =
			(PLL_M <<0)  |            // Calculated by CubeMX
			(PLL_N << 6) |
			(PLL_P <<16) |
			(RCC_PLLCFGR_PLLSRC_HSE); // HSE selected


	RCC->CR |= RCC_CR_PLLON; 			 // PLL is enabling in 3 2 1 go
	while (!(RCC->CR & RCC_CR_PLLRDY));  // is PLL ready ?

	RCC->CFGR |= RCC_CFGR_SW_PLL;		                    // system clock selected as HSE
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // wait for it
}


void testIfCLKisOK(void){

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // (0x1UL << 0)

	GPIOA->MODER |= GPIO_MODER_MODER5_0; // (1UL << 10) 5th pin of A port is selected as output

	GPIOA->OTYPER |= 0;  		 // push pull as default mode
	GPIOA->OSPEEDR |= 0; 		 // low speed as default mode
}

void testGo(void){
	GPIOA->BSRR |= GPIO_BSRR_BS5; //(1 << 5); // set
	waitMS(500); // delay(10000000);
	GPIOA->BSRR |= GPIO_BSRR_BR5; //(1 << 21); // reset
	waitMS(500); // delay(10000000);
}
