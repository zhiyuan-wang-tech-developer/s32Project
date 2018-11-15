/*
 * system_config.h
 *
 *  Created on: Nov 13, 2018
 *      Author: dynatron2018
 */

#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

// Interrupt Priority Level Settings
#define 	INTERRUPT_PRIORITY_LEVEL_UART			(5u)			// Low Power UART Module 0 RX & TX IRQ for firmware download

#define 	INTERRUPT_PRIORITY_LEVEL_TIMER_TX		(6u)			// Low Power Timer 0 IRQ for 793.65us timing to transmit ADC data
#define 	INTERRUPT_PRIORITY_LEVEL_TIMER_1s		(7u)			// Low Power Interrupt Timer 0 Channel 0 IRQ for 1 second timing

#define 	INTERRUPT_PRIORITY_LEVEL_SPI_ADC		(11u)			// Low Power SPI 0 IRQ for ADC
#define 	INTERRUPT_PRIORITY_LEVEL_SPI_DAC		(12u)			// Low Power SPI 2 IRQ for DAC
#define 	INTERRUPT_PRIORITY_LEVEL_SPI_SBC		(13u)			// Low Power SPI 1 IRQ for SBC

#define 	INTERRUPT_PRIORITY_LEVEL_ADC_RDY		(14u)			// PORT A IRQ for ADC Ready (PTA 1)
#define 	INTERRUPT_PRIORITY_LEVEL_CAN_MSG_BUF	(15u)			// CAN0 0 ~ 15 Message Buffer IRQ

// Define how many seconds the UART synchronization bit is toggled.
#define 	UART_SYNC_COUNT_SECOND					(15u)

// Define how many samples are transmitted via bluetooth every second.
#define 	UART_TX_RATE							1262u

#endif /* SYSTEM_CONFIG_H_ */
