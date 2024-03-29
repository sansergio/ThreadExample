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
#ifndef _MAC_ABS_802154_H
#define _MAC_ABS_802154_H
/*!=================================================================================================
\file       mac_abs_802154.h
\brief      This is a header file for the MAC abstraction module.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/

#include "mac_abs_types.h"

/*==================================================================================================
Public macros
==================================================================================================*/

/*==================================================================================================
Public type definitions
==================================================================================================*/

/*==================================================================================================
Public global variables declarations
==================================================================================================*/

/*==================================================================================================
Public function prototypes
==================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif


/*!*************************************************************************************************
\fn    instanceId_t MAC_RegisterAbsCb_802154(instanceId_t macInstanceId)
\brief Public interface function for the MAC abstraction module. This function initializes the
       internal MAC callbacks structure and returns the pointer to the Mac Abstraction Requests
       structure.

\param[in]  nwkId  The instance of the upper layer ( NWK layer)
\param[out]  nwkId  The instance of the MAC layer (output param)

\retval      macAbsRequests_t       pointer address to the Mac Abstraction Requests
***************************************************************************************************/
macAbsRequests_t* MAC_RegisterAbsCb_802154
(
    instanceId_t nwkInstanceId, //IN
    instanceId_t* pMacInstanceId //OUT
);

#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _MAC_ABS_802154_H */
