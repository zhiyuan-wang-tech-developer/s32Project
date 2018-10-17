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
#include "Cpu.h"
#include "adc.h"
#include "dac.h"

SYS_FSM_STATES 	fsm_state = INITIALIZE;
UART_DATA_t		uart_data;
extern uint8_t uartTxBuffer[9];
bool uart_tx_buffer_mutex = false;

uint8_t uart_sync = 0;		// UART Tx Synchronization Flag (MSB bit is used)
uint8_t saw = 0;

uint8_t adc_data[3] = {0};
int32_t adc_val = 0;

int64_t measured_voltage_64 = 0;
int64_t filter_64[TAPS] = {0};
DATA_32_t filter_output_32;


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
			measured_voltage_64 = 0;
			memset(filter_64, 0, sizeof(filter_64));
			filter_output_32.value = 0;
			/* clear the UART data array */
			memset(uart_data.array, 0, sizeof(uart_data));
			uart_tx_buffer_mutex = false;
			/* Set UART header, type and size */
			uart_data.item.HEADER = 0x55;
			uart_data.item.TYPE = 0x01;
			uart_data.item.SIZE = 0x09;
			saw = 0;
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
			if(true == CheckAdcValueOffset(adc_val))
			{
				// ADC value is not in range, DAC offset is needed.
				fsm_state = OFFSET_DAC;
			}
			else
			{
				fsm_state = UPDATE_SENSOR_OUTPUT;
			}
			break;

		case OFFSET_DAC:
			// If the ADC raw data is not in the range, offset DAC to compensate ADC value
			set_DAC(dac_val_16, true);			// Set new DAC output for ADC compensation
			fsm_state = READ_ADC;
			break;

		case UPDATE_SENSOR_OUTPUT:
			// If the ADC raw data is in the range, convert it to voltage and then filter it.
			measured_voltage_64 = ConvertToVoltage(adc_val);
			filter_output_32.value = fir_filter(measured_voltage_64);
			fsm_state = UPDATE_UART_DATA;
//			printf("adc raw val = %ld\n", adc_val);
//			printf("measured volt = %lld\n", measured_voltage_64);
//			printf("filtered volt = %ld\n", filter_output_32);
			break;

		case UPDATE_UART_DATA:
			// Update UART data array so that it is sent by bluetooth module.
			// Put data in UART data array
			uart_data.item.DATA0 = filter_output_32.byte[2]; 		// high byte
			uart_data.item.DATA1 = filter_output_32.byte[1];		// middle byte
			uart_data.item.DATA2 = filter_output_32.byte[0];		// low byte
			// Set other UART fields
			uart_data.item.STATUS = (uart_sync) | (dac_steps);  	// uart_sync MSB indicates synchronization bit;
			dac_steps = false;										// dac_steps is set to false after uart_data is updated
			uart_data.item.SAW = saw;
			saw++;
			uart_data.item.CHECKSUM = checksum(uart_data.array, (sizeof(uart_data.array) - 1));  // Do not include the last byte that is to store checksum
//			print_uart_data();
			fsm_state = READ_ADC;
			if(uart_tx_buffer_mutex == false)
			{
				uart_tx_buffer_mutex = true;
				memcpy(uartTxBuffer, (uint8_t *)&uart_data, 9);
				uart_tx_buffer_mutex = false;
			}
			break;

		default:
			// We reset the state machine if the state machine happens to be in unknown state.
			fsm_state = INITIALIZE;
			break;
	}
}

int32_t fir_filter(int64_t data_64)
{
	static uint8_t tap = 0;
	int64_t fir_output_64 = 0;
	int32_t fir_output_32 = 0;
	uint8_t i = 0;
	tap = tap % TAPS; 							// Generate the tap value
	filter_64[tap] = data_64;
	tap++;
	for (i = 0; i < TAPS; i++)
	{
		fir_output_64 += filter_64[i] / TAPS;
	}
	fir_output_32 = (int32_t)(fir_output_64 / 200);
	return fir_output_32;
}

uint8_t checksum(uint8_t *p_uart_data, uint8_t size)
{
	uint8_t i = 0;
	uint8_t checksum = 0;
	for (i = 0; i < size; i++)
	{
		checksum += p_uart_data[i];
	}
	checksum = 0x100 - checksum; //Note that the checksum is included
	return checksum;
}

void print_uart_data(void)
{
	uint8_t i = 0;
	printf("uart data:");
	for(i = 0; i < 9; i++)
	{
		printf(" %02X", uart_data.array[i]);
	}
	printf("\n");
}
