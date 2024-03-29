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
\file       thread_nwk_data_globals.c
\brief      This is the source file that contains parameters for the Thread Network Data module
            that can be configured by the application
*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "EmbeddedTypes.h"
#include "thread_types.h"
#include "thread_attributes.h"
#include "thread_mgmt.h"
#include "thread_network.h"
#include "app_thread_config.h"
#include "stack_config.h"
#include "thread_cfg.h"
#include "mpl.h"

/*==================================================================================================
Private macros
==================================================================================================*/

#if (THR_MAX_NEIGHBORS != gNumKeyDeviceListEntries_c) && \
    (!MAC_FILTERING_ENABLED)
    #error Please use the same value for THR_MAX_NEIGHBORS and gNumKeyDeviceListEntries_c
#endif

#if ((!THREAD_ED_CONFIG) && ((THR_MAX_ROUTERS > THR_MAX_NEIGHBORS) && \
      (!MAC_FILTERING_ENABLED)) || (THR_MAX_ROUTERS > 32))
#error Update the THR_MAX_ROUTERS value in thread_cfg.h. Note that the maxim values is 32.
#endif

#if (THR_MAX_INSTANCES > IP_IF_NB)
    #error Use the same value for THR_MAX_INSTANCES and IP_IF_NB (app_stack_config.h)
#endif

/*==================================================================================================
Private type definitions
==================================================================================================*/

/*==================================================================================================
Private prototypes
==================================================================================================*/

/*==================================================================================================
Private global variables declarations
==================================================================================================*/

/*==================================================================================================
Public global variables declarations
==================================================================================================*/
/*! Stack nwk memory managers poolId */
const uint8_t gNwkPoolId = ThrPoolId_d;

/*! Thread Instances Table */
void *gpaThrInstances[THR_MAX_INSTANCES] = {NULL};
const uint32_t gThrNbOfInstances = THR_MAX_INSTANCES;

/*! Thread Attributes Tables */
thrAttr_t *gpaThrAttr[THR_MAX_INSTANCES] = {NULL};
thrStringAttr_t *gpaThrStringAttr[THR_MAX_INSTANCES] = {NULL};
thrActiveAttr_t *gpaThrActiveAttr[THR_MAX_INSTANCES] = {NULL};
thrPendingAttr_t *gpaThrPendingAttr[THR_MAX_INSTANCES] = {NULL};

const mplInstanceCfg_t mThreadMplCfgEndDev = {THR_STACK_MPL_CFG_ENDDEVICE};
#if !THREAD_ED_CONFIG
const mplInstanceCfg_t mThreadMplCfgRouter = {THR_STACK_MPL_CFG_ROUTER};
#endif

/*! Thread Neighbors Table */
thrNeighbor_t gpaThrNeighbors[THR_MAX_NEIGHBORS];
const uint32_t gThrNeighborsTblSize = THR_MAX_NEIGHBORS;
/*! The Max number of neighbors to do a link sync */
const uint8_t gThrMaxLinkSyncNeighbors = THR_MAX_LINK_SYNC_NEIGHBORS;

/*! Handle Tracking Table */
handleTrackingTable_t gpaThrHandleTrackingTable[THR_MAX_DATA_REQS];
const uint8_t gThrHandleTrackingTableSize = THR_MAX_DATA_REQS;
const uint8_t gThrFailChildTransmissions = THR_FAILED_CHILD_TRANSMISSIONS;
const uint8_t gThrFailRouterTransmissions = THR_FAILED_ROUTER_TRANSMISSIONS;

/*! Thread Mac filtering Table */
macFilteringNeighborData_t  *gaMacFilteringTable[MAC_FILTERING_TABLE_SIZE] = {NULL};
const uint32_t gThrMacFilterTlbSize = MAC_FILTERING_TABLE_SIZE;

/*! Service table attributes */
serviceSet_t       gaThrNwkDataServiceSetTbl[THR_NWK_DATA_SERVICE_SET_TBL_SIZE];
const uint8_t     gThrNwkDataServiceSetTblSize = THR_NWK_DATA_SERVICE_SET_TBL_SIZE;

thrLocalServiceSet_t *gpaLocalServiceSetTbl[THR_LOCAL_SERVICE_SET_TBL_SIZE] = {NULL};
const uint8_t     gLocalServiceSetTblSize = THR_LOCAL_SERVICE_SET_TBL_SIZE;

/*! Thread Network Data Table */
nwkDataInterfaceSet_t *gpaNwkDataIfTbl[THR_MAX_INSTANCES] = {NULL};
nwkDataInterfaceSet_t  gaNwkDataIfTbl[THR_MAX_INSTANCES] = {0};

/*! The extended address used for discovery */
const uint8_t gThrDiscoveryExtAddr[] = THR_DISCOVERY_EXT_ADDR;
/*! The key used for discovery */
const uint8_t gThrDiscoveryKey[] = THR_DISCOVERY_KEY;
/*! The frame counter used for discovery */
const uint32_t gThrDiscoveryFrameCounter = THR_DISCOVERY_FRAME_COUNTER;

/*! Time an originator of a Discovery Request should wait
 * for incoming Discovery Responses on a channel.*/
const uint16_t gThrDiscoveryTime = THR_DISCOVERY_TIME;
/*! Maximum jitter time used to delay generation of Discovery Responses.
    It should be less than gThrDiscoverytime*/
const uint16_t gThrDiscoveryMaxJitter = THR_DISCOVERY_MAX_JITTER;

/*! Thread Cache Entries Table */
thrLqCacheEntry_t gaThrRouterLqTbl[THR_MAX_DEV_ADDR_QUERY_CACHE_ENTRIES +
                                   THR_MAX_SLEEPY_ED_NEIGHBORS * THR_CHILD_ADDR_REG_ENTIRES] = {0};
const uint32_t gThrRouterLqTblSize = THR_MAX_DEV_ADDR_QUERY_CACHE_ENTRIES +
                                     THR_MAX_SLEEPY_ED_NEIGHBORS * THR_CHILD_ADDR_REG_ENTIRES;

const uint32_t gThrAddrQueryInitRetryDelaySec = THR_ADDRESS_QUERY_INITIAL_RETRY_DELAY_SEC;
const uint32_t gThrAddrQueryMaxRetryDelaySec = THR_ADDRESS_QUERY_MAX_RETRY_DELAY_SEC;

#if !THREAD_ED_CONFIG
const uint8_t gThrChildAddrRegEntries = THR_CHILD_ADDR_REG_ENTIRES;

thrChildAddrRegEntry_t gaThrAddrRegTbl[THR_MAX_SLEEPY_ED_NEIGHBORS] = {0};
const uint32_t gThrAddrRegTblSize = THR_MAX_SLEEPY_ED_NEIGHBORS;

thrChildMcastAddrRegEntry_t gaThrMcastAddrRegTbl[THR_MAX_SLEEPY_ED_NEIGHBORS] = {0};
const uint32_t gThrMcastAddrRegTblSize = THR_MAX_SLEEPY_ED_NEIGHBORS;
/*! Child Version Set table */
childVersNbSet_t gaChildVersNbTbl[THR_MAX_SLEEPY_ED_NEIGHBORS];
const uint8_t gThrMaxSleepyEdNeighbors = THR_MAX_SLEEPY_ED_NEIGHBORS;

/*! Server Data Prefix table */
ipAddr_t gaServerDataPrefixTbl[THR_SERVER_DATA_PREFIX_TBL_SIZE];
uint8_t  gaServerDataPrefixLenTbl[THR_SERVER_DATA_PREFIX_TBL_SIZE];
const uint8_t gThrServerDataPrefixTblSize = THR_SERVER_DATA_PREFIX_TBL_SIZE;

/*! Server Data Border Router Set table */
borderRouterSet_t gaThrServerDataBrSetTbl[THR_SERVER_DATA_BR_SET_TBL_SIZE];
const uint8_t gThrServerDataBrSetTblSize = THR_SERVER_DATA_BR_SET_TBL_SIZE;

/*! Server Data External Route table */
externalRouteSet_t gaServerDataExtRouteTbl[THR_SERVER_DATA_HAS_ROUTE_TBL_SIZE];
const uint8_t gThrServerDataExtRouteTblSize = THR_SERVER_DATA_HAS_ROUTE_TBL_SIZE;

/*! The maximum interval between increments of ID_sequence_number by the Leader.*/
const uint8_t gThrLeaderIDSeqPeriod = THR_LEADER_ID_SEQUENCE_PERIOD_SEC;
#endif /* if !THREAD_ED_CONFIG */

/*! Pointer to the Thread Stack task message queue */
taskMsgQueue_t *mpThrTaskMsgQueue = NULL;

/*! Pointer to the Ip task message queue */
taskMsgQueue_t *mpThrIpTaskMsgQueue = NULL;

/*! Maximum number of potential parents that can be discovered
    when performing the Attaching procedure */
const uint8_t gThrMaxNwkAttachParents = THR_MAX_NWK_ATTACH_PARENT_ENTRIES;
const uint16_t gThrMinReattachJitterMs = THR_REATTACH_JITTER_MIN_MS;
const uint16_t gThrMaxReattachJitterMs = THR_REATTACH_JITTER_MAX_MS;

/*! On power on, during the network start with NVM, a router will perform a Lync Sync
    after a random period between [0, gThrPowerOnRouterMaxJitterMs] */
const uint32_t gThrPowerOnRouterMaxJitterMs = THR_POWERON_ROUTER_MAX_JITTER_MS;
/*! On power on, during the network start with NVM, an end device will perform a Child Update
    after a random period between [gThrPowerOnRouterMaxJitterMs,
                                   gThrPowerOnRouterMaxJitterMs+gThrPowerOnEDMaxJitterMs] */
const uint32_t gThrPowerOnEDMaxJitterMs = THR_POWERON_ED_MAX_JITTER_MS;

/*! Network diagnostic globals */
mgmtDiagnostic_LinkData_t gaMgmtDiagLinkData[THR_MAX_INSTANCES];
mgmtDiagnostic_DeviceData_t gMgmtDiagnosticDeviceData = {.batteryLevel = 0, /* battery level in percentage */
                                                         .voltage = 3300, /* voltage in mV*/
                                                         .boardName = {sizeof(BOARD_NAME), BOARD_NAME} /* Board Name*/
                                                        };

/*! Thread device configuration */
thrDeviceConfig_t gaThrDeviceConfig[THR_MAX_INSTANCES];

/*! The maximum number of thread networks that can be discovered during network creation to select the best channel*/
const uint8_t gThrMaxDiscNwkToFormNwk = THR_MAX_DISCNWK_TO_FORM_NWK;

/*! Thread Protocol Version*/
const uint8_t gThrProtocolVersion = THR_PROTOCOL_VERSION;

/*! Network Data Prefix table */
ipAddr_t gaNwkDataPrefixTbl[THR_NWK_DATA_PREFIX_TBL_SIZE];
uint8_t  gaNwkDataPrefixLenTbl[THR_NWK_DATA_PREFIX_TBL_SIZE];
const uint8_t gThrNwkDataPrefixTblSize = THR_NWK_DATA_PREFIX_TBL_SIZE;

/*! Network Data Border Router Set table */
borderRouterSet_t gaThrNwkDataBrSetTbl[THR_NWK_DATA_BR_SET_TBL_SIZE];
const uint8_t gThrNwkDataBrSetTblSize = THR_NWK_DATA_BR_SET_TBL_SIZE;

/*! Network Data External Route table */
externalRouteSet_t gThrNwkDataExtRouteTbl[THR_NWK_DATA_HAS_ROUTE_TBL_SIZE];
const uint8_t gThrNwkDataExtRouteTblSize = THR_NWK_DATA_HAS_ROUTE_TBL_SIZE;

/*! Network Data Context Id table */
contextIdSet_t gThrNwkDataContextIdTbl[THR_NWK_DATA_CTX_TBL_SIZE];
const uint8_t gThrNwkDataContextIdTblSize = THR_NWK_DATA_CTX_TBL_SIZE;

/*! Thread Slaac temporary address table - stored in NVM (NotMirroredInRam) */
ipAddr_t *gpaThrSlaacTempAddrTbl[THR_SLAAC_TEMP_ADDR_TABLE_SIZE];
const uint8_t gThrSlaacTempAddrTblSize = THR_SLAAC_TEMP_ADDR_TABLE_SIZE;

/*! Network Data Minimum Stable Lifetime */
const uint32_t gThrNwkDataMinStableLifetime = THR_NWK_DATA_MIN_STABLE_LIFETIME_SEC;

/*! Network Data Context ID reuse delay */
uint32_t gThrContextReuseDelaySec = THR_CONTEXT_REUSE_DELAY_SEC;

/*! The attachment retries of an end device when its parent is lost  */
const uint16_t  gThrEDLostParentAttachRetries = THR_ED_LOST_PARENT_ATTACH_RETRIES;
/*! When the end device (sleepy or powered ED) loses its parent, the end device
    will attempt to attach after THR_ED_ATTACH_RETRY_INITIAL_TIMEOUT milliseconds.
    If the attachment still fails, for each retry, the timeout to trigger the next retry
    will be doubled, and so on, until it reaches to THR_ED_ATTACH_RETRY_MAX_TIMEOUT.*/
const uint16_t gThrEDAttachRetryInitialTimeout = THR_ED_ATTACH_RETRY_INITIAL_TIMEOUT;
/*!  The maximum retry timeout for the end device attachment */
const uint16_t gThrEDAttachRetryMaxTimeout = THR_ED_ATTACH_RETRY_MAX_TIMEOUT;

/*!  The number of active scan retries if no beacon is received  */
const uint16_t gThrActiveScanRetries = THR_ACTIVE_SCAN_RETRIES;

/*! The default periodic interval for REED or End Devic eRxOn to send ChildUpdateRequest.
 * This values should be less than THR_CHILD_ED_TIMEOUT_PERIOD_SEC  */
const uint32_t gThrChildEDKeepAliveIntervalMin = THR_CHILD_ED_KEEP_ALIVE_INTERVAL_MIN_MS;
const uint32_t gThrChildEDKeepAliveIntervalMax = THR_CHILD_ED_KEEP_ALIVE_INTERVAL_MAX_MS;

#if THR_ROUTING_ENABLE
thrInterfaceSet_t maThrIfTbl[THR_MAX_INSTANCES] = {0};
thrIdAssignSet_t *gpaThreadIdAssignSet[THR_MAX_INSTANCES][THR_MAX_POSSIBLE_ROUTERS] = {NULL};

thrLinkSet_t maLinkSetTbl[THR_MAX_INSTANCES * THR_MAX_ROUTERS];
thrRouteSet_t maRouteSetTbl[THR_MAX_INSTANCES * THR_MAX_POSSIBLE_ROUTERS];

/*! The maximum number of Routers that a Thread Network may contain */
uint32_t gThrMaxAllowedRouters = THR_MAX_ROUTERS;
/*!  If a Router goes for LEADER_TIMEOUT seconds without receiving a new
    ID_sequence_number from a neighbor, it MUST consider itself disconnected
    from the Leader and stop using its current Router ID */
uint32_t gThrNetworkIdTimeoutSec = THR_LEADER_TIMEOUT_SEC;
/* The number of active Routers on the Thread Network below which
    a REED may decide to become a Router */
uint32_t gThrRouterUpgradeThreshold = THR_ROUTER_UPGRADE_THRESHOLD;
/*! The number of active Routers on the Thread Network above
    which an active Router may decide to become a Child */
uint32_t gThrRouterDowngradeThreshold = THR_ROUTER_DOWNGRADE_THRESHOLD;
/* The minimum number of neighbors with link quality 2 or better that a
    Router must have to downgrade to a REED. It should be less than 32 */
uint32_t gThrMinDowngradNeigbors = THR_MIN_DOWNGRADE_NEIGHBORS;
/*! The maximum jitter time when soliciting a router ID */
const uint32_t gThrRouterSelJitterSec = THR_ROUTER_SELECTION_JITTER_SEC;
#endif /* THR_ROUTING_ENABLE */

/*! Slaac Manual IID */
uint8_t gaThrSlaacManualIID[INET6_IID_LEN];

/*==================================================================================================
Private functions
==================================================================================================*/

/*==================================================================================================
Public functions
==================================================================================================*/

