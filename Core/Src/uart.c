/*
 * uart.c
 *
 *  Created on: 17 Kas 2021
 *      Author: grkm
 */

#include "uart.h"

void uart2C(void){
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // (0x1UL << 17U) enable uart2 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // (0x1UL << 0)   enable GPIOA clock

	GPIOA->MODER   |= GPIO_MODER_MODER2_1;  // (0x2UL << 4U)
	GPIOA->MODER   |= GPIO_MODER_MODER3_1;  // (0x2UL << 6U)

	GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3); // ((0x3UL << 4U) | (0x3UL << 6U))

	GPIOA->AFR[0] |= (0x7UL << 8U);  // bytes(8:9:10:11)   = 0:1:1:1
	GPIOA->AFR[0] |= (0x7UL << 12U); // bytes(12:13:14:15) = 0:1:1:1

	USART2->CR1 = 0x00;		     // clear all
	USART2->CR1 |= USART_CR1_UE; // (0x1UL << 13)

	USART2->CR1 &= ~(USART_CR1_M); // ~(0x1UL << 12) // M = 0 means 8 bit data length

	// Tx/Rx BaudRate = fCK / (8*(2 - OVER8)*USARTDIV); we got OVER8 = 0 and BaudRate = 115200
	//    USARTDIV = 45000000 / (8*2*115200)
	//	  USARTDIV = 24.414063
	//	  Mantissa = 24
	//	  Fraction = 16*0.414063
	//	  Fraction = 6.624 and nearest is 7
	//	  BRR = 0x197 = ((24U << 4U) | (7U << 0))
	USART2->BRR |= ((24U << 4U) | (7U << 0));

	USART2->CR1 |= USART_CR1_RE; // RE = 1 Enable the Receiver
	USART2->CR1 |= USART_CR1_TE; // TE = 1 Enable the Transmitter
}

void uart2SendChar(uint8_t ch){
	USART2->DR = ch; // enter the data to DR register
	while(!(USART2->SR & USART_CR1_TCIE)); // (0X1UL << 6U)
}

void uart2SendString(char* str){ while(*str) uart2SendChar(*str++); uart2SendChar('\n'); }

uint8_t uart2getChar(void){ while(!(USART2->SR & USART_SR_RXNE)); return USART2->DR; }

