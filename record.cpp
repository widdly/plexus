#include "led.h"
#include "playback.h"
#include "hardware.h"
#include "notes.h"
#include "record.h"
// current output state of record
byte record_led = 0;
boolean record_led_on = false;

typedef struct Record
{
  boolean recording;
  byte initial_button;
  byte current_step;

  Sequence * sequence;
}
Record;

Record record;
byte temp_seq[SEQUENCE_LENGTH];

void record_setup()
{
  record.current_step = 0;
  record.recording = false;
  record.initial_button = 0;
  record_led = 0;
  record_led_on = false;
}

void record_start( const byte voice )
{
  record.current_step = 0;
  record.recording = true;
  record.sequence = playback[voice].sequence;
  record_led = 0;
  record_led_on = false;
  grid_led_update = true;
}

void record_button_down ( const byte button)
{
  if (record.recording)
  {
    byte step = record.current_step;
    record.sequence->steps[step].gate = true;
    record.sequence->steps[step].gate_length = 1;
    if (step == 0)
    {
      record.initial_button = button;
      record.sequence->steps[0].offset_x = 0;
      record.sequence->steps[0].offset_y = 0;
    }
    else
    {
      unsigned char x = get_x_from_button(button);
      unsigned char y = get_y_from_button(button);
      unsigned char start_x = get_x_from_button(record.initial_button);
      unsigned char start_y = get_y_from_button(record.initial_button);
      record.sequence->steps[step].offset_x = (x - start_x);
      record.sequence->steps[step].offset_y = (y - start_y);
    }
    record.current_step++;
    record.sequence->length = record.current_step;
    if (record.current_step == SEQUENCE_LENGTH)
    {
      record.recording = false;
    }
    record_led = button;
    record_led_on = true;
    grid_led_update = true;
  }

}

boolean record_led_update()
{
  //the last entered value is red.
  //yellow horixontal bar graph at bottom showing sequence length
  for (int idx = 0; idx < GRID_SIZE; idx++ )
  {
    if (( idx == record_led ) && (record_led_on))
    {
      if (set_grid_led(idx, LED_RED))
        return true;
    }
    else if ((record.initial_button == idx)&& (record_led_on))
    {
      if (set_grid_led(idx, LED_GREEN))
        return true;    
    }
    else if ((idx > 55) && (idx <= 55 + record.current_step))
    {
      if (set_grid_led(idx, LED_YELLOW))
        return true;
    }
    else
    {
      if (set_grid_led(idx, LED_OFF))
        return true;
    }
  }
  return false;
}


