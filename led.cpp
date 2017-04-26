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
#include <MIDI.h>
#include "led.h"
//led cache and update flags
boolean right_led_update = false;
boolean top_led_update = false;
boolean grid_led_update = false;
byte right_led_cache[RIGHT_LED_COUNT] = {
  LED_OFF
};
byte top_led_cache[TOP_LED_COUNT] = {
  0
};
byte grid_led_cache[GRID_SIZE] = {
  LED_OFF
};
boolean set_right_led(byte position, byte color )
{
  if (right_led_cache[position] != color)
  {
    if (color == LED_OFF)
      MIDI.sendNoteOff((position * 16) + 8, color, 1);
    else
      MIDI.sendNoteOn((position * 16) + 8, color, 1);
    right_led_cache[position] = color;
    return true;
  }
  return false;
}
boolean set_top_led(byte position, byte color )
{
  if (top_led_cache[position] != color)
  {
    MIDI.sendControlChange(104 + position, color, 1);
    top_led_cache[position] = color;
    return true;
  }
  return false;
}
boolean set_grid_led(byte position, byte color )
{
  if (grid_led_cache[position] != color)
  {
    byte button = ((position / 8) * 16) + (position % 8);
    if (color == LED_OFF)
      MIDI.sendNoteOff( button, color, 1);
    else
      MIDI.sendNoteOn( button, color, 1);
    grid_led_cache[position] = color;
    return true;
  }
  return false;
}
