/*
 * task_adc_joy_acc.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
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

/**
 * store and record an adc movement
 */
typedef struct
{
    bool center;
    bool left;
    bool right;
    bool up;
    bool down;
} ADC_MOVE;

/**
 * used to send to other tasks
 */
typedef struct
{
    ADC_MOVE joy;
    ADC_MOVE acc;
    bool joy_is_changed;
    bool acc_is_changed;
} ADC_joy_acc_dir;

/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_ADC_Joy_Acc_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_ADC_Joy_Acc_Bottom_Half(void *pvParameters);

/******************************************************************************
* ADC14 IRQ Handler
******************************************************************************/
void ADC14_IRQHandler(void);

/**
 * Compare two ADC_MOVE structure if they are same
 * @param m1
 * @param m2
 * @return true if same, false otherwise
 */
bool ADC_MOVE_compare(ADC_MOVE *m1, ADC_MOVE *m2);


#endif /* TASK_ADC_JOY_ACC_H_ */
