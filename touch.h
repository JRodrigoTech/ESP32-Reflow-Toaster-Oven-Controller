// Touch Variables
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

unsigned long touch_flag;
unsigned long timeoutstart = 0;
unsigned long timeoutstop = 0;
boolean TouchRead = false ;

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
