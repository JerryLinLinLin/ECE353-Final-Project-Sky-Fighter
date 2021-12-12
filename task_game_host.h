/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_GAME_HOST_H_
#define TASK_GAME_HOST_H_

#include <main.h>

typedef struct
{
    int x;
    int y;
    int height;
    int width;
} LOCATION;

typedef struct
{
    LOCATION loc;
    ADC_MOVE dir;
    bool in_use;
} BULLET;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_Host(void *pvParameters);

LOCATION boarder_range_validate(LOCATION loc);
bool is_in_boarder(LOCATION loc);

bool is_collided(LOCATION loc1, LOCATION loc2);


#endif /* TASK_CONSOLE_H_ */
