/*
 * clkConfig.h
 *
 *  Created on: Nov 14, 2021
 *      Author: grkm
 */

#ifndef INC_CLKCONFIG_H_
#define INC_CLKCONFIG_H_

#include "stm32f4xx.h"                  // Device header
#include "stm32f446xx.h"

#define PLL_M 4   // calculated by CubeMX
#define PLL_N 180
#define PLL_P 0 // it is mean 2

void ClockControl(void);
void testIfCLKisOK(void);
void testGo(void);

#endif /* INC_CLKCONFIG_H_ */
