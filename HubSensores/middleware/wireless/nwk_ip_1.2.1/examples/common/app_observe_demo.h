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

#ifndef _APP_OBSERVE_DEMO_H
#define _APP_OBSERVE_DEMO_H
/*!=================================================================================================
\file       app_observe_demo.h
\brief      This is a header file for the app_observe_demo module.

\copyright  (c) Copyright 2016, Freescale, Inc.  All rights reserved.
==================================================================================================*/

/*==================================================================================================
Include Files
==================================================================================================*/


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
);

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
);

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
);


#ifdef __cplusplus
}
#endif
/*================================================================================================*/
#endif  /* _APP_OBSERVE_DEMO_H */
