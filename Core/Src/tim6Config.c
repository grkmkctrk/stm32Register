/*
 * tim6Config.c
 *
 *  Created on: Nov 16, 2021
 *      Author: grkm
 */

#include "tim6Config.h"

void TIM6C(void){

	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // (0x1UL << 4U)

	TIM6->PSC = 89;         // (fCK_PSC / (PSC[15:0] + 1))
	TIM6->ARR = TIM_ARR_ARR; // 0xFFFF;

	TIM6->DIER = TIM_DIER_UIE; // 1 << 0

	TIM6->CR1 |= TIM_CR1_CEN;        // (1 << 0); // counter enabled
	while(!(TIM6->SR & TIM_SR_UIF)); // wait for stable

}

void resetCounter(void) { TIM6->CNT = 0x0000; }

void countUS(uint16_t U){ while(TIM6->CNT < U); }

void waitUS(uint16_t US){
	resetCounter();
	countUS(US);
}

void waitMS(uint16_t MS){
	for(
			uint16_t hold = 0;
			hold < MS;
			waitUS(1000), hold++
	);
}
