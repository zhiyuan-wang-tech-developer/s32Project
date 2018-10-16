/*
 * dac.h
 *
 *  Created on: Oct 16, 2018
 *      Author: dynatron2018
 */

#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"
#include "stdbool.h"

#define SPI2_BUFFER_SIZE 5

extern int16_t dac_val_16;

bool CheckAdcValueOffset(int32_t adc_val);

int16_t set_DAC(int16_t dac_val, bool write);
int64_t ConvertToVoltage(int32_t adc_raw_val);

void LPSPI2_init(void);
uint8_t DAC_spi_write(uint8_t cmd, const uint8_t *pTxBuffer, uint8_t txLength);
uint8_t DAC_spi_read(uint8_t cmd, uint8_t *pRxBuffer, uint8_t rxLength);

#endif /* DAC_H_ */
