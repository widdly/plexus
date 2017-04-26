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
#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include "WProgram.h"

#define GRID_SIZE    64
#define VOICE_COUNT    4

#define SEQUENCE_LENGTH   8
#define GRID_WIDTH  8
#define GRID_HEIGHT 8

#define LED_OFF        0x0C
#define LED_GREEN      0x3C
#define LED_RED        0x0F
#define LED_YELLOW     0x3E
#define LED_AMBER      0x3F

//modes (selected via right hand buttons)
#define PLAY          0
#define REC           1
#define EDIT          2
#define TEMPO_EDIT    3
#define MODE_COUNT    4

#define SEQUENCE_COUNT  8
#define TOP_LED_COUNT 8
#define RIGHT_LED_COUNT 8

typedef struct Step
{
  unsigned char offset_x;
  unsigned char offset_y;
  boolean gate;
  byte gate_length;
}
Step;

typedef struct Sequence
{
  byte length;
  Step steps[SEQUENCE_LENGTH];
}
Sequence;

typedef struct Playback
{
  boolean playing;
  boolean button_down;
  boolean hold_on;

  byte initial_button;
  byte current_step;
  byte current_button;
  boolean gate;
  byte remaining_gate_time;

  Sequence * sequence;
}
Playback;

#endif
