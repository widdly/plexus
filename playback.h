/*
plexus - a launchpad cv/gate sequencer/keyboard/arpeggiator
Copyright (C) 2017 Dougall IRVING

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
