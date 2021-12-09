/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_GAME_HOST_H_
#define TASK_GAME_HOST_H_

#include <main.h>

extern QueueHandle_t Queue_Game_Host;
extern TaskHandle_t Task_Game_Host_Handle;

typedef struct
{
    int x;
    int y;
    int height;
    int width;
} LOCATION;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_Host(void *pvParameters);

LOCATION boarder_range_validate(LOCATION loc);




#endif /* TASK_CONSOLE_H_ */
