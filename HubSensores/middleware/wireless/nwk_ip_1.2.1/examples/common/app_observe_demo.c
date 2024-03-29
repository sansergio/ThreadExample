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
 
/*!=================================================================================================
\file       app_observe_demo.c
\brief      This is a public source file for the app_observe_demo module.

\copyright  (c) Copyright 2016, Freescale, Inc.  All rights reserved.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/
#include "app_coap_observe.h"
#include "RNG_Interface.h"
#include "shell.h"

/*==================================================================================================
Private macros
==================================================================================================*/
/* Timer interval for generating a new value for the resource of interest */
#define GENERATE_DATA_INTERVAL         20000U //milliseconds

/* The resource for which the server is the authority */
#define URI_OBSERVE_RESOURCE           "/number"
const coapUriPath_t gURI_OBSERVE_RESOURCE   = {SizeOfString(URI_OBSERVE_RESOURCE), (uint8_t*)URI_OBSERVE_RESOURCE};

/* Callback function for receiving the messages with URI_OBSERVE_RESOURCE URI-path */    
#define COAP_OBSERVE_RESOURCE \
                {\
                    {APP_ObserveServerRcvReqCb, (coapUriPath_t*)&gURI_OBSERVE_RESOURCE}\
                }

/*==================================================================================================
Private type definitions
==================================================================================================*/


/*==================================================================================================
Private prototypes
==================================================================================================*/
#if COAP_OBSERVE_SERVER
static void APP_ObserveServerUpdateHandle(void *param);
static void APP_ObserveServerRcvReqCb(coapSessionStatus_t sessionStatus, 
                                            void* pData, coapSession_t* pSession, uint32_t dataLen);
static void APP_ObserveServerUpdate(void *param);
#endif

#if COAP_OBSERVE_CLIENT
static void APP_ObserveRcvData(coapSessionStatus_t sessionStatus, void* pData, 
                                            coapSession_t* pSession, uint32_t dataLen);
#endif


/*==================================================================================================
Private global variables declarations
==================================================================================================*/
tmrTimerID_t mCoapObserveGenerateData;

/* Resource value */
uint32_t gResourceValue = 0;

taskMsgQueue_t * appMsgQueue = NULL;

/* Server must increment the sequence ID at each change of value of the resource */
uint8_t mObserveSequenceId;               /*!< sequence ID for each notification 
                                           (LSB 24 bits of Observe option send by server)*/


/*==================================================================================================
Public global variables declarations
==================================================================================================*/

/*==================================================================================================
Public functions
==================================================================================================*/
#if COAP_OBSERVE_SERVER
/*!*************************************************************************************************
\fn    void APP_ObserveStartServer()
\brief This is an application function that starts a CoAP server for a set of resources.

\param [in]       msgQueue                  task message queue
\param [in]       interfaceId               IP interface id

\return       
***************************************************************************************************/
void APP_ObserveStartServer
(   
    taskMsgQueue_t * msgQueue,
    ipIfUniqueId_t ipIfId
)
{   
    
    coapStartUnsecParams_t coapStartUnsecParams = {.port = COAP_DEFAULT_PORT,
                                                   .addrFamily = AF_INET6};
    coapRegCbParams_t callbacksStruct[] = COAP_OBSERVE_RESOURCE; 

    appMsgQueue = msgQueue;
    
    COAP_Server_InitObserve(ipIfId, &coapStartUnsecParams, (coapRegCbParams_t*)callbacksStruct,
                            NumberOfElements(callbacksStruct));
    

    /* Start a periodic timer that will generate a random number and will inform the registered 
    clients about the new value of the number */
    mCoapObserveGenerateData = TMR_AllocateTimer();
    if (gTmrInvalidTimerID_c != mCoapObserveGenerateData)
    {
        TMR_StartIntervalTimer(mCoapObserveGenerateData,GENERATE_DATA_INTERVAL,APP_ObserveServerUpdateHandle,NULL);
    }
}
#endif

#if COAP_OBSERVE_CLIENT
/*!*************************************************************************************************
\fn    void APP_ObserveStartClient()
\brief This is an application function that starts a CoAP observe client for a resource.

\param [in]       msgQueue                  task message queue
\param [in]       interfaceId               IP interface id
\param [in]       pServerIpAddr             pointer to server's IP address
\param [in]       pResource                 pointer to CoAP resource the client wants to observe

\return       
***************************************************************************************************/
void APP_ObserveStartClient
(   
    taskMsgQueue_t * msgQueue,
    ipIfUniqueId_t ipIfId,
    ipAddr_t * pServerIpAddr,
    coapUriPath_t * pResource
)
{   
    
    coapStartUnsecParams_t coapStartUnsecParams = {.port = COAP_DEFAULT_PORT,
                                                   .addrFamily = AF_INET6};

    appMsgQueue = msgQueue;
    
    COAP_Client_InitObserve(ipIfId, &coapStartUnsecParams, NULL, 0);

    COAP_Client_StartObserving(pServerIpAddr, pResource, APP_ObserveRcvData);
}

/*!*************************************************************************************************
\fn    void APP_ObserveStopClient()
\brief This is an application function that stops a CoAP observe client.

\param [in]       msgQueue                  task message queue
\param [in]       interfaceId               IP interface id
\param [in]       pServerIpAddr             pointer to server's IP address
\param [in]       pResource                 pointer to CoAP resource the client wants to observe

\return       
***************************************************************************************************/
void APP_ObserveStopClient
(   
    ipAddr_t * pServerIpAddr,
    coapUriPath_t * pResource
)
{   
    COAP_Client_StopObserving(pServerIpAddr, pResource, APP_ObserveRcvData);
}
#endif



/*==================================================================================================
Private functions
==================================================================================================*/
#if COAP_OBSERVE_SERVER
/*!*************************************************************************************************
\fn void APP_ObserveServerUpdateHandle(void)
\brief  This function is an on timer function that sends a message to update the resource value. 

\retval      none
***************************************************************************************************/

static void APP_ObserveServerUpdateHandle(void *param)
{
    NWKU_SendMsg(APP_ObserveServerUpdate, NULL, appMsgQueue);
}

/*!*************************************************************************************************
\fn void APP_ObserveServerRcvReqCb()
\brief

\param  [in]    sessionStatus   status for CoAP session
\param  [in]    pData           pointer to CoAP message payload
\param  [in]    pSession        pointer to CoAP session
\param  [in]    dataLen         length of CoAP payload

\retval      none
***************************************************************************************************/
static void APP_ObserveServerRcvReqCb
(
    coapSessionStatus_t sessionStatus, 
    void* pData, 
    coapSession_t* pSession,
    uint32_t dataLen
)
{
    /* Check if the client asked for subscription */
    if (pSession->bIsSubscribed == TRUE)
    {   
        /* Add the client to the list of observers */
        COAP_Server_AddObserver(pSession, (coapUriPath_t*)&gURI_OBSERVE_RESOURCE);

        COAP_AddOptionToList(pSession, COAP_OBSERVE_OPTION, (uint8_t*)&pSession->observeOption, sizeof(uint8_t));        

    }
    else
    {
        /* if the client was in the table of observers but this time did not include observe option,
         remove it from the table of observers */
        COAP_Server_RemoveObserver(pSession, (coapUriPath_t*)&gURI_OBSERVE_RESOURCE);         
    }

    /* Send the current value of the resource */
    COAP_Send(pSession, gCoapMsgTypeAckSuccessContent_c, (void*)&gResourceValue, sizeof(gResourceValue));
}

/*!*************************************************************************************************
\fn void APP_ObserveServerUpdate()
\brief

\retval      none
***************************************************************************************************/
static void APP_ObserveServerUpdate(void *param)
{

    RNG_GetRandomNo(&gResourceValue);
    mObserveSequenceId++;

    COAP_Server_NotifyObservers((coapUriPath_t*)&gURI_OBSERVE_RESOURCE, gCoapNonConfirmable_c, 
                                mObserveSequenceId, (uint8_t*)&gResourceValue, sizeof(gResourceValue));
}
#endif

#if COAP_OBSERVE_CLIENT
/*!*************************************************************************************************
\fn void APP_ObserveRcvData()
\brief

\param  [in]    sessionStatus   status for CoAP session
\param  [in]    pData           pointer to CoAP message payload
\param  [in]    pSession        pointer to CoAP session
\param  [in]    dataLen         length of CoAP payload

\retval      none
***************************************************************************************************/
static void APP_ObserveRcvData
(
    coapSessionStatus_t sessionStatus, 
    void* pData, 
    coapSession_t* pSession,
    uint32_t dataLen
)
{
#if THREAD_USE_SHELL
    char remoteAddrStr[INET6_ADDRSTRLEN];

    uint32_t number = ntohal(pData);
    
    if (gCoapSuccess_c == sessionStatus)
    {    
        ntop(AF_INET6, &pSession->remoteAddr, remoteAddrStr, INET6_ADDRSTRLEN);
        shell_printf("new value: 0x%08X from ", number);
        shell_printf(remoteAddrStr);
        shell_printf("\r\n");
        shell_refresh();
    }
#endif
}
#endif    
/* Delimiters */
/*================================================================================================*/


/*==================================================================================================
Private debug functions
==================================================================================================*/
