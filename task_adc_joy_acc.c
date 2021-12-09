/*
 * task_led.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <main.h>


 TaskHandle_t Task_ADC_Joy_Acc_Bottom_Half_Handle;
 TaskHandle_t Task_ADC_Joy_Acc_Timer_Handle;

 volatile uint32_t JOYSTICK_X_DIR = 0;
 volatile uint32_t JOYSTICK_Y_DIR = 0;

 volatile uint32_t ACC_X_DIR = 0;
 volatile uint32_t ACC_Y_DIR = 0;
 volatile uint32_t ACC_Z_DIR = 0;


 /******************************************************************************
 * Used to start an ADC14 Conversion
 ******************************************************************************/
 void Task_ADC_Joy_Acc_Timer(void *pvParameters)
 {
     while(1)
     {
         /* 
          * Start the ADC conversion
          */
         ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;


         /* 
          * Delay 50mS
          */
         vTaskDelay(pdMS_TO_TICKS(50));

     }
 }


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_ADC_Joy_Acc_Bottom_Half(void *pvParameters)
{
    JOYSTICK_DIR_t joy_dir;
    JOYSTICK_DIR_t joy_prev_dir = JOYSTICK_DIR_CENTER;

    ACC_DIR_t acc_dir;
    ACC_DIR_t acc_prev_dir = ACC_DIR_CENTER;


    while(1)
    {
        /* ADD CODE
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ADC_joy_acc_dir current;

        // joystick
        if(JOYSTICK_X_DIR < VOLT_0P85)
        {
           joy_dir = JOYSTICK_DIR_LEFT;
        }
        else if(JOYSTICK_X_DIR > VOLT_2P50)
        {
            joy_dir = JOYSTICK_DIR_RIGHT;
        }
        else if(JOYSTICK_Y_DIR < VOLT_0P85)
        {
            joy_dir = JOYSTICK_DIR_DOWN;
        }
        else if(JOYSTICK_Y_DIR > VOLT_2P50)
        {
            joy_dir = JOYSTICK_DIR_UP;
        }
        else
        {
            joy_dir = JOYSTICK_DIR_CENTER;
        }

        // accelerometer
        if((ACC_X_DIR > (VOLT_2P31 - (ACC_RANGE * 3))) &&  (ACC_X_DIR < (VOLT_2P31 + (ACC_RANGE * 3))))
        {
           acc_dir = ACC_DIR_RIGHT;
        }
        else if((ACC_X_DIR > (VOLT_0P99 - (ACC_RANGE * 3))) &&  (ACC_X_DIR < (VOLT_0P99 + (ACC_RANGE * 3))))
        {
            acc_dir = ACC_DIR_LEFT;
        }
        else if((ACC_Z_DIR > (VOLT_2P31 - ACC_RANGE)) &&  (ACC_Z_DIR < (VOLT_2P31 + ACC_RANGE)))
        {
            acc_dir = ACC_DIR_UP;
        }
        else if((ACC_Z_DIR > (VOLT_0P99 - ACC_RANGE)) &&  (ACC_Z_DIR < (VOLT_0P99 + ACC_RANGE)))
        {
            acc_dir = ACC_DIR_DOWN;
        }
        else
        {
            acc_dir = ACC_DIR_CENTER;
        }

        // save data
        current.joy = joy_dir;
        current.acc = acc_dir;

        // mark if changed
        current.joy_is_changed = joy_dir != joy_prev_dir;
        current.acc_is_changed = acc_dir != acc_prev_dir;

        // send
        if (current.joy_is_changed || current.acc_is_changed) {
            xQueueSendToBack(Queue_Console, &current, portMAX_DELAY);
        }


        /* ADD CODE
         * Update the prev_dir of the joystick
         */
        joy_prev_dir = joy_dir;
        acc_prev_dir = acc_dir;
    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    JOYSTICK_X_DIR = ADC14->MEM[0];
    JOYSTICK_Y_DIR = ADC14->MEM[1];

    ACC_X_DIR = ADC14->MEM[2];
    ACC_Y_DIR = ADC14->MEM[3];
    ACC_Z_DIR = ADC14->MEM[4];


    /*
     * Send a task notification to Task_Joystick_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_ADC_Joy_Acc_Bottom_Half_Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}



