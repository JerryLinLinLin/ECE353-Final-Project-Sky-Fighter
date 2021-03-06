/*
 * task_game_controller.c
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#include <main.h>


/******************************************************************************
* Task used to manage game process, to start the game and check end condition
******************************************************************************/
void Task_Game_Controller(void *pvParameters)
{
    int phase = 0; // detect current process phase

    int press_start_flash_count = 0; // count for flash press start

    uint8_t S1_debounce_state = 0x00; // s1 debouce

    bool is_intro_song_sent = false; // flag to hold intro song
    bool is_game_over_song_sent = false; // flag to hold game over song

    while(1)
    {
        S1_debounce_state = S1_debounce_state << 1; // move debounce

        // welcome screen
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

            if (!is_intro_song_sent) {
                is_intro_song_sent = true;
                // send song

                SOUND sound = PLAY_INTRO_SONG;
                xQueueSendToBack(Queue_Song, &sound, 0);
            }

            // detect if S1 is pressed to start the game
            if (ece353_s1_pressed()) {
                S1_debounce_state = S1_debounce_state | BIT0;
            }
            if (S1_debounce_state == 0x7F)
            {
                phase = 1; // start game
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

                // game start sound effect
                SOUND sound = PLAYER_SHOOTING;
                xQueueSendToBack(Queue_Song, &sound, 0);

                // Release Host and NPC semaphore
                xSemaphoreGive(Sem_GAME_HOST);
                xSemaphoreGive(Sem_GAME_NPC);
            }
        }
        // game is running
        if (phase == 1) {
            bool win = false;
            // wait until receive a result
            xQueueReceive(Queue_Game_Host_NPC_to_Controller, &win, portMAX_DELAY);
            if (win) {
                // suspend game processes
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
                        COLOR_CODE[YELLOW1]
                );
                xSemaphoreGive(Sem_RENDER);

                if (!is_game_over_song_sent) {
                    is_game_over_song_sent = true;
                    // send song you win
                    SOUND sound = YOU_WIN;
                    xQueueSendToBack(Queue_Song, &sound, 0);
                }
            }
            else {
                // suspend game processes
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

                if (!is_game_over_song_sent) {
                    is_game_over_song_sent = true;
                    // send song game over
                    SOUND sound = GAME_OVER;
                    xQueueSendToBack(Queue_Song, &sound, 0);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}



