/*
 * task_song.h
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#ifndef TASK_SONG_H_
#define TASK_SONG_H_

#include "main.h"


/******************************************************************************
* Task to play the sound effect of game
******************************************************************************/
void Task_Song(void *pvParameters);

/**
 * Sound effects
 */
typedef enum
{
    NO_PLAY, PLAY_INTRO_SONG, PLAYER_SHOOTING, NPC_KILLED, GAME_OVER, YOU_WIN
} SOUND;

#endif /* TASK_ADC_JOY_ACC_H_ */
