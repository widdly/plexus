#include "hardware.h"
#include "SPI.h"
#include "definitions.h"

// hardware digital i/o pins
#define CLK_IN_PIN   8
#define CLK_OUT_PIN  6
#define GATE_OUT_PIN_1  2
#define GATE_OUT_PIN_2  3
#define GATE_OUT_PIN_3  4
#define GATE_OUT_PIN_4  5
const byte gate_out_pins[VOICE_COUNT] = {GATE_OUT_PIN_1,GATE_OUT_PIN_2,GATE_OUT_PIN_3,GATE_OUT_PIN_4};
// DAC pins
#define CS_PIN_A  9
#define CS_PIN_B    10 
// these are internal to the SPI library 
//#define SCK_PIN 13
//#define MOSI_PIN  11
#define MAX_NOTE 60

/* CV output DACs
            MCP4822 
teensy 
5v        Vdd   - 1   8 - VoutA
pin 9or10 /CS   - 2   7 - AVss  <-- GND
pin 13    SCK   - 3   6 - VoutB
pin 11    SDI   - 4   5 - /LDAC <-- not used tied to GND

Vout A/B to non-inverting opamp with gain ~ 1.225
  1 semitone = 68 milivolts
  5 octaves = 60 semitones = 4.080 volts
  external gain = 1.22549 
  R1 = 100k
  R2 = 22k + 1k trimmer
  gain = 1 + R2 / R1 ~ 1.22 -> 1.23
*/
void setup_cv_dac_hw()
{
  pinMode(CS_PIN_A,OUTPUT);
  digitalWrite(CS_PIN_A,HIGH);
  pinMode(CS_PIN_B,OUTPUT);
  digitalWrite(CS_PIN_B,HIGH);
  SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV2);
  set_cv_output_hw(0,0);
  set_cv_output_hw(1,0);
  set_cv_output_hw(2,0);
  set_cv_output_hw(3,0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}

void set_cv_output_hw( const byte thannel, const byte note_number)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
{
  const byte cv_out_map[4]={2,0,1,3};
  const byte channel = cv_out_map[thannel];
  //LDAC and shutdown not used
  //gain always set to 2x ( 4.096 max out)
  const unsigned int millivolts = (note_number%MAX_NOTE) * 68;
  const byte channel_cs_pin[VOICE_COUNT] = {CS_PIN_A,CS_PIN_A,CS_PIN_B,CS_PIN_B};
  const byte cs_pin = channel_cs_pin[channel%VOICE_COUNT];
  byte lowByte = millivolts & 0xff;
  byte highByte = ((millivolts >> 8) & 0xff)|0x10;
  if ((channel == 1)||(channel==3))
    highByte |= 0x80;
  digitalWrite(cs_pin,LOW);
  SPI.transfer(highByte);
  SPI.transfer(lowByte);
  digitalWrite(cs_pin,HIGH);
}

void setup_digital_io_hw()
{
  //digital inputs <--- TBD handle hw clk input
  pinMode(CLK_IN_PIN,INPUT_PULLUP);
  // TBD setup HW interrupt here
  
  //digital outputs 
  for (int idx = 0; idx < VOICE_COUNT; idx++)
  {
    pinMode(gate_out_pins[idx],OUTPUT);
    digitalWrite(gate_out_pins[idx],HIGH);
  }
  pinMode(CLK_OUT_PIN,OUTPUT);
  digitalWrite(CLK_OUT_PIN,HIGH);
}

void set_gate_output_hw( const byte channel, const boolean state)
{
  if (state)
    digitalWrite(gate_out_pins[channel],LOW);
  else
    digitalWrite(gate_out_pins[channel],HIGH);
}

void set_clock_output_hw( const boolean state)
{
  if (state)
    digitalWrite(CLK_OUT_PIN,LOW);
  else
    digitalWrite(CLK_OUT_PIN,HIGH);
}
byte get_x_from_button( const byte button )
{
  return (button & 0x3F) % GRID_HEIGHT;
}

byte get_y_from_button( const byte button )
{
  return (button & 0x3F) / GRID_WIDTH;
}

byte get_button_from_x_y( const byte x, const byte y )
{
  return (y * GRID_WIDTH) + x;
}


