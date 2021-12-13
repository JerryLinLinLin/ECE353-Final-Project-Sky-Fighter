/*
 * main.c
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#include "main.h"

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    ece353_all_setup();

    __enable_irq();

    // print welcome message
    printf("\n\r");
    printf("*********************************************\n\r");
    printf("ECE 353 Final Project - Sky Fighter \n\r");
    printf("*********************************************\n\r");
    printf("\n\r");
    printf("Goal: You will need to control a jet fighter to defeat Alien! Use your gun to fight against them and remember do not be caught. "
            "Good Luck Commander! \n\r");
    printf("\n\r");
    printf("Key Control: \n\r");
    printf("        Accelerometer:  Move fighter in left, right, up, down, and diagonal. \n\r");
    printf("        Joystick:       Control your gun direction. Target to Alien! \n\r");
    printf("        S1 Button:      Press to shoot a bullet! \n\r");
    printf("\n\r");
    printf("Long Press S1 Button to Start the Game...");
    printf("\n\r");

    // initialize queue
    Queue_Game_ADC_to_Host = xQueueCreate(100,sizeof(ADC_joy_acc_dir));
    Queue_Game_NPC_to_Host = xQueueCreate(100,sizeof(LOCATION));
    Queue_Game_Host_to_NPC = xQueueCreate(1,sizeof(bool));
    Queue_Game_Host_NPC_to_Controller = xQueueCreate(1,sizeof(bool));
    Queue_Song = xQueueCreate(10, sizeof(SOUND));

    // initialize semaphore
    Sem_RENDER = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_RENDER);
    Sem_PRINT = xSemaphoreCreateBinary();
    xSemaphoreGive(Sem_PRINT);
    Sem_GAME_HOST = xSemaphoreCreateBinary();
    Sem_GAME_NPC = xSemaphoreCreateBinary();

    // create tasks
    xTaskCreate
    (   Task_Song,
        "Task_Song",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &Task_Song_Handle
    );

    xTaskCreate
    (   Task_Game_Controller,
        "Task_Game_Controller",
        configMINIMAL_STACK_SIZE,
        NULL,
        2,
        &Task_Game_Controller_Handle
    );

    xTaskCreate
    (   Task_Game_NPC,
        "Task_Game_NPC",
        configMINIMAL_STACK_SIZE,
        NULL,
        3,
        &Task_Game_NPC_Handle
    );

    xTaskCreate
    (   Task_Game_Host,
        "Task_Game_Host",
        1024,
        NULL,
        4,
        &Task_Game_Host_Handle
    );

    xTaskCreate
    (   Task_ADC_Joy_Acc_Timer,
        "Task_ADC_Joy_Acc_Timer",
        configMINIMAL_STACK_SIZE,
        NULL,
        6,
        &Task_ADC_Joy_Acc_Timer_Handle
    );

    xTaskCreate
    (   Task_ADC_Joy_Acc_Bottom_Half,
        "Task_ADC_Joy_Acc_Bottom_Half",
        1024,
        NULL,
        7,
        &Task_ADC_Joy_Acc_Bottom_Half_Handle
    );


    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
