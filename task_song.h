

#ifndef TASK_SONG_H_
#define TASK_SONG_H_

#include "main.h"


/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Song(void *pvParameters);

typedef enum {NO_PLAY, PLAY_INTRO_SONG, PLAYER_SHOOTING, NPC_KILLED, GAME_OVER, YOU_WIN} SOUND;

#endif /* TASK_ADC_JOY_ACC_H_ */
