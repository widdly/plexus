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
#ifndef LED_H
#define LED_H
#include "definitions.h"
#include "tempo.h"
extern boolean right_led_update;
extern boolean top_led_update;
extern boolean grid_led_update;
//led functions
boolean set_right_led(byte position, byte color );
boolean set_top_led(byte position, byte color );
boolean set_grid_led(byte position, byte color );
#endif
