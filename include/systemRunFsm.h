/*
 * systemRunFsm.h
 *
 *  Created on: Oct 15, 2018
 *      Author: Zhiyuan
 */

#ifndef SYSTEMRUNFSM_H_
#define SYSTEMRUNFSM_H_

typedef enum
{
	INITIALIZE = 1,		// Initialize all variables.
	READ_ADC,			// Read ADC raw data.
	CHECK_RANGE,		// Check if the ADC raw date is in the range.
	OFFSET_DAC,			// Offset DAC if the ADC raw data is not in the range.
	UPDATE_SENSOR_OUTPUT,		// Convert ADC value to voltage and then filter it by FIR.
	UPDATE_UART_DATA			// Update the UART data.
} SYS_FSM_STATES;

extern SYS_FSM_STATES fsm_state; // Hold the FSM current state.

void fsm_task_run(void);

#endif /* SYSTEMRUNFSM_H_ */
