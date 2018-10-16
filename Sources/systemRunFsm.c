/*
 * system finite state machine for normal run
 *
 * systemRunFsm.c
 *
 *  Created on: Oct 15, 2018
 *      Author: dynatron2018
 */

#include "systemRunFsm.h"
#include "stdio.h"
#include "string.h"
#include "adc.h"

SYS_FSM_STATES fsm_state = INITIALIZE;

uint8_t adc_data[3] = {0};
int32_t adc_val = 0;

/*
 * run finite state machine in endless for loop
 */
void fsm_task_run(void)
{
	switch (fsm_state)
	{
		case INITIALIZE:
			// Initialize the variables used in this state machine.
			adc_data_ready = false;
			memset(adc_data, 0, sizeof(adc_data));
			adc_val = 0;
			fsm_state = READ_ADC;
			break;

		case READ_ADC:
			// Perform ADC reading via the lpspi0.
			if(adc_data_ready)		// Check adc data ready flag first
			{
				adc_data_ready = false;
				adc_val = ADC_read_data(ADC_CH0, adc_data);
				fsm_state = CHECK_RANGE;
			}
			else
			{
				fsm_state = READ_ADC;
			}
			break;

		case CHECK_RANGE:
			// After ADC raw data is read, check if it is in the range.
			printf("adc raw val = %ld\n", adc_val);
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
