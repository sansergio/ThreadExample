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
/*!
**  @addtogroup nwk_ip_evm
**  @{
*/

#ifndef _EVENT_MANAGER_H
#define _EVENT_MANAGER_H

/*!=================================================================================================
\file       event_manager.h
\brief      This is a header file for the event_manager module.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/

#include "EmbeddedTypes.h"
#include "stack_config.h"
#include "network_utils.h"

/*==================================================================================================
Public macros
==================================================================================================*/

/*! Macro used to specify any instance Id */
#define gEvmAnyInstanceId_c  THR_ALL_FFs32
/*==================================================================================================
Public type definitions
==================================================================================================*/

/*! Event Manager Registered Modules */
typedef enum
{
    gEvmModule6LoWPAN_c = 0x01000000,
    gEvmModuleNd_c      = 0x02000000,
    gEvmModuleThread_c  = 0x03000000
} evmModules_t;

/*! Event Manager Callback */
typedef void (*pfFunction_t)(void* pEvent);

/*! Event Manager table entry */
typedef struct eventManagerEntry_tag
{
    uint32_t code;                  /* Event Code */
    pfFunction_t pfFunction;        /* Pointer to the callback function */
    taskMsgQueue_t **ppMsgQueue;    /* Pointer to the task message queue the event will be sent to */
    instanceId_t instanceId;        /* Instance Id of the module which is registered to the event */
    bool_t bNotifyAsync;            /* Type of event notification: TRUE  - An OS message will be sent
                                                                   FALSE - Function will be called directly */
} eventManagerEntry_t;

/*! Event Parameters Header */
typedef struct evmParams_tag
{
    uint32_t code;                  /* Event Code */
    uint32_t instanceId;            /* Instance Id */
    uint16_t buffSize;              /* Event Data Size */
    uint16_t reserved;              /* Reserved for future use */
    uint8_t* pBuff;                 /* Event Data */
} evmParams_t;

/*==================================================================================================
Public global variables declarations
==================================================================================================*/

/*! Event Manager Events Table */
extern eventManagerEntry_t * aEventsTable[];
extern const uint32_t eventsTableSize;

extern const eventManagerEntry_t aStaticEventsTable[];
extern const uint16_t aStaticEventsTableSize;

/* monitoring function */
extern pfFunction_t pfEventMonitoringFunction;

/*==================================================================================================
Public function prototypes
==================================================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*!*************************************************************************************************
\fn     void EVM_EventNotify(uint32_t code, void *pEventData, uint16_t dataSize, instanceId_t instanceId)
\brief  Notifies the event manager of an event that occurred.

\param  [in]  code        Event code
\param  [in]  pEventData  Pointer to the event data. NOTE: Should be pointer a to static data not
                          dynamically allocated memory. The Event manager module will NOT free it.
\param  [in]  dataSize    The size in bytes of the event data
\param  [in]  instanceId  Instance Id of the module that is signaling the event
                          Possible values: - instance Id value (if the module has an instance Id)
                                           - gEvmAnyInstanceId_c (if the module does not have an instance Id)
***************************************************************************************************/
void EVM_EventNotify(uint32_t code, void *pEventData, uint16_t dataSize, instanceId_t instanceId);

/*!*************************************************************************************************
\fn     bool_t EVM_RegisterDynamic(uint32_t code, pfFunction_t pfFunction, taskMsgQueue_t ** ppMsgQueue,
                                   instanceId_t instanceID, bool_t bNotifyAsync)
\brief  Registers listening for an event dynamically(at run time).

\param  [in]  code          Event code (single event) / event set code (multiple events)
\param  [in]  pfFunction    Callback function for event
\param  [in]  ppMsgQueue    Task message queue to use for the callback function
\param  [in]  instanceId    Instance Id of the module which is providing the event. Use gEvmAnyInstanceId_c
                            to be notified for all instance Ids
\param  [in]  bNotifyAsync  If TRUE the notification callback function will be called asynchronously
                            by sending a message to the provided task message queue.

\retval       bool_t        TRUE if success
                            FALSE otherwise
***************************************************************************************************/
bool_t EVM_RegisterDynamic(uint32_t code, pfFunction_t pfFunction, taskMsgQueue_t ** ppMsgQueue,
                           instanceId_t instanceID, bool_t bNotifyAsync);

/*!*************************************************************************************************
\fn     void EVM_Unregister(uint32_t code, pfFunction_t pfFunction)
\brief  Unregisters listening for an event dinamically(at run time).

\param  [in]  code        Event code
\param  [in]  pfFunction  Callback function for event
***************************************************************************************************/
void EVM_Unregister(uint32_t code, pfFunction_t pfFunction);

#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _EVENT_MANAGER_H */
/*!
** @}
*/
