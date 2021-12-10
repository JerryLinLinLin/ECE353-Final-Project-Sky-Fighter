/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Game_NPC;
TaskHandle_t Task_Game_NPC_Handle;

#define RED_5   0x1F
#define GREEN_6 0x0F
#define BLUE_5  0x0F
#define BLACK 0x0000

#define FG_COLOR (RED_5 << 11)
#define BG_COLOR BLACK

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_NPC(void *pvParameters)
{
    srand(time(0));

    LOCATION ufo1_loc = {.x = 64, .y = 20, .height = ufo1HeightPixels,
                        .width = ufo1WidthPixels};
    ADC_MOVE ufo1_dir = generate_random_dir();

    unsigned long long move_time_count = 0;

    lcd_draw_image(
            ufo1_loc.x,
            ufo1_loc.y,
            ufo1_loc.width,
            ufo1_loc.height,
            ufo1Bitmaps,
      FG_COLOR,
      BG_COLOR
    );

    while(1)
    {
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
        xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
        lcd_draw_image(
                ufo1_loc.x,
                ufo1_loc.y,
                ufo1_loc.width,
                ufo1_loc.height,
                ufo1Bitmaps,
          FG_COLOR,
          BG_COLOR
        );
        xSemaphoreGive(Sem_RENDER);
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


