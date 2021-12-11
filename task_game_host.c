/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

#define FG_COLOR (RED_5)
#define BG_COLOR BLACK

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Game_Host(void *pvParameters)
{
    LOCATION jet_loc = {.x = 64, .y = 64, .height = jet_fighterHeightPixels,
                        .width = jet_fighterWidthPixels};

    uint16_t fgColor = COLOR_CODE[RED1];
    uint16_t bgColor = COLOR_CODE[BLACK];

    lcd_draw_image(
            jet_loc.x,
            jet_loc.y,
            jet_loc.width,
            jet_loc.height,
      jet_fighterBitmaps,
      fgColor,
      bgColor
    );

    ADC_joy_acc_dir current;

    while(1)
    {

        xQueueReceive(Queue_Game_Host, &current, 0);

//        if (current.joy.left && current.joy.up)
//        {
//            jet_loc.x--;
//            jet_loc.y--;
//            vTaskDelay(pdMS_TO_TICKS(10));
//        }
//        if (current.joy.right && current.joy.up)
//        {
//            jet_loc.x++;
//            jet_loc.y--;
//            vTaskDelay(pdMS_TO_TICKS(10));
//        }
//        if (current.joy.left && current.joy.down)
//        {
//            jet_loc.x--;
//            jet_loc.y++;
//            vTaskDelay(pdMS_TO_TICKS(10));
//        }
//        if (current.joy.right && current.joy.down)
//        {
//            jet_loc.x++;
//            jet_loc.y++;
//            vTaskDelay(pdMS_TO_TICKS(10));
//        }
//
//        if (current.joy.left)
//        {
//            jet_loc.x--;
//        }
//        if (current.joy.right)
//        {
//            jet_loc.x++;
//        }
//        if (current.joy.up)
//        {
//            jet_loc.y--;
//        }
//        if (current.joy.down)
//        {
//            jet_loc.y++;
//        }

        if (current.acc.left && current.acc.up)
        {
            jet_loc.x--;
            jet_loc.y--;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (current.acc.right && current.acc.up)
        {
            jet_loc.x++;
            jet_loc.y--;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (current.acc.left && current.acc.down)
        {
            jet_loc.x--;
            jet_loc.y++;
            vTaskDelay(pdMS_TO_TICKS(10));
        }
        if (current.acc.right && current.acc.down)
        {
            jet_loc.x++;
            jet_loc.y++;
            vTaskDelay(pdMS_TO_TICKS(10));
        }

        if (current.acc.left)
        {
            jet_loc.x--;
        }
        if (current.acc.right)
        {
            jet_loc.x++;
        }
        if (current.acc.up)
        {
            jet_loc.y--;
        }
        if (current.acc.down)
        {
            jet_loc.y++;
        }

        jet_loc = boarder_range_validate(jet_loc);

        xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
        lcd_draw_image(
          jet_loc.x,
          jet_loc.y,
          jet_loc.width,
          jet_loc.height,
          jet_fighterBitmaps,
          fgColor,
          bgColor
        );
        xSemaphoreGive(Sem_RENDER);
        vTaskDelay(pdMS_TO_TICKS(5));

    }
}

bool is_in_boarder(LOCATION loc)
{

    int x0, x1, y0, y1;

    x0 = loc.x - (loc.width/2);
    x1 = loc.x + (loc.width/2);

    y0 = loc.y  - (loc.height/2);
    y1 = loc.y  + (loc.height/2);

    if (x0 <= 2 || y0 <= 2 || x1 >= 126 || y1 >= 126) {
        return true;
    }
    return false;
}

LOCATION boarder_range_validate(LOCATION loc) {

    LOCATION current;
    current.height = loc.height;
    current.width = loc.width;
    current.x = loc.x;
    current.y = loc.y;

    int x0, x1, y0, y1;

    x0 = loc.x - (loc.width/2);
    x1 = loc.x + (loc.width/2);

    y0 = loc.y  - (loc.height/2);
    y1 = loc.y  + (loc.height/2);

    if (x0 < 2) {
        int exceed = 2- x0;
        current.x = loc.x + exceed;
    }
    if (y0 < 2) {
        int exceed = 2- y0;
        current.y = loc.y + exceed;
    }
    if (x1 > 126) {
        int exceed = x1 - 126;
        current.x = loc.x - exceed;
    }
    if (y1 > 126) {
        int exceed = y1 - 126;
        current.y = loc.y - exceed;
    }

    return current;
}


