#ifndef PLAYBACK_H
#define PLAYBACK_H
#include "definitions.h"
extern byte select_voice;
extern Playback playback[VOICE_COUNT];
//playback handlers
void playback_setup();
void playback_start();
void playback_set_hold ( const byte voice, const boolean hold_state );
void playback_button_down ( const byte button, const byte voice);
void playback_button_up( const byte button, const byte voice);
void playback_clock();
boolean playback_led_update();
#endif
