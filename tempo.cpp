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
#include "tempo.h"
#include "led.h"
#define TEMPO_MAX 240
#define TEMPO_MIN 40
boolean external_clk = true;
byte clk_divider = 0;
unsigned int tempo = 120;  //range 40 to 280
const byte digits_3_by_6[10][18]
={{
  0,1,0,
  1,0,1,
  1,0,1,
  1,0,1,
  1,0,1,
  0,1,0
},{
  0,0,1,
  0,1,1,
  0,0,1,
  0,0,1,
  0,0,1,
  0,0,1
},{
  0,1,0,
  1,0,1,
  0,0,1,
  9,1,0,
  1,0,0,
  1,1,1 
},{
  1,1,1,
  0,0,1,
  1,1,0,
  0,0,1,
  0,0,1,
  1,1,0
},{
  1,0,1,
  1,0,1,
  1,1,1,
  0,0,1,
  0,0,1,
  0,0,1
},{
  1,1,1,
  1,0,0,
  1,1,0,
  0,0,1,
  1,0,1,
  0,1,0
},{
  0,1,1,
  1,0,0,
  1,1,0,
  1,0,1,
  1,0,1,
  0,1,0
},{
  1,1,1,
  0,0,1,
  0,1,0,
  1,0,0,
  1,0,0,
  1,0,0
},{
  0,1,0,
  1,0,1,
  0,1,0,
  1,0,1,
  1,0,1,
  0,1,0
},{
  1,1,1,
  1,0,1,
  1,1,1,
  0,0,1,
  1,0,1,
  0,1,0
}};
const byte digits_2_by_6[3][12]
={{
  0,0,
  0,0,
  0,0,
  0,0,
  0,0,
  0,0
},{
  0,1,
  1,1,
  0,1,
  0,1,
  0,1,
  0,1
},{
  1,1,
  0,1,
  0,1,
  1,0,
  1,0,
  1,1 
}};
#define EXT_CLK_ICON_SIZE 48
const byte external_clock_icon[EXT_CLK_ICON_SIZE] 
{
  0,0,0,0,0,1,0,0,
  1,1,1,1,1,1,1,0,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,0,
  0,0,0,0,0,1,0,0,
  0,0,0,0,0,0,0,0
};
////////////////////////////////////////////////////////
IntervalTimer myTimer;
int metro = 0;
void timer_metro()
{
  metro = 1;
}
void set_metro(unsigned int interval_ms)
{
    myTimer.begin(timer_metro, interval_ms);
}
///////////////////////////////////////////////////
void tempo_edit_start()
{
    grid_led_update = true;
}

boolean tempo_update_led()
{
  const unsigned int left_digit = tempo/100;
  const unsigned int middle_digit = (tempo - (left_digit*100))/10;
  const unsigned int right_digit = tempo%10;
  // draw the external clock icon 
  if (external_clk)
  {
    for (int idx = 0; idx < EXT_CLK_ICON_SIZE; idx++)
    {
      if (external_clock_icon[idx]==1)
      {
        if (set_grid_led(idx,LED_GREEN))
            return true;
      }
      else
      {
        if (set_grid_led(idx,LED_OFF))
            return true;
      }      
    }
  }
  else //draw digits
  {
    byte led_idx=0;
    for (byte y = 0; y < 6; y++)
    {
      for (byte x = 0; x < 2; x++)
      {
        byte pixel = (y*2)+x;
        if (digits_2_by_6[left_digit][pixel])
        {
          if (set_grid_led(led_idx,LED_RED))
               return true;
        }
        else
        {
          if (set_grid_led(led_idx,LED_OFF))
               return true;          
        }
        led_idx++;
      }
      for (byte x = 0; x < 3; x++)
      {        
        byte pixel = (y*3)+x;
        if (digits_3_by_6[middle_digit][pixel]==1)
        {
          if (set_grid_led(led_idx,LED_YELLOW))
               return true;
        }
        else
        {
          if (set_grid_led(led_idx,LED_OFF))
               return true;          
        }
        led_idx++;
      }
      for (byte x = 0; x < 3; x++)
      {
        byte pixel = (y*3)+x;
        if (digits_3_by_6[right_digit][pixel]==1)
        {
          if (set_grid_led(led_idx,LED_GREEN))
               return true;
        }
        else
        {
          if (set_grid_led(led_idx,LED_OFF))
               return true;          
        }
        led_idx++;
      }
    }
  }
  for (int idx = 0; idx < GRID_WIDTH; idx++)
  {
    if (idx <=clk_divider)
    {
      if (set_grid_led(48+idx,LED_GREEN))
        return true;
    }
    else
    {
      if (set_grid_led(48+idx,LED_OFF))
        return true;   
    }
  }
  byte bottom_row[8]={LED_RED,LED_YELLOW,LED_GREEN,LED_GREEN,LED_YELLOW,LED_RED,LED_OFF,LED_GREEN};
  for (int idx = 0; idx < 8 ; idx++)
    if (set_grid_led(56+idx,bottom_row[idx]))
      return true;                
  return false;
}

void tempo_button_down( const byte button )
{
  //second bottom row is divider controller
  if ((button / 8 ) == 6) 
  {
    clk_divider = (button % 8);
    unsigned int sped= 60000 / (tempo * 8);
    sped *= (1+clk_divider);
    myTimer.begin(timer_metro, sped*1000);
  }
  else if((button / 8 ) == 7) //tempo up down buttons and ext clock button
  {
    byte which = (button % 8);
    if (which == 0)//-100
    {
      if (tempo > 140)
        tempo -= 100;
      else
        tempo = TEMPO_MIN;
    }
    else if (which == 1)
      tempo -= 10;
    else if (which == 2)
      tempo -= 1;
    else if (which == 3)
      tempo += 1;
    else if (which == 4)
      tempo += 10;
    else if (which == 5)
      tempo += 100;
    else if (which == 7)
    {
      if (!external_clk)
        external_clk = true;
      else
        external_clk = false;
    }
    if (tempo < TEMPO_MIN)
      tempo = TEMPO_MIN;
    if (tempo > TEMPO_MAX)
      tempo = TEMPO_MAX;
    unsigned int clck_hi_ms = 60000 / (tempo * 8);
    clck_hi_ms *= (1+clk_divider);
    clck_hi_ms *= 1000;
    set_metro(clck_hi_ms);  
  }
  grid_led_update = true;
}

