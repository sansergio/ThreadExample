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

#ifndef _DHCP6_CLIENT_H
#define _DHCP6_CLIENT_H

/*!
\file       dhcp6_client.h
\brief      This is a public header file for the DHCPv6 module. 
*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "EmbeddedTypes.h"
#include "stack_config.h"
#include "ip.h"
#include "dhcp6.h"

#if IP_IP6_ENABLE
/*==================================================================================================
Public macros
==================================================================================================*/

/*==================================================================================================
Public type definitions
==================================================================================================*/
typedef struct dhcp6ReliabilityParams_tag
{
    uint32_t rt;
    uint32_t irt;
    uint32_t mrc;
    uint32_t mrt;
    uint32_t mrd;
    uint32_t msgNo;
    uint32_t initialMsgSendingTime;
} dhcp6ReliabilityParams_t;

typedef struct dhcp6ClientData_tag
{   
    ipAddr_t ipAddr;
    ipAddr_t relayAddr;
    ipAddr_t prefix; 
    uint8_t serverID[DHCP6_MAX_DEVICEID_LEN];
    uint16_t startTime;
    
    dhcp6DUID_t DUID;
    uint32_t timestamp;
    
    uint32_t xid;                   /*transaction ID */
    uint32_t reqOptions;
    uint32_t iaID;
    uint32_t T1;
    uint32_t T2;
    uint32_t preferredLifetime;
    
    uint32_t validLifetime;
    ipIfUniqueId_t ipIfId;
    
    dhcp6RelayAgCb_t pfRelayAgCb;
    void* pData;  
    
    dhcp6ReliabilityParams_t retrans;    
    uint8_t serverIDLen;
    uint8_t state;
    uint8_t lqi;

} dhcp6ClientData_t;

typedef struct dhcp6ClientRamData_tag
{
    tmrTimerID_t retransTimer;
}dhcp6ClientRamData_t;
    
typedef struct dhcp6ClientStartParams_tag
{
    ipIfUniqueId_t ipIfId;
    uint32_t clientStartMode;
    uint16_t deviceType;
    ipAddr_t *relayAddr;
    ipAddr_t *pPrefix;
    uint32_t macSec;
}dhcp6ClientStartParams_t;

typedef void (*dhcp6ClientSetAddrCb_t) (ipIfUniqueId_t ifUniqueId,ipAddr_t* ipAddr, void* pData);
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
\fn     void DHCP6_Client_Init(taskMsgQueue_t *pTaskMsgQueue)
\brief  This function initialize the DHCPv6 Client module.

\param  [in]  pTaskMsgQueue  Pointer to the task message queue.
***************************************************************************************************/
void DHCP6_Client_Init(taskMsgQueue_t *pTaskMsgQueue);

/*!*************************************************************************************************
\fn     void DHCP6_Client_Start(dhcp6ClientStartParams_t *pDhcp6ClientStartParams)
\brief  This function starts the DHCPv6 Client module.

\param  [in]  pDhcp6ClientStartParams  Pointer to start parameter structure, that contains:
                                       pIfPtr          Double pointer to the interface handle.
                                       clientStartMode One of the five possible DHCP start-up modes
                                                                     1 - Address Assignment
                                                                     2 - DNS configuration in parallel
                                                                         with Address Assignment
                                                                     3 - Stateless DHCPv6 for DNS configuration
                                                                     4 - Prefix Delegation
                                                                     5 - DNS configuration in parallel
                                                                         with Prefix Delegation
                                       deviceType      One of the three possible device types
                                                                     1 - Node
                                                                     2 - Router
                                                                     3 - Border Router
                                       relayAddr       The ip address of the closest relay
                                       pPrefix         Pointer to the prefix of the network in which
                                                       the client wishes to join
                                       macSec          The MAC security level
                             
\retval       nwkStatus_t              The status of the operation.
***************************************************************************************************/
nwkStatus_t DHCP6_Client_Start(dhcp6ClientStartParams_t *pDhcp6ClientStartParams);

/*!*************************************************************************************************
\fn     void DHCP6_Client_Stop(ipIfUniqueId_t ipIfId, uint32_t clientMode)
\brief  This function stops the DHCPv6 Client module on a given interface.

\param  [in]  pIfPtr      Double pointer to the interface handle.
\param  [in]  clientMode  Client mode.
***************************************************************************************************/
void DHCP6_Client_Stop(ipIfUniqueId_t ipIfId, uint32_t clientMode);

/*!*************************************************************************************************
\fn     void DHCP6_Client_SolicitAddress(void * param)
\brief  This function handles the receiving of a Router Advertisement message and sends a
        DHCP Solicit message

\param  [in]  param  Pointer to the client's info table.
***************************************************************************************************/
void DHCP6_Client_SolicitAddress(void * param);

/*!*************************************************************************************************
\fn     void DHCP6_Client_HandleDadFailed(void * param)
\brief  This function handles the receiving of an unsuccessful DAD and sends a DHCP Decline message.

\param  [in]  param  Pointer to the client's info table.
***************************************************************************************************/
void DHCP6_Client_HandleDadFailed(void * param);

/*!*************************************************************************************************
\fn     void DHCP6_Client_SendRelease(void *param)
\brief  This function sends a DHCP Release message.

\param  [in]  param  Pointer to the client's info table.
***************************************************************************************************/
void DHCP6_Client_SendRelease(void *param);

/*!*************************************************************************************************
\fn     void DHCP6_Client_SendDecline(void* param)
\brief  This function sends a DHCP Decline message.

\param  [in]  param  Pointer to the entry from client table.
***************************************************************************************************/
void DHCP6_Client_SendDecline(void* param);

/*!*************************************************************************************************
\fn     void DHCP6_Client_RegisterRelayAg(dhcp6RelayAgCb_t pfRelayAgCb, ipIfUniqueId_t ifId)
\brief  This function registers the Relay Agent callback.

\param  [in]  pfRelayAgCb  Pointer to the RelayAgent callback.
\param  [in]  ifId         IP interface identifier.
***************************************************************************************************/
void DHCP6_Client_RegisterRelayAg(dhcp6RelayAgCb_t pfRelayAgCb,ipIfUniqueId_t ifId);

/*!*************************************************************************************************
\fn     void DHCP6_Client_Send(ipIfUniqueId_t ifId, void * pDhcp6Pkt, uint32_t dhcp6MsgSize,
                               ipAddr_t* destination, ipAddr_t* pSourceIpAddr)
\brief  This function sends a DHCP message to lower layers.

\param  [in]  ifId           IP interface identifier.
\param  [in]  pDhcp6Pkt      Pointer to the message that needs to be sent.
\param  [in]  dhcp6MsgSize   Size of the data.
\param  [in]  destination    Specifies the destination (AllDhcpServersAndRelayAgents or AllDhcpServers)
\param  [in]  pSourceIpAddr  Pointer to the source ip address or in6addr_any for IP source address
                             select
***************************************************************************************************/
void DHCP6_Client_Send(ipIfUniqueId_t ifId, void * pDhcp6Pkt, uint32_t dhcp6MsgSize,
                       ipAddr_t* destination, ipAddr_t* pSourceIpAddr);

/*!*************************************************************************************************
\fn     void DHCP6_Client_RegisterSetAddr(dhcp6ClientSetAddrCb_t pfDhcp6ClientSetAddr)
\brief  This function sets the pointer to SetAddr function, that will be called after the client
        has received a valid address from server

\param  [in]  pfDhcp6ClientSetAddr  Function pointer
***************************************************************************************************/
void DHCP6_Client_RegisterSetAddr(dhcp6ClientSetAddrCb_t pfDhcp6ClientSetAddr);

/*!*************************************************************************************************
\fn     bool_t DHCP6_Client_IsAddrSolicitPending(ipIfUniqueId_t ipIfId)
\brief  Checks if any address solicit message is pending a response

\param  [in]  ipIfId  Interface unique ID

\retval       bool_t  TRUE if there are pending address solicit operations
***************************************************************************************************/
bool_t DHCP6_Client_IsAddrSolicitPending(ipIfUniqueId_t ipIfId);

/*!*************************************************************************************************
\fn     void DHCP6_Client_AddOptionClientID(uint8_t ** pDhcp6Pkt, dhcp6ClientData_t* clientParam,
                                            uint32_t* dhcp6MsgSize)
\brief  This function adds the "Client ID" option.

\param  [in]      pDhcp6Pkt     Pointer to the end of the DHC packet.
\param  [in]      clientParam   Pointer to the client's table.
\param  [in,out]  dhcp6MsgSize  The size of the message.

***************************************************************************************************/
void DHCP6_Client_AddOptionClientID(uint8_t ** pDhcp6Pkt, dhcp6ClientData_t* clientParam,
                                    uint32_t* dhcp6MsgSize);

/*!*************************************************************************************************
\fn     void DHCP6_Client_AddOptionElapsedTime(uint8_t ** pDhcp6Pkt, dhcp6ClientData_t* clientParam,
                                               uint32_t* dhcp6MsgSize)
\brief  This function adds the "Elapsed Time" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in]      clientParam  Pointer to client table entry
\param  [in,out]  dhcpMsgSize  The size of the DHCP message.

***************************************************************************************************/
void DHCP6_Client_AddOptionElapsedTime(uint8_t ** pDhcp6Pkt, dhcp6ClientData_t* clientParam,
                                       uint32_t* dhcp6MsgSize);

#if !THREAD_ED_CONFIG
/*!*************************************************************************************************
\fn     void DHCP6_Client_ParseVendorOpt(uint8_t* pOption, uint16_t opSize, dhcp6VendorOpt_t* pVendorOptInfo)
\brief  This function parses Vendor option.

\param  [in]  pOption         Pointer to Vendor option in the received packet.
\param  [in]  opSize          The length of vendor option.
\param  [in]  pVendorOptInfo  Pointer to the vendor's options structure.

\retval       none
***************************************************************************************************/
void DHCP6_Client_ParseVendorOpt(uint8_t* pOption, uint16_t opSize, dhcp6VendorOpt_t* pVendorOptInfo);

#endif

#ifdef __cplusplus
}
#endif

#endif
/*================================================================================================*/
#endif  /* _DHCP6_CLIENT_H */
