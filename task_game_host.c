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
void Task_Game_Host(void *pvParameters)
{
    // current jet location
    LOCATION jet_loc = {.x = 64, .y = 64, .height = jet_fighterHeightPixels,
                        .width = jet_fighterWidthPixels};
    // current npc location
    LOCATION npc_loc = { .x = 0, .y = 0, .height = 0, .width = 0 };

    // joy and acc current status
    ADC_joy_acc_dir current =
            { .joy = { .center = true, .left = false, .right = false, .up =
                               false,
                       .down = false },
              .acc = { .center = true, .left = false, .right = false, .up =
                               false,
                       .down = false },
              .acc_is_changed = false, .joy_is_changed = false };

    // jet color
    uint16_t fgColor = COLOR_CODE[GREEN1];
    uint16_t bgColor = COLOR_CODE[BLACK];

    // collision
    bool current_collide = false; // collision flag
    bool pre_is_collide = false; // detect previous collision

    // am light sensor change color
    bool is_dark = false;

    // create bullet list for tracking
    int i;
    BULLET bullet_list[5];
    for (i = 0; i < 5; i++) {
        LOCATION new_bullet_loc = { .x = 0, .y = 0, .height = bulletWidthPixels,
                                    .width = bulletHeightPixels };
        ADC_MOVE new_bullet_dir = { .center = false, .left = false, .right = false,
                                    .up = false, .down = false };
        bullet_list[i].loc = new_bullet_loc;
        bullet_list[i].dir = new_bullet_dir;
        bullet_list[i].in_use = false;
    }

    // debounce state for S1
    uint8_t debounce_state = 0x00;

    // draw initial image
    lcd_draw_image(
            jet_loc.x,
            jet_loc.y,
            jet_loc.width,
            jet_loc.height,
      jet_fighterBitmaps,
      fgColor,
      bgColor
    );

    while(1)
    {

        xQueueReceive(Queue_Game_ADC_to_Host, &current, 0);

        // Control jet movement
        if (current.acc.left && current.acc.up)
        {
            jet_loc.x--;
            jet_loc.y--;
        }
        else if (current.acc.right && current.acc.up)
        {
            jet_loc.x++;
            jet_loc.y--;
        }
        else if (current.acc.left && current.acc.down)
        {
            jet_loc.x--;
            jet_loc.y++;
        }
        else if (current.acc.right && current.acc.down)
        {
            jet_loc.x++;
            jet_loc.y++;
        }
        else if (current.acc.left)
        {
            jet_loc.x--;
        }
        else if (current.acc.right)
        {
            jet_loc.x++;
        }
        else if (current.acc.up)
        {
            jet_loc.y--;
        }
        else if (current.acc.down)
        {
            jet_loc.y++;
        }
        else {}

        jet_loc = boarder_range_validate(jet_loc);

        // Collision detection
        xQueueReceive(Queue_Game_NPC_to_Host, &npc_loc, 0);
        bool current_collide = is_collided(jet_loc, npc_loc);
        if (current_collide && !pre_is_collide) {
//            printf("DEBUG: IS COLLIDED\n\r");
        }
        pre_is_collide = current_collide;

        // render image
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

        // bullet control
        int q;
        for (q = 0; q < 5; q++) {
            if (bullet_list[q].in_use) {
                // if it is in boarder or hit npc
                if (is_collided(npc_loc, bullet_list[q].loc)) {
                    bool flash = 1;
                    xQueueSendToBack(Queue_Game_Host_to_NPC, &flash, 0);

                }
                if (is_in_boarder(bullet_list[q].loc) || is_collided(npc_loc, bullet_list[q].loc)) {
                    // render bullet with empty
                    xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                                    lcd_draw_image(
                                      bullet_list[q].loc.x,
                                      bullet_list[q].loc.y,
                                      bullet_list[q].loc.width,
                                      bullet_list[q].loc.height,
                                      bulletBitmaps,
                                      COLOR_CODE[BLACK],
                                      COLOR_CODE[BLACK]
                                    );
                    xSemaphoreGive(Sem_RENDER);
                    bullet_list[q].in_use = false;
                }
                else {
                    // render bullet
                    xSemaphoreTake(Sem_RENDER, portMAX_DELAY);
                    lcd_draw_image(
                      bullet_list[q].loc.x,
                      bullet_list[q].loc.y,
                      bullet_list[q].loc.width,
                      bullet_list[q].loc.height,
                      bulletBitmaps,
                      COLOR_CODE[WHITE],
                      COLOR_CODE[BLACK]
                    );
                    xSemaphoreGive(Sem_RENDER);
                }

                if (bullet_list[q].dir.left && bullet_list[q].dir.up) {
                    bullet_list[q].loc.x--;
                    bullet_list[q].loc.y--;
                }
                else if (bullet_list[q].dir.right && bullet_list[q].dir.up) {
                    bullet_list[q].loc.x++;
                    bullet_list[q].loc.y--;
                }
                else if (bullet_list[q].dir.left && bullet_list[q].dir.down) {
                    bullet_list[q].loc.x--;
                    bullet_list[q].loc.y++;
                }
                else if (bullet_list[q].dir.right && bullet_list[q].dir.down) {
                    bullet_list[q].loc.x++;
                    bullet_list[q].loc.y++;
                }
                else if (bullet_list[q].dir.left){
                    bullet_list[q].loc.x--;
                }
                else if (bullet_list[q].dir.right){
                    bullet_list[q].loc.x++;
                }
                else if (bullet_list[q].dir.up){
                    bullet_list[q].loc.y--;
                }
                else if (bullet_list[q].dir.down){
                    bullet_list[q].loc.y++;
                }
                else {}

            }
        }

        // Initialize a bullet
        debounce_state = debounce_state << 1;
        if (ece353_s1_pressed())
        {
            debounce_state = debounce_state | BIT0;
        }
        if (debounce_state == 0x7F)
        {
            bool bypass = false;
            for (q = 0; q < 5; q++) {
                if (bypass) {
                    continue;
                }
                if (!bullet_list[q].in_use && current.joy.center!=true) {
                    bullet_list[q].in_use = true;
                    bullet_list[q].dir = current.joy;
                    bullet_list[q].loc.x = jet_loc.x;
                    bullet_list[q].loc.y = jet_loc.y;
                    bypass = true;
                }
            }
        }
        // am light sensor change color
        if (is_dark && (am_light_get_lux() > 10)) {
            is_dark = false;
            fgColor = COLOR_CODE[generate_random_in_range(0, 12)];
        }
        if (!is_dark && (am_light_get_lux() < 10)) {
            is_dark = true;
            fgColor = COLOR_CODE[generate_random_in_range(0, 12)];
        }



        // delay task
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

bool is_collided(LOCATION loc1, LOCATION loc2)
{
    int xA_0, xA_1, yA_0, yA_1;

    xA_0 = loc1.x - (loc1.width/2) + 2;
    xA_1 = loc1.x + (loc1.width/2) - 2;

    yA_0 = loc1.y  - (loc1.height/2) + 2;
    yA_1 = loc1.y  + (loc1.height/2) - 2;

    int xB_0, xB_1, yB_0, yB_1;

    xB_0 = loc2.x - (loc2.width/2) + 2;
    xB_1 = loc2.x + (loc2.width/2) - 2;

    yB_0 = loc2.y  - (loc2.height/2) + 2;
    yB_1 = loc2.y  + (loc2.height/2) - 2;

    if ((((xA_0 < xB_0) && (xB_0 < xA_1)) || ((xA_0 < xB_1) && (xB_1 < xA_1)))
            && (((yA_0 < yB_0) && (yB_0 < yA_1))
                    || ((yA_0 < yB_1) && (yB_1 < yA_1))))
    {
        return true;
    }
    return false;
}

int generate_random_in_range(int lower, int upper)
{
    int i;
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}


