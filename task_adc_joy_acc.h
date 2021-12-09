/*
 * task_print1.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_ADC_JOY_ACC_H_
#define TASK_ADC_JOY_ACC_H_

#include "main.h"

#define VOLT_0P85  1056      // 0.85 /(3.3/4096)
#define VOLT_2P50  3103      // 2.50 /(3.3/4096)

// from https://www.mouser.com/datasheet/2/348/KXTC9-2050_Specifications_Rev_2-1297883.pdf
#define VOLT_2P31 ((int)(2.31/(3.3/4096))) // 2867      // 2.31 /(3.3/4096)
#define VOLT_0P99 ((int)(0.99/(3.3/4096))) // 1228      // 0.99 /(3.3/4096)
#define VOLT_1P65 ((int)(1.65/(3.3/4096))) // 2048      // 1.65 /(3.3/4096)
#define ACC_RANGE 100       // Error range of accelerometer

extern TaskHandle_t Task_ADC_Joy_Acc_Timer_Handle;
extern TaskHandle_t Task_ADC_Joy_Acc_Bottom_Half_Handle;

typedef enum {
    JOYSTICK_DIR_CENTER,
    JOYSTICK_DIR_LEFT,
    JOYSTICK_DIR_RIGHT,
    JOYSTICK_DIR_UP,
    JOYSTICK_DIR_DOWN,
} JOYSTICK_DIR_t;

typedef enum {
    ACC_DIR_CENTER,
    ACC_DIR_LEFT,
    ACC_DIR_RIGHT,
    ACC_DIR_UP,
    ACC_DIR_DOWN,
} ACC_DIR_t;

typedef struct
{
    JOYSTICK_DIR_t joy;
    ACC_DIR_t acc;
} ADC_joy_acc_dir;

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_ADC_Joy_Acc_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_ADC_Joy_Acc_Bottom_Half(void *pvParameters);

void ADC14_IRQHandler(void);


#endif /* TASK_ADC_JOY_ACC_H_ */
