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


#ifndef _DHCP6_SERVER_H
#define _DHCP6_SERVER_H

/*!
\file       dhcp6_server.h
\brief      This is a public header file for the DHCPv6 Server module. 
*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "EmbeddedTypes.h"
#include "stack_config.h"

#include  "dhcp6.h"
#include  "ip.h"

#if IP_IP6_ENABLE
/*==================================================================================================
Public macros
==================================================================================================*/
#define DHCP6_DUID_LL_LEN          10U

/*==================================================================================================
Public type definitions
==================================================================================================*/
typedef enum
{
    gDhcp6AssignStateOffered_c,
    gDhcp6AssignStateAssigned_c
} dhcp6AssignState_t;

typedef struct dhcp6ServerBindingTbl_tag
{
    ipAddr_t ipAddr[DHCP6_MAX_IA_ADDRESSES];
    ipIfUniqueId_t ipIfId;
    uint32_t iaId;
    uint32_t leaseTime;
    uint32_t timestamp;
    uint8_t clientID[DHCP6_MAX_DEVICEID_LEN];
    uint32_t clientMode;
}dhcp6ServerBindingTbl_t;

typedef struct dhcp6ServerStartParams_tag
{
    ipIfUniqueId_t ipIfId;
    dhcp6ServerIpCfg_t** paServerIpCfg;
    ipAddr_t **paDnsCfg;
    uint16_t serverDeviceType;
}dhcp6ServerStartParams_t;

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
\fn     void DHCP6_Server_Init(taskMsgQueue_t *pTaskMsgQueue)
\brief  This function initializes the DHCPv6 Server module.

\param  [in]  pTaskMsgQueue  Pointer to the task message queue.
***************************************************************************************************/
void DHCP6_Server_Init(taskMsgQueue_t *pTaskMsgQueue);

/*!*************************************************************************************************
\fn     nwkStatus_t DHCP6_Server_Start(dhcp6ServerStartParams_t *pDhcp6StartParams)
\brief  This function starts the DHCPv6 Server module.

\param  [in]  pDhcp6StartParams  Pointer to start parameter structure, that contains:
                                   ifHandle         Double pointer to the interface.
                                   paServerIpCfg    Pointer to server's configuration structure.
                                   paDnsCfg         Pointer to DNS servers list.
                                   serverDeviceType The type of device.

\retval       status             TRUE -- The ip address of the DHCP server and the ip address pool
                                         were successfully set
                                 FALSE - An error occurred and the ip addresses were not set.
***************************************************************************************************/
nwkStatus_t DHCP6_Server_Start(dhcp6ServerStartParams_t *pDhcp6StartParams);

/*!*************************************************************************************************
\fn     dhcp6ServerBindingTbl_t * DHCP6_Server_GetClientByIdx(ifHandle_t* pIfHandle, uint32_t index)
\brief  Returns a client from the client table situated at "index" position.

\param  [in]  pIfHandle  Double pointer to the interface.
\param  [in]  index      Index

\return       pDhcp6ClientEntry  Returns the client entry.
****************************************************************************************************/
dhcp6ServerBindingTbl_t * DHCP6_Server_GetClientByIdx(ifHandle_t* pIfHandle, uint32_t index);

/*!*************************************************************************************************
\fn     void DHCP6_Server_Stop(ipIfUniqueId_t ipIfId)
\brief  This function stops the DHCPv6 Server module.

\param  [in]  ipIfId  IP interface identifier
***************************************************************************************************/
void DHCP6_Server_Stop(ipIfUniqueId_t ipIfId);

/*!*************************************************************************************************
\fn     void DHCP6_Server_RegisterRelayAg(dhcp6RelayAgCb_t pfRelayAgCb, ifHandle_t* pIfPtr)
\brief  This function registers the Relay Agent callback.

\param  [in]  pfRelayAgCb  Pointer to the RelayAgent callback.
\param  [in]  pIfPtr       Double pointer to the interface.
***************************************************************************************************/
void DHCP6_Server_RegisterRelayAg(dhcp6RelayAgCb_t pfRelayAgCb, ifHandle_t* pIfPtr);

/*!*************************************************************************************************
\fn     void DHCP6_Server_Send(dhcp6ClientTempBindingTbl_t * pServerTempTbl, dhcp6Packet_t *pDhcp6Pkt,
                               uint32_t dhcp6MsgSize)
\brief  This function sends a message to lower layers.

\param  [in]  pServerTempTbl  Pointer to client's structure
\param  [in]  pDhcp6Pkt       Pointer the message to be sent
\param  [in]  dhcp6MsgSize    The size of the message
***************************************************************************************************/
void DHCP6_Server_Send(dhcp6ClientTempBindingTbl_t * pServerTempTbl,
                       dhcp6Packet_t *pDhcp6Pkt, uint32_t dhcp6MsgSize);

/*!*************************************************************************************************
\fn     void DHCP6_Server_AddOptionClientID(uint8_t ** pDhcp6Pkt, dhcp6ClientTempBindingTbl_t * pServerTempTbl,
                                            uint32_t* dhcp6MsgSize)
\brief  This function adds the "ClientID" option.

\param  [in]  pDhcp6Pkt       Pointer to the end of the DHC packet.
\param  [in]  pServerTempTbl  Pointer to the server's table.
\param  [in]  dhcp6MsgSize    The size of the message.
***************************************************************************************************/
void DHCP6_Server_AddOptionClientID(uint8_t ** pDhcp6Pkt, dhcp6ClientTempBindingTbl_t * pServerTempTbl,
                                    uint32_t* dhcp6MsgSize);

/*!*************************************************************************************************
\fn     void DHCP6_Server_AddOptionServerID(uint8_t ** pDhcp6Pkt, dhcp6ClientTempBindingTbl_t * pServerTempTbl,
                                            uint32_t* dhcp6MsgSize)
\brief  This function adds the "ServerID" option.

\param  [in]  pDhcp6Pkt       Pointer to the end of the DHC packet.
\param  [in]  pServerTempTbl  Pointer to the server's table.
\param  [in]  dhcp6MsgSize    The size of the message.
***************************************************************************************************/
void DHCP6_Server_AddOptionServerID(uint8_t ** pDhcp6Pkt, dhcp6ServerCfg_t* pServerStruct,
                                    uint32_t* dhcp6MsgSize);

#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _DHCP6_SERVER_H */
#endif
