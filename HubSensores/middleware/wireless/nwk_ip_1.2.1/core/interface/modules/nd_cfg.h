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

#ifndef _ND_CFG_H
#define _ND_CFG_H

/*==================================================================================================
Include Files
==================================================================================================*/

#include "EmbeddedTypes.h"
#include "app_stack_config.h"

/*==================================================================================================
Public macros
==================================================================================================*/

/* Default Values */

/*! Maximum number of entries in the neighbor cache */
#ifndef ND_NEIGHBOR_CACHE_SIZE
    #define ND_NEIGHBOR_CACHE_SIZE       10
#endif

/*! Maximum number of entries in the Prefix list */
#ifndef ND_PREFIX_LIST_SIZE
    #define ND_PREFIX_LIST_SIZE          4
#endif

/*! Maximum number of entries in the Route Information list */
#ifndef ND_ROUTE_INFO_LIST_SIZE
    #define ND_ROUTE_INFO_LIST_SIZE      4
#endif

/*! Maximum number of entries in the RDNSS list */
#ifndef ND_RDNSS_LIST_SIZE
    #define ND_RDNSS_LIST_SIZE           4
#endif

/*! Maximum number of entries in the Destination Cache */
#ifndef ND_DESTINATION_CACHE_SIZE
    #define ND_DESTINATION_CACHE_SIZE    4
#endif

/* Configuration macros consistency checks. */

#if ND_NEIGHBOR_CACHE_SIZE  < 1
    #error ND_NEIGHBOR_CACHE_SIZE should be > 0
#endif

#if ND_PREFIX_LIST_SIZE < 1
    #error ND_PREFIX_LIST_SIZE should be > 0
#endif

#if ND_ROUTE_INFO_LIST_SIZE < 1
    #error ND_ROUTE_INFO_LIST_SIZE should be > 0
#endif

#if ND_RDNSS_LIST_SIZE < 1
    #error ND_RDNSS_LIST_SIZE should be > 0
#endif

#if ND_DESTINATION_CACHE_SIZE < 1
    #error ND_DESTINATION_CACHE_SIZE should be > 0
#endif



/*! Description of the ND_DAD_TRANSMITS configuration option: The number of consecutive Neighbor
    Solicitation messages sent while performing Duplicate Address Detection on a tentative address.
    A value of zero indicates that Duplicate Address Detection is not performed on tentative
    addresses. A value of one indicates a single transmission with no follow-up retransmissions. */
#ifndef ND_DAD_TRANSMITS
    #define ND_DAD_TRANSMITS (1U)
#endif


/*! Description of the ND_LIFETIME_GUARD_INTERVAL configuration option: The amount of time in seconds
    before a context/prefix expires to send an RS */
#ifndef ND_LIFETIME_GUARD_INTERVAL
    #define ND_LIFETIME_GUARD_INTERVAL (10U)
#endif

/*! Description of the ND_REG_ADDRESS_GUARD_TIME configuration option: The amount of time in seconds
    before an address registration expires to send an NS with ARO */
#ifndef ND_REG_ADDRESS_GUARD_TIME
    #define ND_REG_ADDRESS_GUARD_TIME (10U)
#endif

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


#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _ND_CFG_H */
