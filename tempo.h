#ifndef TEMPO_H
#define TEMPO_H
#include "definitions.h"
//metro timer
extern int metro;
void set_metro(unsigned int interval_ms);
//tempo edit handlers
boolean tempo_update_led(); 
void tempo_button_down( const byte button );
void tempo_edit_start();
#endif
