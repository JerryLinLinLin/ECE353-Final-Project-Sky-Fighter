/*
 * task_game_npc.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#ifndef TASK_GAME_NPC_H_
#define TASK_GAME_NPC_H_

#include <main.h>

/**
 * struct to store a npc and use as object
 */
typedef struct
{
    int height;
    int width;
    int type;
    const uint8_t *image;
    COLOR_INDEX color;
    int hp;
} NPC_TYPE;

/******************************************************************************
* Task used to handle the movement of npc
******************************************************************************/
void Task_Game_NPC(void *pvParameters);

/**
 * generate random direction for npc random movement
 * @return ADC_MOVE dir
 */
ADC_MOVE generate_random_dir(void);


#endif
