/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_RENDERER_H_
#define TASK_RENDERER_H_

#include <main.h>

extern QueueHandle_t Queue_Renderer;
extern TaskHandle_t Task_Renderer_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Renderer(void *pvParameters);




#endif /* TASK_CONSOLE_H_ */
