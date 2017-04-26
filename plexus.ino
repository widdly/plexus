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
#include "definitions.h"
#include "notes.h"
#include "hardware.h"
#include "tempo.h"
#include "led.h"
#include "edit.h"
#include "playback.h"
#include "record.h"
//generic handlers
void handle_button_down( byte button );
void handle_button_up( byte button );
void handle_mode_button( byte button );
void handle_function_button( byte button );
// top and right button states
byte mode = PLAY;
boolean hold[VOICE_COUNT] = {
  false
};
//////////////////////////////////////////////////////////////////////////
byte note_cache[128] = {0};
void handle_note_on(byte channel, byte pitch, byte velocity)
{
  if ((velocity != 0) && (velocity != 127))
    return;
  if (note_cache[pitch] == velocity)
    return;
  note_cache[pitch] = velocity;
  byte y = pitch / 16;
  byte x = pitch % 16;
  if ((x == 8) && (velocity == 127))
  {
    handle_mode_button(y);
  }
  else
  {
    byte button = x + (y * 8);
    if (velocity == 127)
      handle_button_down(button);
    else if (velocity == 0)
      handle_button_up(button);
  }
}
void handle_note_off(byte channel, byte pitch, byte velocity)
{
  if (velocity != 0)
    return;
  if (note_cache[pitch] == 0)
    return;
  note_cache[pitch] = 0;
  byte y = pitch / 16;
  byte x = pitch % 16;
  byte button = x + (y * 8);
  if (x < 8)
    handle_button_up(button);
}
void handle_control_change(byte channel, byte number, byte value)
{
  static byte cc_cache[128] = {0};
  //only want 0 or 127 and only changes
  if ((value != 127)&&(value != 0))
    return;
  if (cc_cache[number] == value )
    return;  
  cc_cache[number] = value;
  if ((number >= 104) && (number <= 112))
  {
    byte y = number - 104;
    if (value == 127)
    {
      handle_function_button(y);
    }
  }
}
void reset_launchpad()
{
  MIDI.sendControlChange(0, 0, 1);
}
void set_brightness(int bright)
{
  int actual_bright = 13 - bright;
  if (actual_bright < 0)
    actual_bright = 0;
  MIDI.sendControlChange(30, actual_bright, 1);
}
//////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  MIDI.setHandleNoteOn(handle_note_on);
  MIDI.setHandleNoteOff(handle_note_off);
  MIDI.setHandleControlChange(handle_control_change);
  MIDI.begin(1);
  MIDI.turnThruOff();
  reset_launchpad();
  playback_setup();
  record_setup();
  setup_cv_dac_hw();
  setup_digital_io_hw();  
  set_metro(25000);
  //playback mode, voice 1 selected
  set_top_led(4, LED_GREEN);
  set_right_led(0, LED_GREEN);
}
void loop()
{ 
  static unsigned int send_delay = 0;
  MIDI.read();
  //throttle midi out send speed without
  //dropping clock or midi in
  if (send_delay > 0)
    send_delay--;
  else  if (led_update())
    send_delay = 2000;  //delay after send event
  if (metro)
  {
    metro = 0;
    playback_clock();
  }
}
///////////////////////////////////////////////////////////////
void handle_button_down( byte button )
{
  switch (mode)
  {
    case PLAY:
      playback_button_down(button, select_voice);
      break;
    case REC:
      record_button_down(button);
      break;
    case EDIT:
      edit_button_down(button);
      break;
    case TEMPO_EDIT:
      tempo_button_down (button);
      break;
  }
}
void handle_button_up( byte button )
{
  switch (mode)
  {
    case PLAY:
      playback_button_up(button, select_voice);
      break;
    case REC:
      break;
    case EDIT:
      break;
    case TEMPO_EDIT:
      break;
  }
}
void handle_mode_button( byte button )
{
  if (button < MODE_COUNT)
  {
    if (mode != button)
    {
      mode = button;
      switch (mode)
      {
        case PLAY:
          record_start(select_voice);
          break;
        case REC:
          record_start(select_voice);
          break;
        case EDIT:
          edit_start(select_voice);
          break;
        case TEMPO_EDIT:
          tempo_edit_start();
          break;
      }
      right_led_update = true;
    }
  }
}
void handle_function_button( byte button )
{
  if (button < 4)//hold buttons
  {
    if ( hold[button] ) //hold off
    {
      hold[button] = false;
      playback_set_hold(button, false);
    }
    else //hold on
    {
      hold[button] = true;
      playback_set_hold(button, true);
    }
    top_led_update = true;
  }
  else
  {
    if (select_voice != button - 4)
    {
      select_voice = button - 4;
      if (mode == REC)
        record_start(select_voice);
      else if (mode == EDIT)
        edit_start(select_voice);
      grid_led_update = true;
      top_led_update = true;
    }
  }
}
//////////////////
boolean led_update()
{
  //right leds indicate current mode
  if (right_led_update)
  {
    for (int idx = 0; idx < RIGHT_LED_COUNT; idx++)
    {
      if (mode == idx)
      {
        if (set_right_led(idx, LED_GREEN))
            return true;
      }
      else
      {
        if (set_right_led(idx, LED_OFF))
            return true;
      }
    }
    right_led_update = false;
  }
  //top leds indicate hold and current channel
  if (top_led_update)
  {
    for (int idx = 0; idx < VOICE_COUNT; idx++)
    {
      if ( hold[idx] )
      {
        if (set_top_led(idx, LED_AMBER))
          return true;
      }
      else
      {
        if (set_top_led(idx, 0))
          return true;
      }
      if ( idx == select_voice )
      {
        if (set_top_led(VOICE_COUNT + idx, LED_GREEN))
          return true;
      }
      else
      {
        if (set_top_led(VOICE_COUNT + idx, 0))
          return true;
      }
    }
    top_led_update = false;
  }
  if (grid_led_update)
  {
    switch (mode)
    {
      case PLAY:
        if (playback_led_update())
          return true;
        break;
      case REC:
        if (record_led_update())
          return true;
        break;
      case EDIT:
        if (edit_led_update())
          return true;
        break;
      case TEMPO_EDIT:
        if (tempo_update_led())
          return true;
        break;
        
    }
    grid_led_update = false;
  }
  return false;
}

