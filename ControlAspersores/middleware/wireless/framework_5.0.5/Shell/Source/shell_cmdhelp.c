/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
*
* \file shell_cmdhelp.c
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
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
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

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "shell.h"
#include <string.h>
#include "FunctionLib.h"
#include "MemManager.h"
#include "ModuleInfo.h"

#if (SHELL_ENABLED && SHELL_USE_HELP)
/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
static int8_t DoHelp(uint8_t argc, char * argv[]);
static int8_t DoVer(uint8_t argc, char * argv[]);
#if SHELL_USE_AUTO_COMPLETE
static int8_t DoHelpComplete(uint8_t argc, char * argv[], char last_char, uint8_t maxv, char * cmdv[]);
#endif

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
extern uint8_t  mShellMaxCmdLen;

const cmd_tbl_t CommandFun_Help = 
{
    .name = "help",
    .maxargs = 2,
    .repeatable = 1,
    .cmd = DoHelp,
    .usage = "print command description/usage",
#if SHELL_USE_AUTO_COMPLETE
    .complete = DoHelpComplete,
#endif
    .help = "\r\n"
            "   - print brief description of all commands\r\n"
            "help <command>\r\n"
            "   - print detailed usage of 'command'\r\n"
};

const cmd_tbl_t CommandFun_Ver = 
{
    .name = "version",
    .maxargs = 2,
    .repeatable = 1,
    .cmd = DoVer,
    .usage = "print version of all the registered modules",
#if SHELL_USE_AUTO_COMPLETE
    .complete = NULL,
#endif
    .help = NULL
};

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief  This function will display a list of all registered SW module information.
*
* \param[in]  argc  The number of arguments
* \param[in]  argv  table with command argumens
*
* \return  int8_t  command status (command_ret_t)
*
********************************************************************************** */
static int8_t DoVer(uint8_t argc, char * argv[])
{
    moduleInfo_t *pInfo = gVERSION_TAGS_startAddr_d;

    if( !gVERSION_TAGS_entries_d )
    {
        shell_write("There are no registered modules!");
        SHELL_NEWLINE();
        return CMD_RET_FAILURE;
    }

    while( pInfo < gVERSION_TAGS_endAddr_d )
    {
        shell_write(*pInfo->moduleString);
        SHELL_NEWLINE();
        pInfo++;
    }

    return CMD_RET_SUCCESS;
}
 
/*! *********************************************************************************
* \brief  This function will display a list of all commands with a short usage.
*         If called with argument, it will displat a detailed help for a command
*
* \param[in]  argc  The number of arguments
* \param[in]  argv  table with command argumens
*
* \return  int8_t  command status (command_ret_t)
*
********************************************************************************** */
static int8_t DoHelp(uint8_t argc, char * argv[])
{
    uint16_t i;

    if (argc == 1)
    {
        char * pStr = MEM_BufferAlloc( mShellMaxCmdLen + 2 );
        
        if( pStr )
        {
            for( i=0; i<SHELL_MAX_COMMANDS; i++ )
            {
                if( gpCmdTable[i] )
                {
                    uint16_t len = strlen(gpCmdTable[i]->name);
                    
                    FLib_MemCpy( pStr, gpCmdTable[i]->name, len );
                    FLib_MemSet( &pStr[len], ' ', mShellMaxCmdLen - len + 2); 
                    shell_writeN(pStr, mShellMaxCmdLen + 2);
                    shell_write(gpCmdTable[i]->usage);
                    SHELL_NEWLINE();
                }
            }

            MEM_BufferFree(pStr);
        }
        else
        {
            for( i=0; i<SHELL_MAX_COMMANDS; i++ )
            {
                if( gpCmdTable[i] )
                {
                    shell_write(gpCmdTable[i]->name);
                    shell_writeN(" ", 1);
                    shell_write(gpCmdTable[i]->usage);
                    SHELL_NEWLINE();
                }
            }
        }
    }
    else if (argc == 2)
    {
        for( i=0; i<SHELL_MAX_COMMANDS; i++ )
        {
            if( gpCmdTable[i] && !strcmp(argv[1], gpCmdTable[i]->name))
            {
                if (gpCmdTable[i]->help != NULL)
                {
                    shell_write(gpCmdTable[i]->name);
                    shell_writeN(" - ", 3);
                    shell_write(gpCmdTable[i]->help);
                    SHELL_NEWLINE();
                    return CMD_RET_SUCCESS;
                }
                else
                {
                    shell_write ("- No additional help available.\r\n");
                    return CMD_RET_SUCCESS;
                }
            }

        }
        shell_write( "- No command available.\r\n" );
    }
    return CMD_RET_SUCCESS;
}

#if SHELL_USE_AUTO_COMPLETE
/*! *********************************************************************************
* \brief  This is the autocomplete function for Help. 
*         It will return possible arguments
*
* \param[in]  argc       The number of arguments
* \param[in]  argv       Table with command argumens
* \param[in]  last_char  The Last character received
* \param[in]  maxv       The maximun number of matchs
* \param[in]  cmdv       Table with possible matchs
*
* \return  int8_t  command status (command_ret_t)
*
********************************************************************************** */
static int8_t DoHelpComplete(uint8_t argc, char * argv[], char last_char, uint8_t maxv, char * cmdv[])
{
    uint8_t str_len;
    uint8_t found = 0;
    uint8_t i;
    str_len = strlen(argv[argc-1]);

    switch(argc)
    {
        case 2:
            for( i=0; i<SHELL_MAX_COMMANDS; i++ )
            {
                if(gpCmdTable[i] && !strncmp(argv[argc-1], gpCmdTable[i]->name, str_len))
                {
                    cmdv[found] = gpCmdTable[i]->name;
                    found++;
                }  
            }
            break;
        default:
            break;
    }
    return found;
}
#endif //#if SHELL_USE_AUTO_COMPLETE
#endif
/*******************************************************************************
 * EOF
 ******************************************************************************/