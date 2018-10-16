/*
 * systemRunFsm.h
 *
 *  Created on: Oct 15, 2018
 *      Author: Zhiyuan
 */

#ifndef SYSTEMRUNFSM_H_
#define SYSTEMRUNFSM_H_

#include "stdint.h"

#define	TAPS	  4		/* Number of filter taps in FIR filter */

/*
 * System Finite State Machine State Set
 */
typedef enum
{
	INITIALIZE = 1,		// Initialize all variables.
	READ_ADC,			// Read ADC raw data.
	CHECK_RANGE,		// Check if the ADC raw date is in the range.
	OFFSET_DAC,			// Offset DAC if the ADC raw data is not in the range.
	UPDATE_SENSOR_OUTPUT,		// Convert ADC value to voltage and then filter it by FIR.
	UPDATE_UART_DATA			// Update the UART data.
} SYS_FSM_STATES;

/*
 * Custom UART data fields
 */
typedef union
{
	uint8_t array[9];
	struct
	{
		uint8_t HEADER;					// array[0]
		uint8_t TYPE;
		uint8_t SIZE;
		uint8_t DATA0;
		uint8_t DATA1;
		uint8_t DATA2;
		uint8_t STATUS;
		uint8_t SAW;
		uint8_t CHECKSUM;				// array[8]
	} item;
} UART_DATA_t;

extern SYS_FSM_STATES fsm_state; // Hold the FSM current state.

void fsm_task_run(void);

int32_t fir_filter(int64_t data_64);

#endif /* SYSTEMRUNFSM_H_ */
