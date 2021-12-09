/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Game_Host;
TaskHandle_t Task_Game_Host_Handle;

#define RED_5   0x1F
#define GREEN_6 0x0F
#define BLUE_5  0x0F
#define BLACK 0x0000

#define FG_COLOR (RED_5 << 11)
#define BG_COLOR BLACK



/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_Host(void *pvParameters)
{
    int i = 64;
    int j = 64;

    lcd_draw_image(
      i,
      j,
      wisconsinWidthPixels,
      wisconsinHeightPixels,
      wisconsinBitmaps,
      FG_COLOR,
      BG_COLOR
    );

    ADC_joy_acc_dir current;

    while(1)
    {
//        current.joy = JOYSTICK_DIR_LEFT;
//        current.joy_is_changed = true;

        xQueueReceive(Queue_Game_Host, &current, 1);

//        lcd_draw_animation(
//                i - 20,
//                j,
//                wisconsinWidthPixels,
//                wisconsinHeightPixels,
//                wisconsinBitmaps,
//                FG_COLOR,
//                BG_COLOR,
//               20,
//                MOVE_DIR_LEFT);


            if (current.joy == JOYSTICK_DIR_CENTER)
        {
            continue;
        }

        if (current.joy == JOYSTICK_DIR_LEFT)
        {
            if (!((i < 1 || i > 126) || (j < 1 || j > 126)))
            {
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                i = i - 5;
                lcd_draw_animation(
                        i,
                        j,
                        wisconsinWidthPixels,
                        wisconsinHeightPixels,
                        wisconsinBitmaps,
                        FG_COLOR,
                        BG_COLOR,
                       5,
                        MOVE_DIR_LEFT);
                xSemaphoreGive(Sem_RENDER);
            }


        }
        if (current.joy == JOYSTICK_DIR_RIGHT)
        {
            if (!((i < 1 || i > 126) || (j < 1 || j > 126)))
            {
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                i = i + 5;
                lcd_draw_animation(
                        i,
                        j,
                        wisconsinWidthPixels,
                        wisconsinHeightPixels,
                        wisconsinBitmaps,
                        FG_COLOR,
                        BG_COLOR,
                       5,
                       MOVE_DIR_RIGHT);
                xSemaphoreGive(Sem_RENDER);
            }
        }
        if (current.joy == JOYSTICK_DIR_UP)
        {
            if (!((i < 1 || i > 126) || (j < 1 || j > 126)))
            {
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                j = j - 5;
                lcd_draw_animation(
                        i,
                        j,
                        wisconsinWidthPixels,
                        wisconsinHeightPixels,
                        wisconsinBitmaps,
                        FG_COLOR,
                        BG_COLOR,
                        5,
                        MOVE_DIR_UP);
                xSemaphoreGive(Sem_RENDER);
            }
        }
        if (current.joy == JOYSTICK_DIR_DOWN)
        {
            if (!((i < 1 || i > 126) || (j < 1 || j > 126)))
            {
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                j = j + 5;
                lcd_draw_animation(
                        i,
                        j,
                        wisconsinWidthPixels,
                        wisconsinHeightPixels,
                        wisconsinBitmaps,
                        FG_COLOR,
                        BG_COLOR,
                       5,
                       MOVE_DIR_DOWN);
                xSemaphoreGive(Sem_RENDER);
            }
        }

//            vTaskDelay(pdMS_TO_TICKS(10));

    }
}


