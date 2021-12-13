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
#include <string.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* ECE353 Includes */
#include <ece353.h>
#include <image.h>
#include <buzzer.h>
#include <task_adc_joy_acc.h>
#include <task_game_host.h>
#include <task_game_npc.h>
#include <task_game_controller.h>

// define semaphore
SemaphoreHandle_t Sem_RENDER;
SemaphoreHandle_t Sem_PRINT;
SemaphoreHandle_t Sem_GAME_HOST;
SemaphoreHandle_t Sem_GAME_NPC;

// define handle
TaskHandle_t Task_Game_Host_Handle;
TaskHandle_t Task_Game_NPC_Handle;
TaskHandle_t Task_Game_Controller_Handle;
TaskHandle_t Task_ADC_Joy_Acc_Bottom_Half_Handle;
TaskHandle_t Task_ADC_Joy_Acc_Timer_Handle;

// define queue
QueueHandle_t Queue_Game_ADC_to_Host;
QueueHandle_t Queue_Game_Host_to_NPC;
QueueHandle_t Queue_Game_NPC_to_Host;
QueueHandle_t Queue_Game_Host_to_Controller;

#endif /* MAIN_H_ */
