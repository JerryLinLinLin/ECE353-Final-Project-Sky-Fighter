/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_GAME_NPC_H_
#define TASK_GAME_NPC_H_

#include <main.h>

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_NPC(void *pvParameters);

ADC_MOVE generate_random_dir(void);

typedef struct
{
    int height;
    int width;
    int type;
    const uint8_t *image;
    COLOR_INDEX color;
    int hp;
} NPC_TYPE;


#endif /* TASK_CONSOLE_H_ */
