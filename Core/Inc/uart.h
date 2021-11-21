/*
 * uart.h
 *
 *  Created on: 17 Kas 2021
 *      Author: grkm
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f4xx.h"                  // Device header
#include "stm32f446xx.h"

void uart2C(void);
void uart2SendChar(uint8_t);
void uart2SendString(char*);
uint8_t uart2getChar(void);

#endif /* INC_UART_H_ */
