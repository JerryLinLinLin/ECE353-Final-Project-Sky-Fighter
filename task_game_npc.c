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
void Task_Game_NPC(void *pvParameters)
{
    // wait for controller
    xSemaphoreTake(Sem_GAME_NPC, portMAX_DELAY);

    srand(time(0));

    NPC_TYPE cuurent_npc = { .height = ufo1HeightPixels, .width =
                                     ufo1WidthPixels,
                             .type = 0, .color = RED1, .hp = 10, .image = ufo1Bitmaps};

    LOCATION ufo1_loc = {.x = 64, .y = 20, .height = cuurent_npc.height,
                        .width = cuurent_npc.width};
    ADC_MOVE ufo1_dir = generate_random_dir();

    unsigned long long move_time_count = 0;

    // if a new npc appears
    bool new_npc = true;

    int level = 1;

    int a;

    while(1)
    {

        // print welcome message
        if (new_npc) {
            for (a=0; a < 10; a++);
            new_npc = false;
            xSemaphoreTake(Sem_PRINT, portMAX_DELAY);
            char string[20];
            sprintf(string, "%d", level);
            printf("LEVEL ");
            printf(string);
            printf("\n\r");
            printf("A new enemy appears. Eliminate it! \n\r");
            xSemaphoreGive(Sem_PRINT);
        }

        move_time_count++;
        if (move_time_count > 20 || is_in_boarder(ufo1_loc)) {
            ufo1_dir = generate_random_dir();
            move_time_count = 0;
        }
        if (ufo1_dir.left && ufo1_dir.up)
        {
            ufo1_loc.x--;
            ufo1_loc.y--;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (ufo1_dir.right && ufo1_dir.up)
        {
            ufo1_loc.x++;
            ufo1_loc.y--;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (ufo1_dir.left && ufo1_dir.down)
        {
            ufo1_loc.x--;
            ufo1_loc.y++;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (ufo1_dir.right && ufo1_dir.down)
        {
            ufo1_loc.x++;
            ufo1_loc.y++;
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        if (ufo1_dir.left)
        {
            ufo1_loc.x--;
        }
        if (ufo1_dir.right)
        {
            ufo1_loc.x++;
        }
        if (ufo1_dir.up)
        {
            ufo1_loc.y--;
        }
        if (ufo1_dir.down)
        {
            ufo1_loc.y++;
        }

        ufo1_loc = boarder_range_validate(ufo1_loc);
        xQueueSendToBack(Queue_Game_NPC_to_Host, &ufo1_loc, 0);

        bool flash = 0;
        xQueueReceive(Queue_Game_Host_to_NPC, &flash, 0);
        if (flash) {
            cuurent_npc.hp--;
            // print hit message
            xSemaphoreTake(Sem_PRINT, portMAX_DELAY);
            char string2[20];
            sprintf(string2, "%d", cuurent_npc.hp);
            printf("You hit enemy! Enemy remaining HP: ");
            printf(string2);
            printf("\n\r");
            xSemaphoreGive(Sem_PRINT);

            if (cuurent_npc.hp == 0) {
                // target eliminated
                xSemaphoreTake(Sem_PRINT, portMAX_DELAY);
                printf("You has eliminated the enemy! Congratulation\n\r");
                xSemaphoreGive(Sem_PRINT);

                // render image with explosion
                xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                lcd_draw_image(
                        ufo1_loc.x,
                        ufo1_loc.y,
                        explosionWidthPixels,
                        explosionHeightPixels,
                        explosionBitmaps,
                        COLOR_CODE[BLACK],
                        COLOR_CODE[YELLOW1]
                );
                xSemaphoreGive(Sem_RENDER);
               for (a=0; a < 10; a++);
               level++;
               lcd_draw_image(
                       ufo1_loc.x,
                       ufo1_loc.y,
                       explosionWidthPixels,
                       explosionHeightPixels,
                       explosionBitmaps,
                       COLOR_CODE[BLACK],
                       COLOR_CODE[BLACK]
               );
               xSemaphoreGive(Sem_RENDER);

                if (level > 2) {
                    xSemaphoreTake(Sem_PRINT, portMAX_DELAY);
                    printf("YOU WIN! Congratulation\n\r");
                    xSemaphoreGive(Sem_PRINT);
                    bool win = true;
                    xQueueSendToBack(Queue_Game_Host_to_Controller, &win, 0);
                    continue;
                }

                // re initialize
                new_npc = true;
                cuurent_npc.hp = 20;
                cuurent_npc.image = ufo2Bitmaps;
                cuurent_npc.height = ufo2HeightPixels;
                cuurent_npc.width = ufo2WidthPixels;
                cuurent_npc.color = PURPLE1;
                ufo1_loc.x = 64;
                ufo1_loc.y = 20;
                ufo1_loc.height = cuurent_npc.height;
                ufo1_loc.width = cuurent_npc.width;

            }

            // render image with white
            xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
            lcd_draw_image(
                    ufo1_loc.x,
                    ufo1_loc.y,
                    cuurent_npc.width,
                    cuurent_npc.height,
                    cuurent_npc.image,
                    COLOR_CODE[WHITE],
                    COLOR_CODE[BLACK]
            );
            xSemaphoreGive(Sem_RENDER);
        }
        else {
            // render image
            xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
            lcd_draw_image(
                    ufo1_loc.x,
                    ufo1_loc.y,
                    cuurent_npc.width,
                    cuurent_npc.height,
                    cuurent_npc.image,
                    COLOR_CODE[cuurent_npc.color],
                    COLOR_CODE[BLACK]
            );
            xSemaphoreGive(Sem_RENDER);
        }
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}

ADC_MOVE generate_random_dir(void) {
    ADC_MOVE dir = { .center = false, .left = rand() & 1, .right = rand() & 1,
                              .up = rand() & 1, .down = rand() & 1 };
    while (dir.left == dir.right == true) {
        dir.left = rand() & 1;
        dir.right = rand() & 1;
    }
    while (dir.up == dir.down == true) {
        dir.up = rand() & 1;
        dir.down = rand() & 1;
    }
    return dir;
}


