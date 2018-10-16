/*
 * adc.h
 *
 *  Created on: Oct 15, 2018
 *      Author: dynatron2018
 */

#ifndef ADC_H_
#define ADC_H_

#include "stdint.h"
#include "stdbool.h"
/*
 * External ADC MCP3911 command
 */
#define MCP3911_CHANNEL_0    0x00
#define MCP3911_CHANNEL_1    0x03
#define MCP3911_MOD          0x06
#define MCP3911_PHASE        0x07
#define MCP3911_GAIN         0x09
#define MCP3911_STATUSCOM    0x0a
#define MCP3911_CONFIG       0x0c
#define MCP3911_OFFCAL_CH0   0x0e
#define MCP3911_GAINCAL_CH0  0x11
#define MCP3911_OFFCAL_CH1   0x14
#define MCP3911_GAINCAL_CH1  0x17
#define MCP3911_VREFCAL      0x1a

/*
 * The size of data that is following the ADC command
 */
#define REGSIZE_CHANNEL_0    0x03
#define REGSIZE_CHANNEL_1    0x03
#define REGSIZE_MOD          0x01
#define REGSIZE_PHASE        0x02
#define REGSIZE_GAIN         0x01
#define REGSIZE_STATUSCOM    0x02
#define REGSIZE_CONFIG       0x02
#define REGSIZE_OFFCAL_CH0   0x03
#define REGSIZE_GAINCAL_CH0  0x03
#define REGSIZE_OFFCAL_CH1   0x03
#define REGSIZE_GAINCAL_CH1  0x03
#define REGSIZE_VREFCAL      0x01

#define GAIN     32		/* ADC gain */

#define ADC_CH0 0		/* ADC channel 0 */
#define ADC_CH1 1		/* ADC channel 1 */

#define SPI0_BUFFER_SIZE 32

#define Sleep(n)  do {int t; for(t=0; t<4800*(n); t++){;}} while(0)

void LPSPI0_init(void);
void ADC_init(void);
int32_t ADC_read_data(uint8_t channel, uint8_t *adc_data);
uint8_t ADC_spi_write(uint8_t cmd, const uint8_t *pTxBuffer, uint8_t txLength);
uint8_t ADC_spi_read(uint8_t cmd, uint8_t *pRxBuffer, uint8_t rxLength);

extern bool adc_data_ready;

#endif /* ADC_H_ */
