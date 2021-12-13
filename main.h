/*
 * main.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
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
#include <task_song.h>
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
TaskHandle_t Task_Song_Handle;

// define queue
QueueHandle_t Queue_Game_ADC_to_Host; // Sending the JOY and ACC info to host
QueueHandle_t Queue_Game_Host_to_NPC; // Sending bullet info to npc to check if bullet hit a npc
QueueHandle_t Queue_Game_NPC_to_Host; // Sending npc location to host to check collision
QueueHandle_t Queue_Game_Host_NPC_to_Controller; // Sending flag to mark the end of game (win or lose)
QueueHandle_t Queue_Song; // Choosing which sound to play

#endif /* MAIN_H_ */
