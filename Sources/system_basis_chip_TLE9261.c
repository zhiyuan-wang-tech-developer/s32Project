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

/*
 * System Basis Chip Status Register Address (7 bits)
 */
#define BUS_STATUS_REG_ADDRESS				(0b1000100)
#define PRODUCT_INFO_REG_ADDRESS			(0b1111110)

/*
 * System Basis Chip Control Register Configuration Byte
 */
// SBC normal mode; VCC3 ON; VCC2 ON in normal mode; VCC1 overvoltage reset; VCC1 reset threshold = highest
#define MODE_SUPPLY_CONTROL_CONFIG_BYTE		(0b00101000)
#define HARDWARE_CONTROL_CONFIG_BYTE		(0b01010000)
#define WATCHDOG_CONTROL_CONFIG_BYTE		(0b00000110)
// HS-CAN module mode = CAN normal mode with no SWK
#define BUS_CONTROL_1_CONFIG_BYTE			(0b00000011)

/*
 * Register Access Mode
 */
#define READ_REG							(0u)
#define WRITE_REG							(1u)

// Mid-range SBC family + TLE9261QX (5V, no LIN, VCC3, no SWK)
#define SBC_TLE9261QX_ID					(0b00110100)


static SBC_CONTROL_WORD_t SBC_write_register;
static SBC_STATUS_WORD_t  SBC_read_register;

/*
 * @brief: System Basis Chip initialization function
 */
bool SBC_Init(void)
{
	status_t SBC_SPI_status = STATUS_SUCCESS;

	// SPI port initialization
	SBC_SPI_status = LPSPI_DRV_MasterInit(LPSPI1_CAN, &lpspi1_canState, &lpspi1_can_MasterConfig0);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}

	SBC_SPI_status = LPSPI_DRV_MasterSetDelay(LPSPI1_CAN, 1u, 1u, 1u);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}

	INT_SYS_SetPriority(LPSPI1_IRQn, 15u);

	/* Read the family and product identification register */
	SBC_write_register.field.address = PRODUCT_INFO_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = READ_REG;
	SBC_write_register.field.data = 0u;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}
	if( SBC_read_register.field.data != SBC_TLE9261QX_ID )
	{
		// Wrong family and product identifier
		return false;
	}

	/* SBC Control Register Configuration */
	SBC_write_register.field.address = MODE_SUPPLY_CONTROL_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = WRITE_REG;
	SBC_write_register.field.data = MODE_SUPPLY_CONTROL_CONFIG_BYTE;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}
	if( SBC_write_register.field.data != SBC_read_register.field.data )
	{
		return false;
	}

	SBC_write_register.field.address = HARDWARE_CONTROL_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = WRITE_REG;
	SBC_write_register.field.data = HARDWARE_CONTROL_CONFIG_BYTE;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}
	if( SBC_write_register.field.data != SBC_read_register.field.data )
	{
		return false;
	}

	SBC_write_register.field.address = WATCHDOG_CONTROL_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = WRITE_REG;
	SBC_write_register.field.data = WATCHDOG_CONTROL_CONFIG_BYTE;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}
	if( SBC_write_register.field.data != SBC_read_register.field.data )
	{
		return false;
	}

	SBC_write_register.field.address = BUS_CONTROL_1_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = WRITE_REG;
	SBC_write_register.field.data = BUS_CONTROL_1_CONFIG_BYTE;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}
	if( SBC_write_register.field.data != SBC_read_register.field.data )
	{
		return false;
	}

	/* Read bus communication status register */
	SBC_write_register.field.address = BUS_STATUS_REG_ADDRESS;
	SBC_write_register.field.register_access_mode = READ_REG;
	SBC_write_register.field.data = 0u;
	SBC_SPI_status = LPSPI_DRV_MasterTransferBlocking(LPSPI1_CAN, (uint8_t *)&SBC_write_register.control_word, (uint8_t *)&SBC_read_register.status_word, sizeof(uint16_t), 100);
	if( SBC_SPI_status != STATUS_SUCCESS )
	{
		return false;
	}

	return true;
}




