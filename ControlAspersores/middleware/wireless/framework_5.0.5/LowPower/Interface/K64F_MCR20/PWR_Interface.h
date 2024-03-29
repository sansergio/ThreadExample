/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file PWR_Interface.h
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef _PWR_INTERFACE_H_
#define _PWR_INTERFACE_H_

/*****************************************************************************
 *                               INCLUDED HEADERS                            *
 *---------------------------------------------------------------------------*
 * Add to this section all the headers that this module needs to include.    *
 * Note that it is not a good practice to include header files into header   *
 * files, so use this section only if there is no other better solution.     *
 *---------------------------------------------------------------------------*
 *****************************************************************************/
#include "EmbeddedTypes.h"

#ifdef __cplusplus
    extern "C" {
#endif

/*****************************************************************************
 *                             PRIVATE MACROS                                *
 *---------------------------------------------------------------------------*
 * Add to this section all the access macros, registers mappings, bit access *
 * macros, masks, flags etc ...                                              *
 *---------------------------------------------------------------------------*
 *****************************************************************************/


/*****************************************************************************
 *                             PUBLIC MACROS                                 *
 *---------------------------------------------------------------------------*
 * Add to this section all the access macros, registers mappings, bit access *
 * macros, masks, flags etc ...                                              *
 *---------------------------------------------------------------------------*
 *****************************************************************************/
#ifndef gAllowDeviceToSleep_c
#define gAllowDeviceToSleep_c 0
#endif
   
/* Zigbee stack interface functions */
/******************************************************************************
* Description : Macros to get the current status of the STACK
* Assumptions : None
* Inputs      : None
* Output      : Status from PWRLib_StackPS
* Errors      : Not handled
******************************************************************************/
#define PWRLib_GetCurrentZigbeeStackPowerState      PWRLib_StackPS


/******************************************************************************
* Description : Macro to set the status of the STACK
* Inputs      : NewStackPS  : New state
*               StackPS_Running   : Busy
*               StackPS_Sleep     : Sleep allowed. Duration is appl. specific
*               StackPS_DeepSleep : DeepSleep allowed
* Output      : None
* Errors      : Not handled
******************************************************************************/
#define PWRLib_SetCurrentZigbeeStackPowerState( NewStackPS)  PWRLib_StackPS = NewStackPS;

/*****************************************************************************
 *                        PUBLIC TYPE DEFINITIONS                            *
 *---------------------------------------------------------------------------*
 * Add to this section all the data types definitions: stuctures, unions,    *
 * enumerations, typedefs ...                                                *
 *---------------------------------------------------------------------------*
 *****************************************************************************/


/* 
 * Name: PWRLib_WakeupReason_t
 * Description: Wakeup reason UNION definitions
 */
typedef  union {
  uint8_t AllBits;
  struct {
    uint8_t   FromReset        :1;                // Comming from Reset
    uint8_t   FromUART         :1;                // Wakeup by UART interrupt
    uint8_t   FromKeyBoard     :1;                // Wakeup by TSI/Push button interrupt
    uint8_t   FromLPTMR        :1;                // Wakeup by LPTMR timer interrupt
    uint8_t   FromRTC          :1;                // Wakeup by RTC timer interrupt
    uint8_t   FromTimer        :1;                // Wakeup by Radio Timer
    uint8_t   DeepSleepTimeout :1;                // DeepSleep timer ran out
    uint8_t   SleepTimeout     :1;                // Sleep timer ran out
  } Bits;
} PWRLib_WakeupReason_t;

/* 
 * Name: PWRLib_StackPS_t
 * Description: Zigbee stack power state
 */
typedef enum{
  StackPS_Running=122,
  StackPS_Sleep,
  StackPS_DeepSleep
} PWRLib_StackPS_t;

/* 
 * Name: PWRLib_LVD_VoltageLevel_t
 * Description: Reported voltage levels. LEVEL_BEST is the highest, corespondig to > 3.0V
 */
typedef enum{
  PWR_ABOVE_LEVEL_3_0V,    // > 3.0 V
  PWR_BELOW_LEVEL_3_0V,
  PWR_BELOW_LEVEL_2_9V,
  PWR_BELOW_LEVEL_2_8V,
  PWR_BELOW_LEVEL_2_7V,
  PWR_BELOW_LEVEL_2_56V,
  PWR_BELOW_LEVEL_2_1V,
  PWR_BELOW_LEVEL_2_0V,
  PWR_BELOW_LEVEL_1_9V,
  PWR_BELOW_LEVEL_1_8V,
  PWR_LEVEL_CRITICAL // < 1.6 V
} PWRLib_LVD_VoltageLevel_t;

/*****************************************************************************
 *                        PUBLIC VARIABLES                            *
 *---------------------------------------------------------------------------*
 * Add to this section all the data types definitions: stuctures, unions,    *
 * enumerations, typedefs ...                                                *
 *---------------------------------------------------------------------------*
 *****************************************************************************/

extern PWRLib_StackPS_t PWRLib_StackPS;
extern volatile PWRLib_WakeupReason_t PWRLib_MCU_WakeupReason;
/*****************************************************************************
 *                            PUBLIC FUNCTIONS                               *
 *---------------------------------------------------------------------------*
 * Add to this section all the global functions prototype preceded           *
 * by the keyword 'extern'                                                   *
 *---------------------------------------------------------------------------*
 *****************************************************************************/
 
/*---------------------------------------------------------------------------
 * Name: PWR_Init
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_Init
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWRLib_Init
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWRLib_Init
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWRLib_GetSystemResetStatus
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern uint16_t PWRLib_GetSystemResetStatus
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWR_AllowDeviceToSleep
 * Description: - This function is used to reset the global variable which 
 *                permits(on SET)/restricts(On RESET)the device to enter 
 *                low power state.
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_AllowDeviceToSleep
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWR_DisallowDeviceToSleep
 * Description: - This function is used to reset the global variable which 
 *                permits(on SET)/restricts(On RESET)the device to enter 
 *                low power state.
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_DisallowDeviceToSleep
(
  void
);
     
/*---------------------------------------------------------------------------
 * Name: PWR_DisallowXcvrToSleep
 * Description: - This function is used to reset the global variable which 
 *                permits(on SET)/restricts(On RESET)the device to enter 
 *                low power state.
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
void PWR_DisallowXcvrToSleep(void);

/*---------------------------------------------------------------------------
 * Name: PWR_AllowXcvrToSleep
 * Description: - This function is used to reset the global variable which 
 *                permits(on SET)/restricts(On RESET)the device to enter 
 *                low power state.
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
void PWR_AllowXcvrToSleep(void);

/*---------------------------------------------------------------------------
 * Name: PWR_CheckIfDeviceCanGoToSleep
 * Description: - This function is used to  Check  the Permission flag to go to 
 *                low power mode
 * Parameters: -
 * Return: - TRUE  : If the device is allowed to go to the LPM else FALSE
 *---------------------------------------------------------------------------*/
extern bool_t PWR_CheckIfDeviceCanGoToSleep
(
  void
);


/*---------------------------------------------------------------------------
 * Name: PWR_EnterPowerOff
 * Description: - Radio on Reset, MCU on VLLS1
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_EnterPowerOff(void);

/*---------------------------------------------------------------------------
 * Name: PWR_EnterLowPower
 * Description: - 
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern PWRLib_WakeupReason_t PWR_EnterLowPower
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWR_SetDeepSleepTimeInMs
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_SetDeepSleepTimeInMs
(
  uint32_t deepSleepTimeTimeMs
);

/*---------------------------------------------------------------------------
 * Name: PWR_SetDeepSleepTimeInSymbols
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWR_SetDeepSleepTimeInSymbols
(
  uint32_t deepSleepTimeTimeSym
);

/*---------------------------------------------------------------------------
 * Name: PWRLib_LVD_ReportLevel
 * Description: - 
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern PWRLib_LVD_VoltageLevel_t PWRLib_LVD_ReportLevel
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWRLib_Reset
 * Description: -
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
extern void PWRLib_Reset
(
  void
);

/*---------------------------------------------------------------------------
 * Name: PWR_EnterSleep
 * Description: - 
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
void PWR_EnterSleep
(
void
);

/*---------------------------------------------------------------------------
 * Name: PWR_GetDeepSleepMode
 * Description: - 
 * Parameters: -
 * Return: -
 *---------------------------------------------------------------------------*/
uint8_t PWR_GetDeepSleepMode
(
  void
);

#ifdef __cplusplus
}
#endif

#endif /* _PWR_INTERFACE_H_ */
