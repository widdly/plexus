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

