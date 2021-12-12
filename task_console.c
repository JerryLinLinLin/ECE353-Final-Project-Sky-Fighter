/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>


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

//        if (current.joy_is_changed == true) {
//            if (current.joy.center) {
//                        printf("DEBUG: Joystick position - CENTER\n\r");
//                    }
//                    if (current.joy.left) {
//                        printf("DEBUG: Joystick position - LEFT\n\r");
//                    }
//                    if (current.joy.right) {
//                        printf("DEBUG: Joystick position - RIGHT\n\r");
//                    }
//                    if (current.joy.up) {
//                        printf("DEBUG: Joystick position - UP\n\r");
//                    }
//                    if (current.joy.down) {
//                        printf("DEBUG: Joystick position - DOWN\n\r");
//                    }
//        }
//
//        if (current.acc_is_changed == true) {
//            if (current.acc.center) {
//                        printf("DEBUG: Accelerometer position - CENTER\n\r");
//                    }
//                    if (current.acc.left) {
//                        printf("DEBUG: Accelerometer position - LEFT\n\r");
//                    }
//                    if (current.acc.right) {
//                        printf("DEBUG: Accelerometer position - RIGHT\n\r");
//                    }
//                    if (current.acc.up) {
//                        printf("DEBUG: Accelerometer position - UP\n\r");
//                    }
//                    if (current.acc.down) {
//                        printf("DEBUG: Accelerometer position - DOWN\n\r");
//                    }
//        }

    }
}


