/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_GAME_NPC_H_
#define TASK_GAME_NPC_H_

#include <main.h>

//extern QueueHandle_t Queue_Game_NPC;
extern TaskHandle_t Task_Game_NPC1_Handle;
extern TaskHandle_t Task_Game_NPC2_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_NPC(void *pvParameters);

ADC_MOVE generate_random_dir(void);




#endif /* TASK_CONSOLE_H_ */
