

#include <main.h>


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Song(void *pvParameters)
{
    SOUND sound = NO_PLAY;

    int intro_song_ticks_period = 3000;
    int intro_song_time_count = 0;

    int game_over_song_ticks_period = 10000;
    int game_over_song_time_count = 0;

    int you_win_song_ticks_period = 20000;
    int you_win_song_time_count = 0;

    while(1)
    {
        xQueueReceive(Queue_Song, &sound, 0);
        switch(sound){
        case PLAY_INTRO_SONG: {
            play_tone(intro_song_ticks_period);
            buzzer_on();
            intro_song_ticks_period = ((intro_song_ticks_period + 1000) % 7000) + 3000;
            intro_song_time_count++;
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
            game_over_song_ticks_period = game_over_song_ticks_period + 3000;
            game_over_song_time_count++;
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
            you_win_song_ticks_period = you_win_song_ticks_period - 1000;
            you_win_song_time_count++;
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

