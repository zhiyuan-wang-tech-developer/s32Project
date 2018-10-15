/*
 * system finite state machine for normal run
 *
 * systemRunFsm.c
 *
 *  Created on: Oct 15, 2018
 *      Author: dynatron2018
 */

#include "systemRunFsm.h"

SYS_FSM_STATES fsm_state = INITIALIZE;

/*
 * run finite state machine in endless for loop
 */
void fsm_task_run(void)
{
	switch (fsm_state)
	{
		case INITIALIZE:
			// Initialize the variables used in this state machine.
			fsm_state = READ_ADC;
			break;

		case READ_ADC:
			// Perform ADC reading via the lpspi0.

			fsm_state = CHECK_RANGE;
			break;

		case CHECK_RANGE:
			// After ADC raw data is read, check if it is in the range.

			fsm_state = OFFSET_DAC;
			break;

		case OFFSET_DAC:
			// If the ADC raw data is not in the range, offset DAC to compensate ADC value

			fsm_state = UPDATE_SENSOR_OUTPUT;
			break;

		case UPDATE_SENSOR_OUTPUT:
			// If the ADC raw data is in the range, convert it to voltage and then filter it.

			fsm_state = UPDATE_UART_DATA;
			break;

		case UPDATE_UART_DATA:
			// Update uart data array so that it is sent by bluetooth module.

			fsm_state = READ_ADC;
			break;

		default:
			// We reset the state machine if the state machine happens to be in unknown state.

			fsm_state = INITIALIZE;
			break;
	}
}
