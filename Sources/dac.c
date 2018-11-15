/*
 * dac.c
 *
 *  Created on: Oct 16, 2018
 *      Author: dynatron2018
 */

#include "dac.h"
#include "Cpu.h"
#include "string.h"
#include "system_config.h"

bool dac_steps = false;		// indicate DAC offset stepping

int16_t dac_val_16 = 2048;

const int64_t ADC_Correction = 91500;

uint8_t dac_change_count = 0;

uint8_t lpspi2_dac_txDataBuffer[SPI2_BUFFER_SIZE] = {0};
uint8_t lpspi2_dac_rxDataBuffer[SPI2_BUFFER_SIZE] = {0};

/*
 * Check if ADC raw value needs DAC offset
 *
 * @param adc_val: ADC raw value directly from ADC
 * @return
 * 		true: ADC value does need DAC offset.
 * 		false: ADC value does not need DAC offset.
 */
bool CheckAdcValueOffset(int32_t adc_val)
{
	bool AdcValueNeedOffset = false;
	// factor 91.5
	int64_t adc_val_corrected = ADC_Correction / 1000 * adc_val; 		// Do some corrections on adc raw value
//	int64_t threshold =  18750000; 				// 0.6/GAIN; 600mV/gain threshold for clipping
	int16_t stepsize_s = 300; 					// 100e-6 * 3.7 * GAIN; 100uV small step size

	if( (adc_val_corrected >= (stepsize_s*805664)) )  // && (adc_val_corrected < threshold) )
	{
		dac_val_16 -= stepsize_s/3;
		dac_steps = true;
		AdcValueNeedOffset = true;
		dac_change_count = 2;
	}
	else if( (adc_val_corrected <= -(stepsize_s*805664)) ) // && (adc_val_corrected > -threshold) )
	{
		dac_val_16 += stepsize_s/3;
		dac_steps = true;
		AdcValueNeedOffset = true;
		dac_change_count = 2;
	}
	else
	{
//		dac_steps = false;							// dac_steps is set to false after uart date is updated in state machine
		AdcValueNeedOffset = false;
		dac_change_count = 0;
	}

	return AdcValueNeedOffset;
}

/*
 * Convert ADC raw value to measured voltage
 */
int64_t ConvertToVoltage(int32_t adc_raw_val)
{
	int64_t voltage_64 = 0;
	voltage_64 = 805664 * dac_val_16 + (ADC_Correction * adc_raw_val) / 1000;
	return voltage_64;
}

/*
 * set DAC output
 */
int16_t set_DAC(int16_t dac_val, bool write)
{
	uint8_t highByte = 0;
	uint8_t lowByte = 0;
	highByte = (dac_val & 0xff00) >> 8;
	lowByte = (dac_val & 0x00ff);
	// swap dac_val high byte with its low byte
	int16_t dac_val_t = ((lowByte << 8) | highByte);
	if(write)
	{
		DAC_spi_write(0, (uint8_t *)&dac_val_t, 2);
	}
	return dac_val;
}

void LPSPI2_init(void)
{
	LPSPI_DRV_MasterInit(LPSPI2_DAC, &lpspi2_dacState, &lpspi2_dac_MasterConfig0);
	LPSPI_DRV_MasterSetDelay(LPSPI2_DAC, 1U, 1U, 1U);
	INT_SYS_SetPriority(LPSPI2_IRQn, INTERRUPT_PRIORITY_LEVEL_SPI_DAC);
	INT_SYS_ClearPending(LPSPI2_IRQn);
}

/*
 * External DAC SPI Write
 */
uint8_t DAC_spi_write(uint8_t cmd, const uint8_t *pTxBuffer, uint8_t txLength)
{
	memset(lpspi2_dac_txDataBuffer, 0, SPI2_BUFFER_SIZE);		// Clear Tx data buffer
	memset(lpspi2_dac_rxDataBuffer, 0, SPI2_BUFFER_SIZE);		// Clear Rx data buffer
	cmd = (0x00 | ((cmd) << 1)); 								// R/W bit (LSB) is 0 for writing
	lpspi2_dac_txDataBuffer[0] = cmd; 							// copy DAC command
	if( txLength > SPI2_BUFFER_SIZE - 1 ) 						// 1st byte is used for command byte
	{
		txLength = SPI2_BUFFER_SIZE - 1;
	}
	memcpy(&lpspi2_dac_txDataBuffer[1], pTxBuffer, txLength);	// copy TX data
	LPSPI_DRV_MasterTransferBlocking(LPSPI2_DAC, lpspi2_dac_txDataBuffer, lpspi2_dac_rxDataBuffer, (txLength + 1), 100);
	return 0;
}

/*
 * External DAC SPI Read
 */
uint8_t DAC_spi_read(uint8_t cmd, uint8_t *pRxBuffer, uint8_t rxLength)
{
	memset(lpspi2_dac_txDataBuffer, 0, SPI2_BUFFER_SIZE);		// Clear Tx data buffer
	memset(lpspi2_dac_rxDataBuffer, 0, SPI2_BUFFER_SIZE);		// Clear Rx data buffer
	cmd = (0x01 | ((cmd) << 1)) ; 								// R/W bit (LSB) is 1 for reading
	lpspi2_dac_txDataBuffer[0] = cmd; 							// copy DAC command
	if( rxLength > SPI2_BUFFER_SIZE - 1 ) 						// 1st byte is used for command byte
	{
		rxLength = SPI2_BUFFER_SIZE - 1;						// for safety
	}
	LPSPI_DRV_MasterTransferBlocking(LPSPI2_DAC, lpspi2_dac_txDataBuffer, lpspi2_dac_rxDataBuffer, (rxLength + 1), 100);
	memcpy(pRxBuffer, &lpspi2_dac_rxDataBuffer[1], rxLength);	// copy RX data
	return 0;
}
