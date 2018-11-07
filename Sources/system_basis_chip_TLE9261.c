/*
 * system_basis_chip_TLE9261.c
 *
 *  Created on: Nov 7, 2018
 *      Author: dynatron2018
 */

#include "Cpu.h"
#include "system_basis_chip_TLE9261.h"

/*
 * System Basis Chip Control Register Address (7 bits)
 */
#define MODE_SUPPLY_CONTROL_REG_ADDRESS		(0b0000001)
#define HARDWARE_CONTROL_REG_ADDRESS		(0b0000010)
#define WATCHDOG_CONTROL_REG_ADDRESS		(0b0000011)
#define BUS_CONTROL_1_REG_ADDRESS			(0b0000100)



static SBC_CONTROL_WORD_t SBC_write_register;
static SBC_STATUS_WORD_t  SBC_read_register;

void SBC_Init(void)
{

}




