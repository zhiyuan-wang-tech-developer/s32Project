/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : can_pal0.h
**     Project     : AutoLivTest
**     Processor   : S32K144_64
**     Component   : can_pal
**     Version     : Component SDK_S32K14x_09, Driver 01.00, CPU db: 3.00.000
**     Repository  : SDK_S32K14x_09
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-11-06, 13:12, # CodeGen: 65
**     Contents    :
**         CAN_Init                 - status_t CAN_Init(can_instance_t instance, const can_user_config_t *config);
**         CAN_Deinit               - status_t CAN_Deinit(can_instance_t instance);
**         CAN_SetBitrate           - status_t CAN_SetBitrate(can_instance_t instance, can_bitrate_phase_t phase,...
**         CAN_GetBitrate           - status_t CAN_GetBitrate(can_instance_t instance, can_bitrate_phase_t phase,...
**         CAN_ConfigTxBuff         - status_t CAN_ConfigTxBuff(can_instance_t instance, uint32_t buffIdx, const...
**         CAN_ConfigRxBuff         - status_t CAN_ConfigRxBuff(can_instance_t instance, uint32_t buffIdx, const...
**         CAN_Send                 - status_t CAN_Send(can_instance_t instance, uint32_t buffIdx, const...
**         CAN_SendBlocking         - status_t CAN_SendBlocking(can_instance_t instance, uint32_t buffIdx, const...
**         CAN_Receive              - status_t CAN_Receive(can_instance_t instance, uint32_t buffIdx, can_message_t...
**         CAN_ReceiveBlocking      - status_t CAN_ReceiveBlocking(can_instance_t instance, uint32_t buffIdx,...
**         CAN_SetRxFilter          - status_t CAN_SetRxFilter(can_instance_t instance, can_msg_id_type_t idType,...
**         CAN_GetTransferStatus    - status_t CAN_GetTransferStatus(can_instance_t instance, uint32_t buffIdx);
**         CAN_InstallEventCallback - status_t CAN_InstallEventCallback(can_instance_t instance, can_callback_t...
**
**     Copyright 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All Rights Reserved.
**     
**     THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
**     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
**     OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
**     IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
**     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**     SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
**     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
**     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
**     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
**     THE POSSIBILITY OF SUCH DAMAGE.
** ###################################################################*/
/*!
** @file can_pal0.h
** @version 01.00
*/
/*!
**  @addtogroup can_pal0_module can_pal0 module documentation
**  @{
*/
#ifndef can_pal0_H
#define can_pal0_H

/* MODULE can_pal0. */

/* Include inherited beans */
#include "clockManager1.h"
#include "dmaController1.h"
#include "Cpu.h"

/*! @brief Device instance number */
#define INST_CAN_PAL0 (0U)

extern const can_user_config_t can_pal0_Config0;

#endif
/* ifndef __can_pal0_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/

