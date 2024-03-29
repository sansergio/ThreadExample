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
#ifndef _THCI_H
#define _THCI_H
/*!=================================================================================================
\file       thci.h
\brief      This is a header file for the Thread Host Control Interface (THCI) commands
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "sockets.h"
#include "thread_attributes.h"
#include "thread_mgmt.h"

/*==================================================================================================
Public macros
==================================================================================================*/
#define FSCI_INTERFACE                      (0U)

/*==================================================================================================
Public type definitions
==================================================================================================*/
typedef enum nwkOpGroup_tag
{
    gFSCI_IpStackOpGReq_c                       = 0xCEU,
    gFSCI_IpStackOpGCnf_c                       = 0xCFU
}nwkOpGroup_t;

typedef enum nwkOpCode_tag
{
    gTHCI_IpStackBsdSocket_c                    = 0x00U,
    gTHCI_IpStackBsdShutdown_c                  = 0x01U,
    gTHCI_IpStackBsdBind_c                      = 0x02U,
    gTHCI_IpStackBsdSend_c                      = 0x03U,
    gTHCI_IpStackBsdSendto_c                    = 0x04U,
    gTHCI_IpStackBsdRecv_c                      = 0x05U,
    gTHCI_IpStackBsdRecvfrom_c                  = 0x06U,
    gTHCI_IpStackBsdConnect_c                   = 0x07U,
#if BSDS_STREAM_SUPPORT
    gTHCI_IpStackBsdListen_c                    = 0x08U,
    gTHCI_IpStackBsdAccept_c                    = 0x09U,
#endif
    gTHCI_IpStackBsdSetsockopt_c                = 0x0AU,
    gTHCI_IpStackBsdGetsockopt_c                = 0x0BU,
    gTHCI_IpStackIfconfigBind_c                 = 0x0CU,
    gTHCI_IpStackIfconfigAll_c                  = 0x0DU,
    gTHCI_IpStackPing_c                         = 0x0EU,

    /* Thread Network Parameters */
    gTHCI_ThrGetNeighborInfo_c                  = 0x10U,

    gTHCI_GetInstancesReq_c                     = 0x11U,

    /* mac filtering table (white list)*/
    gTHCI_AddMacFilterEntry_c                   = 0x12U,
    gTHCI_RemoveMacFilterEntry_c                = 0x13U,
    gTHCI_EnableMacFiltering_c                  = 0x14U,
    gTHCI_GetMacFilterTable_c                   = 0x15U,

    gTHCI_SetDeviceConfig_c                     = 0x16U,

    /* get/set attributes */
    gTHCI_GetAttrReq_c                          = 0x17U,
    gTHCI_SetAttrReq_c                          = 0x18U,
    gTHCI_GetThrIpAddr_c                        = 0x19U,

    /* Network Interface */
    gTHCI_ThrNwkScan_c                          = 0x1AU,
    gTHCI_ThrNwkCreate_c                        = 0x1BU,
    gTHCI_ThrNwkJoin_c                          = 0x1CU,
    gTHCI_ThrNwkDisconnect_c                    = 0x1DU,
    gTHCI_ThrGetParent_c                        = 0x1EU,
    gTHCI_ThrFactoryReset_c                     = 0x1FU,

    /**/
    gTHCI_ThrSetThreshold_c                     = 0x20U,
    gTHCI_ThrCpuReset_c                         = 0x21U,
    gTHCI_ThrCpuResetIndication_c               = 0x22U,
    gTHCI_ThrGetChildrenTable_c                 = 0x23U,
    gTHCI_ThrGetNeighborTable_c                 = 0x24U,
    gTHCI_ThrGetRoutingTable_c                  = 0x25U,

    /* Thread Network Data */
    gTHCI_LeaderRemoveRouterId_c                = 0x26U,

    gTHCI_ThrSwitchKey_c                        = 0x27U,
    gTHCI_ThrGenerateKey_c                      = 0x28U,

    /* Border Router Nwk data */
    gTHCI_BrPrefixAttrAddEntry_c                = 0x29U,
    gTHCI_BrPrefixAttrGetTable_c                = 0x2AU,
    gTHCI_BrPrefixAttrRemoveEntry_c             = 0x2BU,
    gTHCI_BrPrefixAttrSync_c                    = 0x2CU,
    gTHCI_BrPrefixAttrRemoveAll_c               = 0x2DU,

    gTHCI_ThrNetworkIdTimeout_c                 = 0x2EU,

    gTHCI_ThrChildUpdateToParent_c              = 0x2FU,

    /* DTLS */
    gTHCI_DtlsOpen_c                            = 0x30U,
    gTHCI_DtlsCloseContext_c                    = 0x31U,
    gTHCI_DtlsClosePeer_c                       = 0x32U,
    gTHCI_DtlsConnect_c                         = 0x33U,
    gTHCI_DtlsClientConnected_c                 = 0x34U,
    gTHCI_DtlsSend_c                            = 0x35U,
    gTHCI_DtlsReceive_c                         = 0x36U,

    /* MESHCOP */
    gTHCI_MeshCopStartCommissioner_c            = 0x40U,
    gTHCI_MeshCopStopCommissioner_c             = 0x41U,
    gTHCI_MeshCopAddExpectedJoiner_c            = 0x42U,
    gTHCI_MeshCopGetExpectedJoiner_c            = 0x43U,
    gTHCI_MeshCopRemoveExpectedJoiner_c         = 0x44U,
    gTHCI_MeshCopRemoveAllExpectedJoiners_c     = 0x45U,
    gTHCI_MeshCopSyncSteeringData_c             = 0x46U,
    gTHCI_MeshCopNwkForm_c                      = 0x47U,
    gTHCI_MeshCopNwkJoin_c                      = 0x48U,
    gTHCI_MeshCopNwkScan_c                      = 0x49U,
    gTHCI_MeshCopNwkLeave_c                     = 0x4AU,
    gTHCI_MeshCopSet_c                          = 0x4BU,
    gTHCI_MeshCopGet_c                          = 0x4CU,
    gTHCI_MeshCopSetCommissionerCredential_c    = 0x4DU,
    gTHCI_MeshCopDiagnostic_c                   = 0x4EU,
    gTHCI_MeshCopStartNativeCommissioner_c      = 0x4FU,

    gTHCI_EventNwkScan_c                        = 0x50U,
    gTHCI_EventNwkCreate_c                      = 0x51U,
    gTHCI_EventNwkJoin_c                        = 0x52U,
    gTHCI_EventNwkSelectParents_c               = 0x53U,
    gTHCI_EventNwkGeneral_c                     = 0x54U,
    gTHCI_EventNwkCommissioning_c               = 0x55U,

    gTHCI_ResetCpu_c                            = 0x60U,

    /* Network Diagnostic */
    gFsci_MgmtDiagnosticGetReq_c                = 0x61U,
    gFsci_MgmtDiagnosticResetReq_c              = 0x62U,
    gFsci_MgmtDiagnosticGetRsp_c                = 0x63U,
    gFsci_MgmtDiagnosticResetRsp_c              = 0x64U,
    gFsci_MgmtReadMemoryReq_c                   = 0x65U,
    gFsci_MgmtWriteMemoryReq_c                  = 0x66U,
    gFsci_MgmtDiagnosticDiagTestReq_c           = 0x67U,
    gFsci_MgmtDiagnosticDiagTestRsp_c           = 0x68U,

    gTHCI_ThrIdentify_c                         = 0x69U,

    /* Application Echo UDP */
    gTHCI_ThrEchoUdp_c                          = 0x70U,

    /* Multicast Groups */
    gTHCI_IpStackMcastGroupManage_c             = 0x71U,
    gTHCI_IpStackMcastGroupShow_c               = 0x72U,

    /* Application Addresses */
    gTHCI_ThrSetManualSlaacIID_c                = 0x75U,
    gTHCI_ThrProactiveAddrNotification_c        = 0x76U,

    /* Thread Reattach to network */
    gTHCI_ThrReattach_c                         = 0x80U,

    /* Network Data - Services */
    gTHCI_BrServiceAdd_c                        = 0x85U,
    gTHCI_BrServiceRemove_c                     = 0x86U,
    gTHCI_Dbg_c                                 = 0x89U,

    /* CoAP commands */
    gTHCI_ThrCoapSend_c                         = 0x90U,
    gTHCI_ThrCoapRegisterUri_c                  = 0x91U,
    gTHCI_THRCoapRcvd_c                         = 0x92U,
    gTHCI_THRCoapCreateInstance_c               = 0x93U,

    gTHCI_THRCoapAddressSolicit_c               = 0x94U,

    gTHCI_ThrDnsSend_c                          = 0x95U,
    gTHCI_ThrDnsRcvd_c                          = 0x96U,

    /* Meshcop new features */
    gTHCI_MeshCopMgmtCommGet_c                  = 0xA0U,
    gTHCI_MeshCopMgmtCommSet_c                  = 0xA1U,
    gTHCI_MeshCopMgmtActiveGet_c                = 0xA2U,
    gTHCI_MeshCopMgmtActiveSet_c                = 0xA3U,
    gTHCI_MeshCopMgmtPendingGet_c               = 0xA4U,
    gTHCI_MeshCopMgmtPendingSet_c               = 0xA5U,
    gTHCI_MeshCopMgmtDatasetChanged_c           = 0xA6U,
    gTHCI_MeshCopMgmtAnnounceBegin_c            = 0xA7U,
    gTHCI_MeshCopMgmtPanIdQuery_c               = 0xA8U,
    gTHCI_MeshCopMgmtPanIdConflict_c            = 0xA9U,
    gTHCI_MeshCopMgmtEdScan_c                   = 0xAAU,
    gTHCI_MeshCopMgmtEdReport_c                 = 0xABU,

    /* Thread 1.1 new features */
    gTHCI_ThrNwkDiscoveryReq_c                  = 0xC0U,
    gTHCI_ThrNwkDiscoveryStop_c                 = 0xC1U,
    gTHCI_ThrSearchNwkWithAnounce_c             = 0xC2U,

    gTHCI_IpStackSerialtunOpen_c                = 0xF0U,    /* APP PROC --> FSCI --> SERIAL_TUN --> 802.15.4 */
    gTHCI_IpStackSerialtunClose_c               = 0xF1U,    /* APP PROC --> FSCI --> SERIAL_TUN --> 802.15.4 */
    gTHCI_IpStackSerialtunSend_c                = 0xF2U,    /* APP PROC --> FSCI --> SERIAL_TUN --> 802.15.4 */
    gTHCI_IpStackSerialtunReceive_c             = 0xF3U,    /* APP PROC <-- FSCI <-- SERIAL_TUN <-- 802.15.4 */
}nwkOpCode_t;


typedef struct statusConfirm_tag
{
    uint8_t status;
}statusConfirm_t;

typedef struct statusCoapConfirm_tag
{
    uint8_t status;
    uint8_t msgId[2];
}statusCoapConfirm_t;

typedef struct thciEventData_tag
{
    uint8_t instanceId;             /* InstanceId */
    uint8_t eventModule;            /* Event module */
    uint8_t eventType;              /* Event type */
    uint8_t eventStatus[2];         /* Event Status */
    uint8_t dataSize[2];            /* Event Data Size */
    uint8_t aData[1];               /* Event Data */
}thciEventData_t;

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
\fn     void APP_FsciInterface(void)
\brief  This function is used to initialize the FSCI communication.

\param  [in]    pointer to the message queue

\return         void
***************************************************************************************************/
void APP_FsciInterface(taskMsgQueue_t *pMainThreadMsgQueue);
/*!*************************************************************************************************
\fn     void THCI_EventData(uint8_t opCode, uint8_t length, uint8_t *pData)
\brief

\param  [in]    opCode          FSCI opcode
\param  [in]    length          FSCI message length
\param  [in]    pData           pointer to data

\return         void
***************************************************************************************************/
void THCI_EventData(uint8_t opCode, uint8_t length, uint8_t *pData);

#if THR_ENABLE_EVENT_MONITORING
/*!*************************************************************************************************
\fn    bool_t THCI_EvMonitor( void* param)
\brief

\param [in]   param    pointer to monitor event
***************************************************************************************************/
void THCI_EvMonitor( void* param);
#endif /* THR_ENABLE_EVENT_MONITORING */

#if THR_ENABLE_MGMT_DIAGNOSTICS
/*!*************************************************************************************************
\fn     void THCI_MgmtDiagnosticAppCb(mgmtDiagnostic_RspData_t mgmtDiagRspData)
\brief This function is used to receive the network diagnostic responses
       at the application level. The message is forwarding using FSCI interface

\param  [in]    commandId       Network diagnostic command Id
\param  [in]    coapStatus      CoapStatus
\param  [in]    coapMsgId       Coap Message ID
\param  [in]    dataLen         data length
\param  [in]    pData           pointer to data

\return         void
***************************************************************************************************/
void THCI_MgmtDiagnosticAppCb(mgmtDiagnostic_RspData_t mgmtDiagRspData);
#endif /* THR_ENABLE_MGMT_DIAGNOSTICS */

#if UDP_ECHO_PROTOCOL
/*!*************************************************************************************************
\fn    void THCI_EchoUdpRcv(uint8_t status)
\brief

\param [in]   status    status of the event
***************************************************************************************************/
void THCI_EchoUdpRcv(uint8_t status);
#endif

#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _THCI_H */


