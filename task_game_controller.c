/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>


/******************************************************************************
* Task used to manage game process
******************************************************************************/
void Task_Game_Controller(void *pvParameters)
{
    int phase = 0;

    int press_start_flash_count = 0;

    uint8_t S1_debounce_state = 0x00;

    while(1)
    {
        S1_debounce_state = S1_debounce_state << 1;

        if (phase == 0) {

            // Render Title
            xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
            lcd_draw_image(
                    64,
                    45,
                    skyfighter0WidthPixels,
                    skyfighter0HeightPixels,
                    skyfighter0Bitmaps,
                    COLOR_CODE[BLACK],
                    COLOR_CODE[generate_random_in_range(0, 12)]
            );
            xSemaphoreGive(Sem_RENDER);

            // make press start flash
            uint16_t press_start_color = COLOR_CODE[WHITE];
            if (press_start_flash_count > 7) {

                press_start_color = COLOR_CODE[BLACK];

            }
            if (press_start_flash_count > 14) {
                press_start_flash_count = 0;
            }
            press_start_flash_count ++;

            // render press to start
            xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
            lcd_draw_image(
                    64,
                    105,
                    pressstartWidthPixels,
                    pressstartHeightPixels,
                    pressstartBitmaps,
                    press_start_color,
                    COLOR_CODE[BLACK]
            );
            xSemaphoreGive(Sem_RENDER);

            // detect if S1 is pressed to start the game
            if (ece353_s1_pressed()) {
                S1_debounce_state = S1_debounce_state | BIT0;
            }
            if (S1_debounce_state == 0x7F)
            {
                phase = 1;
                // Render to empty screen
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                lcd_draw_rectangle(
                        64,
                        64,
                        128,
                        128,
                        COLOR_CODE[BLACK]
                );
                xSemaphoreGive(Sem_RENDER);

                // Release Host and NPC semaphore
                xSemaphoreGive(Sem_GAME_HOST);
                xSemaphoreGive(Sem_GAME_NPC);
            }
        }
        if (phase == 1) {
            bool win = false;
            xQueueReceive(Queue_Game_Host_to_Controller, &win, portMAX_DELAY);
            if (win) {
                vTaskSuspend(Task_Game_Host_Handle);
                vTaskSuspend(Task_Game_NPC_Handle);
                // render win screen
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                lcd_draw_image(
                        64,
                        64,
                        you_winWidthPixels,
                        you_winHeightPixels,
                        you_winBitmaps,
                        COLOR_CODE[BLACK],
                        COLOR_CODE[GREEN2]
                );
                xSemaphoreGive(Sem_RENDER);
            }
            else {
                vTaskSuspend(Task_Game_Host_Handle);
                vTaskSuspend(Task_Game_NPC_Handle);
                // render game over screen
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                lcd_draw_image(
                        64,
                        64,
                        game_overWidthPixels,
                        game_overHeightPixels,
                        game_overBitmaps,
                        COLOR_CODE[RED2],
                        COLOR_CODE[BLACK]
                );
                xSemaphoreGive(Sem_RENDER);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}



