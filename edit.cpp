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
#include "edit.h"
#include "led.h"
#include "playback.h"

Sequence * edit;

void edit_start( const byte voice )
{
  edit = playback[voice].sequence;
  grid_led_update = true;
}

void edit_button_down ( const byte button)
{
  byte coloumn = button % 8;
  byte row = button / 8;

  //bottom row is sequence length
  if (row == 7)
  {
    edit->length = coloumn + 1;
  }
  else if (row == 6)
  {
    edit->steps[coloumn].gate = !(edit->steps[coloumn].gate);
  }
  else
  {
    edit->steps[coloumn].gate_length = 6 - row;
  }
  grid_led_update = true;
}

boolean edit_led_update()
{
  //edit screen bottom row is sequence length
  //second bottom is gate on
  //rest of screen is bar graph of step length
  for (int row = 0; row < GRID_HEIGHT; row++ )
  {
    for (int coloumn = 0; coloumn < GRID_WIDTH; coloumn++ )
    {
      int button = (row * 8) + coloumn;
      if (row == 7)
      {
        if ((coloumn + 1) <= edit->length)
        {
          if (set_grid_led(button, LED_RED))
            return true;
        }
        else
        {
          if (set_grid_led(button, LED_OFF))
            return true;
        }
      }
      else if (row == 6)
      {
        if (edit->steps[coloumn].gate)
        {
          if (set_grid_led(button, LED_GREEN))
            return true;
        }
        else
        {
          if ( set_grid_led(button, LED_OFF))
            return true;
        }
      }
      else
      {
        if (edit->steps[coloumn].gate_length >= (6-row))
        {
          if ( set_grid_led(button, LED_YELLOW))
            return true;
        }
        else
        {
          if (set_grid_led(button, LED_OFF))
            return true;
        }
      }
    }
  }
  return false;
}
