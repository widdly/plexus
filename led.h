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
