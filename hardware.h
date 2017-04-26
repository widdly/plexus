#ifndef HARDWARE_H
#define HARDWARE_H
#include "definitions.h"
//dac and hw out handlers
void setup_cv_dac_hw();
void set_cv_output_hw( const byte channel, const byte note_number);
void setup_digital_io_hw();
void set_gate_output_hw( const byte channel, const boolean state);
void set_clock_output_hw( const boolean state);
//helper functions 
byte get_x_from_button( const byte button );
byte get_y_from_button( const byte button );
byte get_button_from_x_y( const byte x, const byte y );
#endif

