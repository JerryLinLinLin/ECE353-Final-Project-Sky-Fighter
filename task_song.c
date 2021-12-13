/*
 * task_song.c
 *
 * Author: Hai Lin
 * Author: Andres Quintanal Escandon
 */

#include <main.h>


/******************************************************************************
* Task to play the sound effect of game
******************************************************************************/
void Task_Song(void *pvParameters)
{
    SOUND sound = NO_PLAY;

    // for intro song tone and time
    int intro_song_ticks_period = 3000;
    int intro_song_time_count = 0;

    // for game over song tone and time
    int game_over_song_ticks_period = 10000;
    int game_over_song_time_count = 0;

    // for you win song tone and time
    int you_win_song_ticks_period = 20000;
    int you_win_song_time_count = 0;

    while(1)
    {
        // receive request from other task
        xQueueReceive(Queue_Song, &sound, 0);
        switch(sound){
        case PLAY_INTRO_SONG: {
            play_tone(intro_song_ticks_period);
            buzzer_on();
            // dynamic change tone
            intro_song_ticks_period = ((intro_song_ticks_period + 1000) % 7000) + 3000;
            intro_song_time_count++;
            // check if exceed time
            if (intro_song_time_count > 5) {
                sound = NO_PLAY;
                intro_song_time_count = 0;
                buzzer_off();
            }
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        case PLAYER_SHOOTING: {
            play_tone(10000);
            buzzer_on();
            sound = NO_PLAY;
            vTaskDelay(pdMS_TO_TICKS(100));
            break;
        }
        case GAME_OVER:
        {
            play_tone(game_over_song_ticks_period);
            buzzer_on();
            // dynamic change tone
            game_over_song_ticks_period = game_over_song_ticks_period + 3000;
            game_over_song_time_count++;
            // check if exceed time
            if (game_over_song_time_count > 5) {
                sound = NO_PLAY;
                game_over_song_time_count = 0;
                buzzer_off();
            }
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        case YOU_WIN:
        {
            play_tone(you_win_song_ticks_period);
            buzzer_on();
            // dynamic change tone
            you_win_song_ticks_period = you_win_song_ticks_period - 1000;
            you_win_song_time_count++;
            // check if exceed time
            if (you_win_song_time_count > 5) {
                sound = NO_PLAY;
                you_win_song_time_count = 0;
                buzzer_off();
            }
            vTaskDelay(pdMS_TO_TICKS(500));
            break;
        }
        case NPC_KILLED:
        {
            play_tone(4000);
            buzzer_on();
            sound = NO_PLAY;
            vTaskDelay(pdMS_TO_TICKS(100));
            break;
        }
        case NO_PLAY:
        {
            buzzer_off();
            vTaskDelay(pdMS_TO_TICKS(50));
            break;
        }
        }

    }
}

