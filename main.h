/*
 * main.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* ECE353 Includes */
#include <ece353.h>
#include <image.h>
#include <task_adc_joy_acc.h>
#include <task_console.h>
#include <task_game_host.h>
#include <task_game_npc.h>
#include <task_game_controller.h>

// define semaphore
SemaphoreHandle_t Sem_RENDER;

// define handle
TaskHandle_t Task_Game_Host_Handle;
TaskHandle_t Task_Game_NPC_Handle;
TaskHandle_t Task_Game_Controller_Handle;
TaskHandle_t Task_ADC_Joy_Acc_Bottom_Half_Handle;
TaskHandle_t Task_ADC_Joy_Acc_Timer_Handle;
TaskHandle_t Task_Console_Handle;

// define queue
QueueHandle_t Queue_Game_Host;
QueueHandle_t Queue_Game_Collision;
QueueHandle_t Queue_Console;

#endif /* MAIN_H_ */
