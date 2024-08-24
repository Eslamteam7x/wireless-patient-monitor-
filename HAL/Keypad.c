#include "Keypad.h"

void Keypad_Init(void) {
	// Set rows (PC0 to PC3) as outputs
	DDRC |= ROW_MASK;
	PORTC |= ROW_MASK;  // Set all rows high
	
	// Set columns (PC4 to PC7) as inputs with pull-ups
	DDRC &= ~COL_MASK;
	PORTC |= COL_MASK;
}
const char keys[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
	{'1', '2', '3', '-'},
	{'M', '0', '=', '+'}
};
char Keypad_GetKey(void) {
	
	
	for (uint8_t row = 0; row < 4; row++) {
		// Set the current row low
		PORTC &= ~(1 << row);
		
		for (uint8_t col = 4; col < 8; col++) {
			if (!(PINC & (1 << col))) {
				// Debounce delay
				_delay_ms(50);
				if (!(PINC & (1 << col))) {
					// Wait for the key to be released
					while (!(PINC & (1 << col)));
					// Set the row back to high
					PORTC |= (1 << row);
					return keys[row][col - 4];
				}
			}
		}
		// Set the row back to high
		PORTC |= (1 << row);
	}
	
	return 0xff;  // Return null character if no key is pressed
}