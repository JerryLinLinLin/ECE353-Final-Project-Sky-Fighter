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
    JOYSTICK_DIR_t dir;
    JOYSTICK_DIR_t prev_dir = JOYSTICK_DIR_CENTER;


    while(1)
    {
        /* ADD CODE
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


        /*
         * Set the dir variable to one of the following values based
         * on the values of JOYSTICK_X_DIR and JOYSTIC_Y_DIR
         */
        if(JOYSTICK_X_DIR < VOLT_0P85)
        {
           dir = JOYSTICK_DIR_LEFT;
        }
        else if(JOYSTICK_X_DIR > VOLT_2P50)
        {
            dir = JOYSTICK_DIR_RIGHT;
        }
        else if(JOYSTICK_Y_DIR < VOLT_0P85)
        {
            dir = JOYSTICK_DIR_DOWN;
        }
        else if(JOYSTICK_Y_DIR > VOLT_2P50)
        {
            dir = JOYSTICK_DIR_UP;
        }
        else
        {
            dir = JOYSTICK_DIR_CENTER;
        }


        /* ADD CODE
         * Send dir to Queue_Console if the the current direction
         * of the joystick does not match the previous direction of the joystick
         */
        if (dir != prev_dir) {
            xQueueSendToBack(Queue_Console, &dir, portMAX_DELAY);
        }


        /* ADD CODE
         * Update the prev_dir of the joystick
         */
        prev_dir = dir;
    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    ece353_rgb(false,true,false);

    JOYSTICK_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    JOYSTICK_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt

    ACC_X_DIR = ADC14->MEM[2];
    ACC_Y_DIR = ADC14->MEM[3];
    ACC_Z_DIR = ADC14->MEM[4];


    /* ADD CODE
     * Send a task notification to Task_Joystick_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_ADC_Joy_Acc_Bottom_Half_Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}



