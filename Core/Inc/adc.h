/*
 * adc.h
 *
 *  Created on: 19 Kas 2021
 *      Author: grkm
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f4xx.h"                  // Device header
#include "stm32f446xx.h"

void ADCInit(void);
void ADCEnable(void);
void ADCStart(uint8_t chan);
uint16_t getValue(void);

#endif /* INC_ADCCONFIG_H_ */
