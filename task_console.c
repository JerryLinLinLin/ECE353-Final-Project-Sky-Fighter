/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Console(void *pvParameters)
{
    ADC_joy_acc_dir current;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        xQueueReceive(Queue_Console, &current, portMAX_DELAY);

        if (current.joy_is_changed == true) {
            if (current.joy == JOYSTICK_DIR_CENTER) {
                        printf("Task_Console: Joystick position - CENTER\n\r");
                    }
                    if (current.joy == JOYSTICK_DIR_LEFT) {
                        printf("Task_Console: Joystick position - LEFT\n\r");
                    }
                    if (current.joy == JOYSTICK_DIR_RIGHT) {
                        printf("Task_Console: Joystick position - RIGHT\n\r");
                    }
                    if (current.joy == JOYSTICK_DIR_UP) {
                        printf("Task_Console: Joystick position - UP\n\r");
                    }
                    if (current.joy == JOYSTICK_DIR_DOWN) {
                        printf("Task_Console: Joystick position - DOWN\n\r");
                    }
        }

        if (current.acc_is_changed == true) {
            if (current.acc == ACC_DIR_CENTER) {
                        printf("Task_Console: Accelerometer position - CENTER\n\r");
                    }
                    if (current.acc == ACC_DIR_LEFT) {
                        printf("Task_Console: Accelerometer position - LEFT\n\r");
                    }
                    if (current.acc == ACC_DIR_RIGHT) {
                        printf("Task_Console: Accelerometer position - RIGHT\n\r");
                    }
                    if (current.acc == ACC_DIR_UP) {
                        printf("Task_Console: Accelerometer position - UP\n\r");
                    }
                    if (current.acc == ACC_DIR_DOWN) {
                        printf("Task_Console: Accelerometer position - DOWN\n\r");
                    }
        }

    }
}


