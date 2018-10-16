/*
 * adc.c
 *
 *  Created on: Oct 15, 2018
 *      Author: dynatron2018
 */

#include "adc.h"
#include "Cpu.h"
#include "stdint.h"
#include "string.h"

uint8_t lpspi0_adc_txDataBuffer[SPI0_BUFFER_SIZE] = {0};
uint8_t lpspi0_adc_rxDataBuffer[SPI0_BUFFER_SIZE] = {0};

bool adc_data_ready = false;					// adc data ready flag for reading adc data in state machine

void LPSPI0_init(void)
{
	LPSPI_DRV_MasterInit(LPSPI0_ADC, &lpspi0_adcState, &lpspi0_adc_MasterConfig0);
	LPSPI_DRV_MasterSetDelay(LPSPI0_ADC, 1U, 1U, 1U);
	INT_SYS_SetPriority(LPSPI0_IRQn, 11);
	INT_SYS_ClearPending(LPSPI0_IRQn);
//	INT_SYS_EnableIRQ(LPSPI0_IRQn);    // LPSPI0_IRQn has been enabled in LPSPI_DRV_MasterInit()
}

void ADC_init(void)
{
	PINS_DRV_ClearPins(PTA, 1<<0);  /* reset ADC */
	Sleep(10);						/* Hold reset */
	PINS_DRV_SetPins(PTA, 1<<0);	/* release ADC reset */
	Sleep(10);						/* Hold */

	// Reset ADC as per sect. 6.7.2 of data sheets
	uint8_t adc_reset_data[2] = {0x00, 0xC0};
	ADC_spi_write(MCP3911_CONFIG, adc_reset_data, REGSIZE_CONFIG);

	// Configure ADC in continuous write mode MCLK is set to 4MHz (output from microcontroller)
	// Set gain to 32x with no boost
	// Set config to OSR of 256
	//                              06    07    08    09    0A    0B    0C    0D    0E    0F    10    12    13    14    15    16    17    18    19    1A                                      1a
	uint8_t adc_config_data[20] = {0x00, 0x00, 0x00, 0x00, 0x10, 0xB8, 0x1F, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42};
	ADC_spi_write(MCP3911_PHASE, adc_config_data, sizeof(adc_config_data));

	// Enable PORTA 1 interrupt for detecting the falling edge on the ADC Ready pin
	INT_SYS_SetPriority(PORTA_IRQn, 13); 						// Set interrupt priority for PORTA 1 (ADC data ready)
	INT_SYS_ClearPending(PORTA_IRQn);
	INT_SYS_EnableIRQ(PORTA_IRQn);
}

void ADC_read_config(void)
{
	uint8_t adc_data[21] = {0};
	ADC_spi_read(MCP3911_MOD, adc_data, 21);
}

/* Function returns the int32_t representation of the
 * three ADC data bytes that are returned through the
 * adc_data pointer
 */
int32_t ADC_read_data(uint8_t channel, uint8_t *adc_data)
{
	int32_t adc_val = 0;
	if (channel == 0)
	{
		ADC_spi_read(MCP3911_CHANNEL_0, adc_data, 3);
	}
	else if (channel == 1)
	{
		ADC_spi_read(MCP3911_CHANNEL_1, adc_data, 3);
	}

	adc_val = adc_val | adc_data[0] << 16 | adc_data[1] << 8 | adc_data[2];

	if (adc_val & 0x800000) { adc_val |= 0xFF000000; }   // Make sure the sign bit is represented by the MSB of the int32
	return adc_val;
}

double ADC_calc_voltage(int32_t adc_val)
{
	double voltage = 0;
	voltage = -1.2 * adc_val / (GAIN * 1.5 * 8388608);  // Negate because ADC measures on the negative input
	return voltage;
}

/*
 * Convert voltage to signed int32
 */
int32_t volt2int32(double data)
{
	int32_t output = 0;
	output = (int32_t)(20 * 1e6 * data);  // 0.05uV/bit
	return output;
}

/*
 * External ADC SPI Write
 */
uint8_t ADC_spi_write(uint8_t cmd, const uint8_t *pTxBuffer, uint8_t txLength)
{
	memset(lpspi0_adc_txDataBuffer, 0, SPI0_BUFFER_SIZE);		// Clear Tx data buffer
	memset(lpspi0_adc_rxDataBuffer, 0, SPI0_BUFFER_SIZE);		// Clear Rx data buffer
	cmd = (0x00 | ((cmd) << 1)); 								// R/W bit (LSB) is 0 for writing
	lpspi0_adc_txDataBuffer[0] = cmd; 							// copy ADC command
	if( txLength > SPI0_BUFFER_SIZE - 1 ) 						// 1st byte is used for command byte
	{
		txLength = SPI0_BUFFER_SIZE - 1;
	}
	memcpy(&lpspi0_adc_txDataBuffer[1], pTxBuffer, txLength);	// copy TX data
	LPSPI_DRV_MasterTransferBlocking(LPSPI0_ADC, lpspi0_adc_txDataBuffer, lpspi0_adc_rxDataBuffer, (txLength + 1), 100);
	return 0;
}

/*
 * External ADC SPI Read
 */
uint8_t ADC_spi_read(uint8_t cmd, uint8_t *pRxBuffer, uint8_t rxLength)
{
	memset(lpspi0_adc_txDataBuffer, 0, SPI0_BUFFER_SIZE);		// Clear Tx data buffer
	memset(lpspi0_adc_rxDataBuffer, 0, SPI0_BUFFER_SIZE);		// Clear Rx data buffer
	cmd = (0x01 | ((cmd) << 1)) ; 								// R/W bit (LSB) is 1 for reading
	lpspi0_adc_txDataBuffer[0] = cmd; 							// copy ADC command
	if( rxLength > SPI0_BUFFER_SIZE - 1 ) 						// 1st byte is used for command byte
	{
		rxLength = SPI0_BUFFER_SIZE - 1;						// for safety
	}
	LPSPI_DRV_MasterTransferBlocking(LPSPI0_ADC, lpspi0_adc_txDataBuffer, lpspi0_adc_rxDataBuffer, (rxLength + 1), 100);
	memcpy(pRxBuffer, &lpspi0_adc_rxDataBuffer[1], rxLength);	// copy RX data
	return 0;
}

/*
 * PORTA 1 <---> ADC READY
 * PORTA 1 interrupt happens when a falling edge is detected on PORTA 1
 *
 */
void PORTA_IRQHandler(void)
{
	uint32_t IRQflags = 0;								// Hold the interrupt status flags
	IRQflags = PINS_DRV_GetPortIntFlag(PORTA);
	if( IRQflags & (1<<1) ) 							// Check if PORTA 1 (ADC READY) interrupt flag is set when a falling edge occurs.
	{
		adc_data_ready = true;							// set adc_data_ready flag for state-machine
	}
	PINS_DRV_ClearPortIntFlagCmd(PORTA);
}
