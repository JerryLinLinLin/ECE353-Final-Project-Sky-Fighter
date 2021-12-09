/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Game_Host;
TaskHandle_t Task_Game_Host_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_Host(void *pvParameters)
{

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */

    }
}


