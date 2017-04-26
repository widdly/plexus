#ifndef RECORD_H
#define RECORD_H

//record handlers
void record_setup();
void record_start( const byte voice );
void record_button_down ( const byte button);
boolean record_led_update();


#endif
