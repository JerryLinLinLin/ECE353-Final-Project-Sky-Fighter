/*
 * task_led.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <main.h>


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
    ADC_MOVE joy_dir = { .center = true, .left = false, .right = false, .up =
                                 false,
                         .down = false };
    ADC_MOVE joy_prev_dir = { .center = true, .left = false, .right = false,
                              .up = false, .down = false };

    ADC_MOVE acc_dir = { .center = true, .left = false, .right = false, .up =
                                 false,
                         .down = false };
    ADC_MOVE acc_prev_dir = { .center = true, .left = false, .right = false,
                              .up = false, .down = false };

    ADC_joy_acc_dir current =
            { .joy = { .center = true, .left = false, .right = false, .up =
                               false,
                       .down = false },
              .acc = { .center = true, .left = false, .right = false, .up =
                               false,
                       .down = false },
              .acc_is_changed = false, .joy_is_changed = false };


    while(1)
    {
        /* ADD CODE
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // joystick
        if(JOYSTICK_X_DIR < VOLT_0P85)
        {
           joy_dir.left = true;
        }
        else
        {
            joy_dir.left = false;
        }

        if(JOYSTICK_X_DIR > VOLT_2P50)
        {
            joy_dir.right = true;
        }
        else
        {
            joy_dir.right = false;
        }

        if(JOYSTICK_Y_DIR < VOLT_0P85)
        {
            joy_dir.down = true;
        }
        else
        {
            joy_dir.down = false;
        }

        if(JOYSTICK_Y_DIR > VOLT_2P50)
        {
            joy_dir.up = true;
        }
        else
        {
            joy_dir.up = false;
        }

        if (!(joy_dir.left || joy_dir.right || joy_dir.down || joy_dir.up)) {
            joy_dir.center = true;
        }
        else
        {
            joy_dir.center = false;
        }

        // accelerometer
        if((ACC_X_DIR > (VOLT_2P31 - (ACC_RANGE * 5))) &&  (ACC_X_DIR < (VOLT_2P31 + (ACC_RANGE * 5))))
        {
           acc_dir.right = true;
        }
        else
        {
            acc_dir.right = false;
        }

        if((ACC_X_DIR > (VOLT_0P99 - (ACC_RANGE * 5))) &&  (ACC_X_DIR < (VOLT_0P99 + (ACC_RANGE * 5))))
        {
            acc_dir.left = true;
        }
        else
        {
            acc_dir.left = false;
        }

        if((ACC_Z_DIR > (VOLT_2P31 - ACC_RANGE)) &&  (ACC_Z_DIR < (VOLT_2P31 + ACC_RANGE)))
        {
            acc_dir.up = true;
        }
        else
        {
            acc_dir.up = false;
        }

        if((ACC_Z_DIR > (VOLT_0P99 - ACC_RANGE * 10)) &&  (ACC_Z_DIR < (VOLT_0P99 + ACC_RANGE * 10)))
        {
            acc_dir.down = true;
        }
        else
        {
            acc_dir.down = false;
        }

        if (!(acc_dir.left || acc_dir.right || acc_dir.down || acc_dir.up)) {
            acc_dir.center = true;
        }
        else
        {
            acc_dir.center = false;
        }

        // save data
        current.joy = joy_dir;
        current.acc = acc_dir;

        // mark if changed
        current.joy_is_changed = !ADC_MOVE_compare(&joy_dir, &joy_prev_dir);
        current.acc_is_changed = !ADC_MOVE_compare(&acc_dir, &acc_prev_dir);

        // send
        xQueueSendToBack(Queue_Game_ADC_to_Host, &current, 0);

        /* ADD CODE
         * Update the prev_dir of the joystick
         */
        joy_prev_dir = joy_dir;
        acc_prev_dir = acc_dir;

//        vTaskDelay(pdMS_TO_TICKS(10));
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
//    vTaskDelay(pdMS_TO_TICKS(50));
}

bool ADC_MOVE_compare(ADC_MOVE *m1, ADC_MOVE *m2)
{
    if (m1->center == m2->center && m1->left == m2->left
            && m1->right == m2->right && m1->up == m2->up
            && m1->down == m2->down)
    {
        return true;
    }
    return false;
}

