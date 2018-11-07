/*
 * system_basis_chip_TLE9261.h
 *
 *  Created on: Nov 7, 2018
 *      Author: dynatron2018
 */

#ifndef SYSTEM_BASIS_CHIP_TLE9261_H_
#define SYSTEM_BASIS_CHIP_TLE9261_H_

#include "stdint.h"
#include "stdbool.h"

// System Basis Chip Control Word data structure
typedef union
{
	uint16_t control_word;
	struct
	{
		uint16_t address : 7;					// 7 address bits [6...0] for register selection
		uint16_t register_access_mode : 1;		// Read only: 0; Write: 1
		uint16_t data : 8;						// 8 data bits [15...8] for configuration information
	} field;
} SBC_CONTROL_WORD_t;

// System Basis Chip Status Word data structure
typedef union
{
	uint16_t status_word;
	struct
	{
		uint8_t status;			// status information field [7...0]
		uint8_t data;			// data field [15...8]
	} field;
} SBC_STATUS_WORD_t;

#endif /* SYSTEM_BASIS_CHIP_TLE9261_H_ */
