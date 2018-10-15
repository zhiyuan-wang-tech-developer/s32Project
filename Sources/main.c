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

volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */

uint32_t countTxSample = 0;
uint32_t countTxSamplePerSec = 0;

const uint8_t uartTxBuffer[9] = "allround\n";
//uint8_t uartTxBuffer[9] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
//uint8_t uartTxBuffer[9] = {'\0'};

void TogglePTD5 (void)
{
	if( LPIT_DRV_GetInterruptFlagTimerChannels(INST_LPIT1, 0x01u) )
	{
		LPIT_DRV_ClearInterruptFlagTimerChannels(INST_LPIT1, 0x01u);
	}
//	countTxSamplePerSec = countTxSample;
//	countTxSample = 0;
//	printf("Tx Sample Rate: %lu\n", countTxSamplePerSec);

//	PINS_DRV_TogglePins(PTE, 1<<8);

//	LPUART_DRV_SendDataPolling(INST_LPUART1, uartTxBuffer, sizeof(uartTxBuffer));

//	PINS_DRV_TogglePins(PTD, 1<<5);
}

//void LPTMR0_IRQHandler(void)
void TogglePTD6 (void)
{
	if( LPTMR_DRV_GetCompareFlag(INST_LPTMR1) )
	{
		// MUST clear compare flag, otherwise program will get stuck in the lptmr0 ISR.
		LPTMR_DRV_ClearCompareFlag(INST_LPTMR1);
	}
//	countTxSample++;
	PINS_DRV_TogglePins(PTD, 1<<6);
	LPUART_DRV_SendDataPolling(INST_LPUART1, uartTxBuffer, sizeof(uartTxBuffer));
}

// available tx sample rate range = 1222 ~ 1280
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
    	printf("Error\n");
    	return exit_code;
	}

    if( PINS_DRV_Init(NUM_OF_CONFIGURED_PINS, g_pin_mux_InitConfigArr) != STATUS_SUCCESS )
    {
    	printf("Error\n");
    }

    INT_SYS_InstallHandler(LPTMR0_IRQn, TogglePTD6, (isr_t *) NULL);

    INT_SYS_EnableIRQGlobal();

    LPTMR_DRV_Init(INST_LPTMR1, &lpTmr1_config0, false);

    INT_SYS_SetPriority(LPTMR0_IRQn, 10);

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
    INT_SYS_InstallHandler(LPIT0_Ch0_IRQn, TogglePTD5, (isr_t *) NULL);
    INT_SYS_SetPriority(LPIT0_Ch0_IRQn, 15);

    if(!INT_SYS_GetActive(LPIT0_Ch0_IRQn))
    {
    	INT_SYS_ClearPending(LPIT0_Ch0_IRQn);
    	INT_SYS_EnableIRQ(LPIT0_Ch0_IRQn);
    }

    LPIT_DRV_StartTimerChannels(INST_LPIT1, 0x01U);

   if( LPUART_DRV_Init(INST_LPUART1, &lpuart1_State, &lpuart1_InitConfig0) != STATUS_SUCCESS )
   {
	   printf("Error\n");
   }


   /* LPSPI0 Initialization */


  /* For example: for(;;) { } */

    for(;;)
    {
    	fsm_task_run();
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
