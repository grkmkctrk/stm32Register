

#ifndef INC_TIM6CONFIG_H_
#define INC_TIM6CONFIG_H_

#include "stm32f4xx.h"                  // Device header
#include "stm32f446xx.h"

void TIM6C(void);
void resetCounter(void);
void countUS(uint16_t);

void waitUS(uint16_t);
void waitMS(uint16_t);

#endif
