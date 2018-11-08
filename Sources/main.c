/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"
#include "stdio.h"
#include "string.h"
#include "systemRunFsm.h"
#include "adc.h"
#include "dac.h"
#include "can_bus.h"
#include "system_basis_chip_TLE9261.h"

volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

//const uint8_t uartText[9] = "allround\n";
uint8_t uartTxBuffer[9] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
//uint8_t uartTxBuffer[9] = {'\0'};

// Function Prototypes
bool setTxSampleRate(uint16_t rate);
void TogglePTD5(void);
void TogglePTD6(void);

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/
int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
    SystemInit();

    if( CLOCK_DRV_Init(&clockManager1_InitConfig0) != STATUS_SUCCESS )
	{
//    	printf("Error\n");
    	return exit_code;
	}

    if( PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr) != STATUS_SUCCESS )
    {
//    	printf("Error\n");
    }

    /*
     * You can replace the default IRQ handler with a new IRQ handler when the vector table is in RAM.
     * If the vector table is in FLASH, the INT_SYS_InstallHandler() is not applicable.
     */
//    INT_SYS_InstallHandler(LPTMR0_IRQn, TogglePTD6, (isr_t *) NULL);

    INT_SYS_EnableIRQGlobal();

    LPTMR_DRV_Init(INST_LPTMR1, &lpTmr1_config0, false);

    INT_SYS_SetPriority(LPTMR0_IRQn, 5);

    if( !INT_SYS_GetActive(LPTMR0_IRQn) )
    {
    	INT_SYS_ClearPending(LPTMR0_IRQn);
    	INT_SYS_EnableIRQ(LPTMR0_IRQn);
    }

    PINS_DRV_ClearPins(PTD, 1<<6);

    setTxSampleRate(1260); // Adjustable Tx sample rate: 1222 - 1280

    if( !LPTMR_DRV_IsRunning(INST_LPTMR1) )
    {
    	LPTMR_DRV_StartCounter(INST_LPTMR1);
    }

    uint32_t lpTimerFreq = 0;
    if( CLOCK_DRV_GetFreq(LPTMR0_CLK, &lpTimerFreq) == STATUS_SUCCESS )
    {
//    	printf("Low Power Timer Frequency: %lu\r\n", lpTimerFreq);
    }

    LPIT_DRV_Init(INST_LPIT1, &lpit1_InitConfig);
    LPIT_DRV_InitChannel(INST_LPIT1, 0, &lpit1_ChnConfig0);
//    INT_SYS_InstallHandler(LPIT0_Ch0_IRQn, TogglePTD5, (isr_t *) NULL);
    INT_SYS_SetPriority(LPIT0_Ch0_IRQn, 15);

    if(!INT_SYS_GetActive(LPIT0_Ch0_IRQn))
    {
    	INT_SYS_ClearPending(LPIT0_Ch0_IRQn);
    	INT_SYS_EnableIRQ(LPIT0_Ch0_IRQn);
    }

    LPIT_DRV_StartTimerChannels(INST_LPIT1, 0x01U);

   if( LPUART_DRV_Init(INST_LPUART0, &lpuart0_State, &lpuart0_InitConfig0) != STATUS_SUCCESS )
   {
//	   printf("Error\n");
   }
//   INT_SYS_SetPriority(LPUART0_RxTx_IRQn, 8);
//   INT_SYS_ClearPending(LPUART0_RxTx_IRQn);
//   INT_SYS_EnableIRQ(LPUART0_RxTx_IRQn);

   /* LPSPI0 Initialization */
   LPSPI0_init();						/* Initialize the LPSPI0 for ADC */
   LPSPI2_init();						/* Initialize the LPSPI2 for DAC */
   set_DAC(dac_val_16, true);			/* Set the initial DAC output */
   ADC_init();							/* Configure the ADC */
   SBC_Init();							/* Configure the System Basis Chip */
   CAN_communication_init();

   /* For example: for(;;) { } */

   for(;;)
   {
	   fsm_task_run();
	   CAN_transceiver_run();
//	  PINS_DRV_TogglePins(PTE, 1<<8);
//	  PINS_DRV_TogglePins(PTD, 1<<6);
//	  PINS_DRV_TogglePins(PTD, 1<<5);
//	  PINS_DRV_TogglePins(PTD, 1<<7);
//    	countfor = LPIT_DRV_GetCurrentTimerCount(INST_LPIT1, 0);
   }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/


/*
 * Overwrite the interrupt handler
 */
/*
 * @brief: The low power interrupt timer 0 channel 0 generates 1s timing interrupt.
 */
void LPIT0_Ch0_IRQHandler(void)
{
	// 1s timing
	static uint16_t sec_counter = 0;

	// Clear interrupt flag first
	if( LPIT_DRV_GetInterruptFlagTimerChannels(INST_LPIT1, 0x01u) )
	{
		LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT1, 0x01u);
	}

	// Second counting
	sec_counter %= 15;	// every 15 seconds the counter is cleared
	if( sec_counter == 0 )
	{
		uart_sync ^= 0x80;		/* Toggle uart_sync MSB bit */
	}
	sec_counter++;

	// Send CAN message every second
	if( !CAN_TimeToTransmit )
	{
		CAN_TimeToTransmit = true;
	}

	// Toggle LED 1
	PINS_DRV_TogglePins(PTE, 1<<8);
}

/*
 * @brief: The low power timer 0 generates 793.65us timing interrupt.
 */
void LPTMR0_IRQHandler(void)
{
	// 793.65us timing

	// Clear interrupt flag first
	if( LPTMR_DRV_GetCompareFlag(INST_LPTMR1) )
	{
		// MUST clear compare flag, otherwise program will get stuck in the lptmr0 ISR handler.
		LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
		LPTMR_DRV_SetInterrupt(INST_LPTMR1, false); // Disable the timer interrupt to prevent possible nested interrupt.
	}

	// Check if the state machine is copying uart data to uart tx buffer
	if( uart_tx_buffer_mutex == false )
	{
		uart_tx_buffer_mutex = true;
		// The state machine now can not access the uart tx buffer
//		LPUART_DRV_SendDataPolling(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer));
		LPUART_DRV_SendDataBlocking(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer), 10);
		uart_tx_buffer_mutex = false;
//		PINS_DRV_TogglePins(PTD, 1<<6); 	// used for waveform observation
	}
	else
	{
		// The uart tx buffer is now being accessed by the state-machine.
		// The uart tx buffer is now being copied.
		// Here, you can send the uart data array directly and safely
//		LPUART_DRV_SendDataPolling(INST_LPUART0, &(uart_data.array[0]), sizeof(uart_data.array));
		LPUART_DRV_SendDataBlocking(INST_LPUART0, &(uart_data.array[0]), sizeof(uart_data.array), 10);
//		PINS_DRV_TogglePins(PTD, 1<<5);
	}
	LPTMR_DRV_SetInterrupt(INST_LPTMR1, true); // Enable the interrupt again
}

/*
 * @brief:
 * available TX sample rate range = 1222 ~ 1280
 */
bool setTxSampleRate(uint16_t rate)
{
	if( (rate < 1222) || (rate > 1280) )
	{
		return false;
	}
	float tickUnit = 0.0125; // us
	float samplePeriod = (1000000.0 / (float) rate); // us
	uint16_t cmpValue = (uint16_t) (samplePeriod / tickUnit); // calculate low power timer compare value
	if( LPTMR_DRV_SetCompareValueByCount(INST_LPTMR1, cmpValue) == STATUS_SUCCESS )
	{
		return true;
	}
	return false;
}

/*
 * @brief: TogglePTD5 and TogglePTD6 for RAM debugging
 * 		   Both functions are registered into the vector table in RAM by INT_SYS_InstallHandler().
 * 		   They can not be registered if the vector table is in FLASH.
 */
void TogglePTD5 (void)
{
	// 1s timing
	static uint16_t sec_counter = 0;
	if( LPIT_DRV_GetInterruptFlagTimerChannels(INST_LPIT1, 0x01u) )
	{
		LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT1, 0x01u);
	}
	sec_counter %= 15;	// every 15 seconds the counter is cleared
	if( sec_counter == 0 )
	{
		uart_sync ^= 0x80;		/* Toggle uart_sync MSB bit */
	}
	sec_counter++;

	if( !CAN_TimeToTransmit )
	{
		CAN_TimeToTransmit = true;
	}
//	countTxSamplePerSec = countTxSample;
//	countTxSample = 0;
//	printf("Tx Sample Rate: %lu\n", countTxSamplePerSec);

//	LPUART_DRV_SendDataPolling(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer));
}


void TogglePTD6 (void)
{
	// 792us timing
	if( LPTMR_DRV_GetCompareFlag(INST_LPTMR1) )
	{
		// MUST clear compare flag, otherwise program will get stuck in the lptmr0 ISR.
		LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
		LPTMR_DRV_SetInterrupt(INST_LPTMR1, false); // Disable the timer interrupt to prevent possible nested interrupt.
	}
//	static uint8_t countTxDummy = 0; // count dummy texts that are transmitted when the uart tx buffer is accessed by the state-machine

//	LPUART_DRV_SendDataPolling(INST_LPUART0, uartText, sizeof(uartText));
//	LPUART_DRV_SendDataBlocking(INST_LPUART0, uartText, sizeof(uartText), 10);
//	LPUART_DRV_SendData(INST_LPUART0, uartText, sizeof(uartText));

//	LPUART_DRV_SendDataPolling(INST_LPUART0, uart_data.array, sizeof(uart_data.array));
//	LPUART_DRV_SendData(INST_LPUART0, uart_data.array, sizeof(uart_data.array));

//	LPUART_DRV_SendDataPolling(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer));

	// Check if the state machine is copying uart data to uart tx buffer
	if(uart_tx_buffer_mutex == false)
	{
		uart_tx_buffer_mutex = true;
		// The state machine now can not access the uart tx buffer
//		LPUART_DRV_SendDataPolling(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer));
		LPUART_DRV_SendDataBlocking(INST_LPUART0, uartTxBuffer, sizeof(uartTxBuffer), 10);
		uart_tx_buffer_mutex = false;
		PINS_DRV_TogglePins(PTD, 1<<6); 	// used for waveform observation
	}
	else
	{
		// The uart tx buffer is now being accessed by the state-machine.
		// The uart tx buffer is now being copied.
//		++countTxDummy;
		// Here, you can send the uart data array directly and safely
//		LPUART_DRV_SendDataPolling(INST_LPUART0, &(uart_data.array[0]), sizeof(uart_data.array));
		LPUART_DRV_SendDataBlocking(INST_LPUART0, &(uart_data.array[0]), sizeof(uart_data.array), 10);
		PINS_DRV_TogglePins(PTD, 1<<5);
	}
	LPTMR_DRV_SetInterrupt(INST_LPTMR1, true); // Enable the interrupt again
}


/* END main */
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
