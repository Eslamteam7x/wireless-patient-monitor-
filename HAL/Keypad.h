#ifndef KEYPAD_DRIVER_H
#define KEYPAD_DRIVER_H

#include <avr/io.h>
#include <util/delay.h>

// Define the row and column pins for the keypad on PORTC
#define ROW_MASK 0x0F  // PC0 to PC3
#define COL_MASK 0xF0  // PC4 to PC7
void Keypad_Init(void);
char Keypad_GetKey(void);

#endif
