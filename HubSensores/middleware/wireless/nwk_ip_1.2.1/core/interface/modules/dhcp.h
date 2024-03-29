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

#ifndef _DHCP_H
#define _DHCP_H

/*!
\file       dhcp.h
\brief      This is a public header file for the DHCPv4 module. 
*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "EmbeddedTypes.h"
#include "stack_config.h"

#include "stdint.h"


#ifndef DHCP4_SERVER_ENABLED
    #define DHCP4_SERVER_ENABLED            0
#endif

#ifndef DHCP4_CLIENT_ENABLED
    #define DHCP4_CLIENT_ENABLED            0
#endif


#if (DHCP4_CLIENT_ENABLED || DHCP4_SERVER_ENABLED) && IP_IP4_ENABLE
/*==================================================================================================
Public macros
==================================================================================================*/
#define DHCP_SERVER_PORT     (67)   /* from client to server  */
#define DHCP_CLIENT_PORT     (68)    /* from server to client   */

#define DHCP_OP_BOOTREQUEST    1
#define DHCP_OP_BOOTREPLY      2

#define DHCP_DISCOVER  1
#define DHCP_OFFER     2
#define DHCP_REQUEST   3
#define DHCP_DECLINE   4
#define DHCP_ACK       5
#define DHCP_NAK       6
#define DHCP_RELEASE   7
#define DHCP_INFORM    8


#define DHCP_OPTION_MSG_TYPE_LEN            1U
#define DHCP_OPTION_SERVER_ID_LEN           4U
#define DHCP_OPTION_CLIENT_ID_FIXED_LEN     6U
#define DHCP_OPTION_REQUESTED_IP_ADDR_LEN   4U
#define DHCP_OPTION_END_LEN                 1U
#define DHCP_OPTION_SUBNET_MASK_LEN         4U
#define DHCP_OPTION_IP_ADDR_LEASE_TIME_LEN  4U
#define DHCP_OPTION_ROUTER_LEN              4U
#define DHCP_OPTION_DNS_LEN                 4U



#define DHCP_OPTION_SUBNET_MASK             1U
#define DHCP_OPTION_ROUTER                  3U
#define DHCP_OPTION_DNS                     6U
#define DHCP_OPTION_REQUESTED_IP_ADDR       50U
#define DHCP_OPTION_IP_ADDR_LEASE_TIME      51U
#define DHCP_OPTION_MSG_TYPE                53U
#define DHCP_OPTION_SERVER_IDENTIFIER       54U
#define DHCP_OPTION_PARAM_REQUEST_LIST      55U
#define DHCP_OPTION_CLIENT_IDENTIFIER       61U
#define DHCP_OPTION_END                     255U

#define DHCP_CIADDR_LEN                  4U
#define DHCP_YIADDR_LEN                  4U
#define DHCP_SIADDR_LEN                  4U
#define DHCP_GIADDR_LEN                  4U
#define DHCP_CHADDR_LEN                  16U

#define DHCP_PKT_MAX_SIZE                512U

#define DHCP_LINK_ETHERNET              0x01
#define DHCP_HARDWARE_ADDRESS           6U
#define DHCP_DEFAULT_NR_HOPS            0

#define DEFAULT_LLADDR_IDX              0
#define DHCP_DISCOVER_OPT_SIZE          12

#define DHCP_TIME_DAY_IN_SECONDS 0x00015180      /*default lease time*/

#define DHCP_FLAGS_BROADCAST        0x8000

/*==================================================================================================
Public type definitions
==================================================================================================*/
typedef enum
{
    gDhcpCodeRequest_c              =1U,
    gDhcpCodeReply_c                =2U
} DhcpOpCode_t;

typedef enum
{
    gDhcpStateInit_c             =1U, /*!< Before sending DHCPDISCOVER */
    gDhcpStateSelecting_c        =2U, /*!< Waiting DHCPOFFER */
    gDhcpStateRequesting_c       =3U, /*!< Waiting DHCPACK */
    gDhcpStateBound_c            =4U, /*!< Connection with DHCP server established */
    gDhcpStateRenewing_c         =5U, /*!< Timer 1 expired, sent DHCPREQUEST to leasing server */
    gDhcpStateRebinding_c        =6U  /*!< Timer 2 expired, sent broadcast DHCPREQUEST */
} dhcpState_t;


typedef struct dhcpPacket_tag
{
    uint8_t opCode;
    uint8_t hwType;
    uint8_t hwLength;
    uint8_t hops;
    uint8_t xid[4];
    uint8_t secs[2];
    uint8_t  flags[2];
    uint8_t ciaddr[4];
    uint8_t yiaddr[4];
    uint8_t siaddr[4];
    uint8_t giaddr[4];
    uint8_t chaddr[16];
    uint8_t  serverName[64];
    uint8_t  file[128];
} dhcpPacket_t;


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
\fn     void DHCP_Client_IntervalTmrHandler(void *param)
\brief  DHCP periodical timer handler.

\param  [in]  param  pointer user data
***************************************************************************************************/
void DHCP_Client_IntervalTmrHandler(void *param);

/*!*************************************************************************************************
\fn     void DHCP_Server_IntervalTmrHandler(void *param)
\brief  DHCP periodical timer handler.

\param  [in]  param  pointer user data
***************************************************************************************************/
void DHCP_Server_IntervalTmrHandler(void *param);

/*!*************************************************************************************************
\fn     void DHCP_AddOptionMsgType(uint8_t ** pDhcpPkt, uint8_t msgType, uint32_t* dhcpMsgSize)
\brief  This function adds the "message type" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in]      msgType      the type of the DHCP message.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message.
***************************************************************************************************/
void DHCP_AddOptionMsgType(uint8_t ** pDhcpPkt,uint8_t msgType, uint32_t* dhcpMsgSize);

/*!*************************************************************************************************
\fn     void DHCP_Server_AddOptionServerID(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize,
                                           uint32_t serverAddr)
\brief  This function adds the "server ID" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in]      serverAddr   Server's IP address.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message.
***************************************************************************************************/
void DHCP_Server_AddOptionServerID(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize,
                                   uint32_t serverAddr);

/*!*************************************************************************************************
\fn     void DHCP_Server_AddOptionIpAddrLeaseTime(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize)
\brief  This function adds the "server ID" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message.
***************************************************************************************************/
void DHCP_Server_AddOptionIpAddrLeaseTime(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize);

/*!*************************************************************************************************
\fn     void DHCP_AddOptionSubnetMask(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize, uint32_t subNetMask)
\brief  This function adds the "SubnetMask" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in]      subNetMask   Subnet mask address.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message
***************************************************************************************************/
void DHCP_AddOptionSubnetMask(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize,uint32_t subNetMask);

/*!*************************************************************************************************
\fn     void DHCP_Server_AddOptionDNS(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize, uint32_t serverAddr)
\brief  This function adds the "DNS" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in]      serverAddr   Server's IP address.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message
***************************************************************************************************/
void DHCP_Server_AddOptionDNS(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize,uint32_t serverAddr);

/*!*************************************************************************************************
\fn     void DHCP_Server_AddOptionRouter(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize, uint32_t serverAddr)
\brief  This function adds the "Router" option.

\param  [in]      pDhcpPkt     Pointer to the end of the DHC packet.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message.
\param  [in]      serverAddr   Server's IP address.
***************************************************************************************************/
void DHCP_Server_AddOptionRouter(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize,uint32_t serverAddr);

/*!*************************************************************************************************
\fn     void DHCP_AddOptionEnd(uint8_t** pDhcpPkt, uint32_t* dhcpMsgSize)
\brief  This function adds the "end" option.

\param  [in]      pDhcpPkt     Pointer to the interface.
\param  [in,out]  dhcpMsgSize  The size of the DHCP message
***************************************************************************************************/
void DHCP_AddOptionEnd(uint8_t** pDhcpPkt,uint32_t* dhcpMsgSize);


#ifdef __cplusplus
}
#endif

#endif
/*================================================================================================*/
#endif  /*_DHCP_H */
