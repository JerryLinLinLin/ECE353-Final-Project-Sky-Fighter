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

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* ECE353 Includes */
#include <ece353.h>
#include <task_adc_joy_acc.h>
#include <task_console.h>
#include <task_game_host.h>
#include <image.h>
#include <task_game_npc.h>

SemaphoreHandle_t Sem_RENDER;


#endif /* MAIN_H_ */
