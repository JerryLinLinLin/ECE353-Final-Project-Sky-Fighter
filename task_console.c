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



        /* ADD CODE
         * based on the message that was received, print out one of the following
         * message to the UART.
         *
         *  "Task_Console: Joystick position - CENTER\n\r"
         *  "Task_Console: Joystick position - LEFT\n\r"
         *  "Task_Console: Joystick position - RIGHT\n\r"
         *  "Task_Console: Joystick position - UP\n\r"
         *  "Task_Console: Joystick position - DOWN\n\r"
         *
         * NOTE, the UART is only accessed in this task, so
         * there is no need to use a semaphore for mutual exclusion of the UART.
         */
        if (dir == JOYSTICK_DIR_CENTER) {
//            printf("Task_Console: Joystick position - CENTER\n\r");
            ece353_rgb(false,false,true);
        }
        if (dir == JOYSTICK_DIR_LEFT) {
//            printf("Task_Console: Joystick position - LEFT\n\r");
            ece353_rgb(false,true,false);
        }
        if (dir == JOYSTICK_DIR_RIGHT) {
//            printf("Task_Console: Joystick position - RIGHT\n\r");
            ece353_rgb(true,false,false);
        }
        if (dir == JOYSTICK_DIR_UP) {
//            printf("Task_Console: Joystick position - UP\n\r");
        }
        if (dir == JOYSTICK_DIR_DOWN) {
//            printf("Task_Console: Joystick position - DOWN\n\r");
        }
    }
}


