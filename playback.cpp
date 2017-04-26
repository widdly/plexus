#include "led.h"
#include "playback.h"
#include "hardware.h"
#include "notes.h"

unsigned int tick = 0;
Sequence sequences[SEQUENCE_COUNT];
Playback playback[VOICE_COUNT];
byte select_voice = 0;

// current output state of playback sequencer
byte playback_led[VOICE_COUNT] = {
  0
};
boolean playback_gate[VOICE_COUNT] = {
  false
};
boolean playback_led_on[VOICE_COUNT] = {
  false
};

void playback_setup()
{
  for (int idx = 0; idx < VOICE_COUNT; idx++)
  {
    playback[idx].playing = false;
    playback[idx].playing = false;
    playback[idx].button_down = false;
    playback[idx].hold_on = false;
    playback[idx].initial_button = 0;
    playback[idx].current_step = 0;
    playback[idx].current_button = 0;
    playback[idx].gate = false;
    playback[idx].remaining_gate_time = 0;
    playback[idx].sequence = &sequences[idx];
  }
  //TBD Initialize these with something interesting or load from persistent memory
  for (int idx = 0; idx < SEQUENCE_COUNT ; idx++ )
  {
    sequences[idx].length = 4;
    for (int step = 0; step < SEQUENCE_LENGTH; step++ )
    {
      sequences[idx].steps[step].offset_x = step;
      sequences[idx].steps[step].offset_y = step;
      sequences[idx].steps[step].gate = true;
      sequences[idx].steps[step].gate_length = 1;
    }
  }
}
void playback_start()
{
  grid_led_update = true;
}
void playback_button_down ( const byte button, const byte voice)
{
  if (!playback[voice].button_down)
  {
    playback[voice].button_down = true;
    if (((playback[voice].playing) && (playback[voice].initial_button != button)) || (!playback[voice].playing))
    {
      playback[voice].playing = true;
      playback[voice].initial_button = button;
      playback[voice].current_step = 0;
      playback[voice].current_button = button;
      playback[voice].gate = playback[voice].sequence->steps[0].gate;
      playback[voice].remaining_gate_time  = playback[voice].sequence->steps[0].gate_length;
      if (tick ==0)
        playback[voice].remaining_gate_time  += 1;

      set_cv_output_hw(voice,get_note_number(playback[voice].current_button));
      playback_led_on[voice] = true;
      playback_led[voice] = button;
      grid_led_update = true;
      set_gate_output_hw(voice,playback[voice].gate);
    }
  }
}
void playback_button_up( const byte button, const byte voice)
{
  if (playback[voice].button_down)
  {
    if (button != playback[voice].initial_button)
      return;

    playback[voice].button_down = false;
    if (!playback[voice].hold_on)
    {
      playback[voice].playing = false;
      playback_gate[voice] = false;
      playback_led_on[voice] = false;
      grid_led_update = true;
      set_gate_output_hw(voice,false);
    }
  }
}
void playback_set_hold ( const byte voice, const boolean hold_state )
{
  playback[voice].hold_on = hold_state;
  //if we are currently holding a sequence then end it
  if ((!hold_state) && (playback[voice].playing) && (!playback[voice].button_down))
  {
    playback[voice].playing = false;
    playback_gate[voice] = false;
    playback_led_on[voice] = false;
    grid_led_update = true;
    set_gate_output_hw(voice,false);
  }
}
void playback_clock_rising ()
{
  set_clock_output_hw(true);
  for (int voice = 0; voice < VOICE_COUNT; voice++)
  {
    if (playback[voice].playing)
    {
      playback[voice].remaining_gate_time--;
      if (playback[voice].remaining_gate_time == 0)
      {
        playback[voice].current_step++;
        playback[voice].current_step %= playback[voice].sequence->length;

        byte this_step = playback[voice].current_step;

        unsigned char x = get_x_from_button(playback[voice].initial_button);
        x += playback[voice].sequence->steps[this_step].offset_x;
        while ( x < 0 )
          x += 8;
        x = x % GRID_WIDTH;
        unsigned char y = get_y_from_button(playback[voice].initial_button);
        y += playback[voice].sequence->steps[this_step].offset_y;
        while ( y < 0 )
          y += 8;
        y = y % GRID_HEIGHT;
        playback[voice].current_button = get_button_from_x_y(x, y);

        playback_led[voice] = playback[voice].current_button ;
        set_cv_output_hw(voice,get_note_number(playback[voice].current_button));
        
        playback[voice].gate = playback[voice].sequence->steps[this_step].gate;
        playback[voice].remaining_gate_time  = playback[voice].sequence->steps[this_step].gate_length;
        playback_gate[voice] = playback[voice].gate;
        grid_led_update = true;
        set_gate_output_hw(voice,playback[voice].gate);
      }
    }
  }
}
void playback_clock_falling ()
{
  set_clock_output_hw(false);
  for (int voice = 0; voice < VOICE_COUNT; voice++)
  {
    if ((playback[voice].playing) && (playback[voice].remaining_gate_time <= 1))
    {
      playback_gate[voice] = false;
      set_gate_output_hw(voice,false);
    }
  }
}

void playback_clock()
{
  tick = (tick + 1) % 2;
  if (tick)
    playback_clock_rising();
  else
    playback_clock_falling();
}

boolean playback_led_update()
{
  for (int idx = 0; idx < GRID_SIZE; idx++ )
  {
    if (( idx == playback_led[select_voice] ) && (playback_led_on[select_voice]))
    {
      if (set_grid_led(idx, LED_GREEN))
        return true;
    }
    else if (( idx == playback_led[0] ) && (playback_led_on[0]))
    {
      if ( set_grid_led(idx, LED_YELLOW))
        return true;
    }
    else if (( idx == playback_led[1] ) && (playback_led_on[1]))
    {
      if ( set_grid_led(idx, LED_YELLOW))
        return true;
    }
    else if (( idx == playback_led[2] ) && (playback_led_on[2]))
    {
      if ( set_grid_led(idx, LED_YELLOW))
        return true;
    }
    else if (( idx == playback_led[3] ) && (playback_led_on[3]))
    {
      if ( set_grid_led(idx, LED_YELLOW))
        return true;
    }
    else
    {
      if (  set_grid_led(idx, LED_OFF))
        return true;
    }
  }
  return false;
}
