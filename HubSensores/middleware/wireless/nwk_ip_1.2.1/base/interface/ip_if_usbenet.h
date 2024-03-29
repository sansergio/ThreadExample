/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#ifndef _IP_IF_USBENET_H
#define _IP_IF_USBENET_H
/*!=================================================================================================
\file       ip_if_usbenet.h
\brief      This is a header file for the Media interface to USB Ethernet (RNDIS)
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include <stdint.h>
#include "ip.h"

/*==================================================================================================
Public macros
==================================================================================================*/


/*==================================================================================================
Public type definitions
==================================================================================================*/


/*==================================================================================================
Public global variables declarations
==================================================================================================*/

extern const mediaIfStruct_t* gUsbEnetMediaIfPtr;

/*==================================================================================================
Public function prototypes
==================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif
/*!*************************************************************************************************
\fn void USBENET_Initialize(void)
\brief  Initialize RNDIS module

\param [in]  void

\retval      void
***************************************************************************************************/
void USBENET_Initialize(void);

/*!*************************************************************************************************
\fn uint32_t IP_UsbEnetDisable(void)
\brief  Disable Usb enet Interface

\param [in]  void

\retval      void
***************************************************************************************************/

void IP_UsbEnetDisable(void);
/*!*************************************************************************************************
\fn uint32_t IP_UsbEnetEnable(void)
\brief  Enable Usb enet Interface

\param [in]  void

\retval      void
***************************************************************************************************/
void IP_UsbEnetEnable(void);


#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /*_IP_IF_USBENET_H */
