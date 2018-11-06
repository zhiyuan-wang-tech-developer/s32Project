/*
 * can_bus.c
 *
 *  Created on: Nov 5, 2018
 *      Author: dynatron2018
 */

#include "Cpu.h"
#include "can_bus.h"
#include "stdio.h"

#define CAN_MESSAGE_ID			0x555u
#define CAN_RX_BUFFER_INDEX		0u
#define CAN_TX_BUFFER_INDEX		1u

// Private members
static CAN_TRANSCEIVER_STATUS_t can_transceiver_status = CAN_INITIALIZE;

static const can_buff_config_t can_buffer_configure =
	{
			.enableFD = false,					// Disable Flexible Data rate
			.enableBRS = false,					// Disable Bit Rate Switch
			.fdPadding = 0u,
			.idType = CAN_MSG_ID_STD,
			.isRemote = false
	};

// Public members
/*
 * The standard CAN ID has 11 bits with the range from 0x000 to 0x7FF.
 */
const uint32_t can_message_ID = CAN_MESSAGE_ID; // for easy observation on oscilloscope

can_message_t  rx_message =
	{
			.cs = 0u,
			.id = 0u,
			.data = {0u},
			.length = 0u
	};

/* Dummy TX message */
can_message_t tx_message =
	{
			.cs = 0u,
			.id = CAN_MESSAGE_ID,
			.data = {"allround"},
			.length = 8u
	};

/*
 * Every 1 sec, this flag is set by the lpit1 ISR handler
 */
bool CAN_TimeToTransmit = false;

/*
 * Every time when a CAN message is received, this flag is set by the CAN_TX_RX_Callback()
 */
bool CAN_TimeToProcessRxMsg = false;

// Private function prototype
void CAN_TX_RX_Callback(uint32_t can_instance, can_event_t can_event_type, uint32_t msg_buffer_index, void* can_state);

/*
 * @brief: initialize the on-chip CAN module and the system basis chip TLE9261QX
 */
bool CAN_communication_init(void)
{
	status_t can_status = STATUS_SUCCESS;
	/* Initialize the CAN module */
	can_status = CAN_Init(INST_CAN_PAL0, &can_pal0_Config0);
	if( can_status != STATUS_SUCCESS )
	{
		return false;
	}

	/* Configure RX buffer */
	can_status = CAN_ConfigRxBuff(INST_CAN_PAL0, CAN_RX_BUFFER_INDEX, &can_buffer_configure, can_message_ID);
	if( can_status != STATUS_SUCCESS )
	{
		return false;
	}

	/* Configure TX buffer */
	can_status = CAN_ConfigTxBuff(INST_CAN_PAL0, CAN_TX_BUFFER_INDEX, &can_buffer_configure);
	if( can_status != STATUS_SUCCESS )
	{
		return false;
	}

	INT_SYS_SetPriority(CAN0_ORed_0_15_MB_IRQn, 10);
	CAN_InstallEventCallback(INST_CAN_PAL0, CAN_TX_RX_Callback, NULL);
	return true;
}

/*
 * @brief: The CAN transmitter + receiver state machine
 * 			If a CAN message is received, the message will be printed on console.
 * 			Every 1 sec, a CAN dummy message will be sent out to CAN bus.
 */
void CAN_transceiver_run(void)
{
	static status_t can_status = STATUS_SUCCESS;

	switch (can_transceiver_status)
	{
		case CAN_INITIALIZE:
			CAN_TimeToTransmit = false;
			CAN_TimeToProcessRxMsg = false;
			can_transceiver_status = CAN_WAIT;
			can_status = STATUS_SUCCESS;
			break;

		case CAN_WAIT:
			if( CAN_TimeToTransmit )
			{
				can_transceiver_status = CAN_TRANSMIT;
			}

			if( CAN_TimeToProcessRxMsg )
			{
				can_transceiver_status = CAN_PROCESS_RX_MSG;
			}

			can_status = CAN_GetTransferStatus(INST_CAN_PAL0, CAN_RX_BUFFER_INDEX);
			if( can_status == STATUS_SUCCESS )
			{
				can_transceiver_status = CAN_RECEIVE;
			}

			can_transceiver_status = CAN_WAIT;
			break;

		case CAN_TRANSMIT:
			CAN_Send(INST_CAN_PAL0, CAN_TX_BUFFER_INDEX, &tx_message);
			CAN_TimeToTransmit = false;
			can_transceiver_status = CAN_WAIT;
			break;

		case CAN_RECEIVE:
			CAN_Receive(INST_CAN_PAL0, CAN_RX_BUFFER_INDEX, &rx_message);
			can_transceiver_status = CAN_WAIT;
			break;

		case CAN_PROCESS_RX_MSG:
			printf("RX: A CAN MSG\r\n");

			CAN_TimeToProcessRxMsg = false;
			can_transceiver_status = CAN_WAIT;
			break;

		default:
			can_transceiver_status = CAN_INITIALIZE;
			break;
	}
}

void CAN_TX_RX_Callback(uint32_t can_instance, can_event_t can_event_type, uint32_t msg_buffer_index, void* can_state)
{
	if(can_event_type == CAN_EVENT_RX_COMPLETE)
	{
		CAN_TimeToProcessRxMsg = true;
	}
}

