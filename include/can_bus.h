/*
 * can_bus.h
 *
 *  Created on: Nov 5, 2018
 *      Author: dynatron2018
 */

#ifndef CAN_BUS_H_
#define CAN_BUS_H_

#include "stdint.h"
#include "stdbool.h"

typedef enum
{
	CAN_INITIALIZE = 1u,
	CAN_WAIT,
	CAN_TRANSMIT,
	CAN_RECEIVE,
	CAN_PROCESS_RX_MSG
} CAN_TRANSCEIVER_STATUS_t;

// Public variable
extern bool CAN_TimeToTransmit;

// Public function prototypes
bool CAN_communication_init(void);
void CAN_transceiver_run(void);

#endif /* CAN_BUS_H_ */
