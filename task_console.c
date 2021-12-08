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
    JOYSTICK_DIR_t dir;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        xQueueReceive(Queue_Console, &dir, portMAX_DELAY);

        if (dir == JOYSTICK_DIR_CENTER) {
            printf("Task_Console: Joystick position - CENTER\n\r");
        }
        if (dir == JOYSTICK_DIR_LEFT) {
            printf("Task_Console: Joystick position - LEFT\n\r");
        }
        if (dir == JOYSTICK_DIR_RIGHT) {
            printf("Task_Console: Joystick position - RIGHT\n\r");
        }
        if (dir == JOYSTICK_DIR_UP) {
            printf("Task_Console: Joystick position - UP\n\r");
        }
        if (dir == JOYSTICK_DIR_DOWN) {
            printf("Task_Console: Joystick position - DOWN\n\r");
        }
    }
}


