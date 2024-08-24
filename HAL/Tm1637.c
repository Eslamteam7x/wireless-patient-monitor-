
#include "TM1637.h"
// Initialize TM1637
void TM1637_Init(void) {
	// Set CLK and DIO as outputs
	TM1637_CLK_DDR |= (1 << TM1637_CLK_PIN);
	TM1637_DIO_DDR |= (1 << TM1637_DIO_PIN);

	TM1637_CLK_HIGH();
	TM1637_DIO_HIGH();
}

// Start condition for TM1637
void TM1637_Start(void) {
	TM1637_CLK_HIGH();
	TM1637_DIO_HIGH();
	_delay_us(2); // Short delay
	TM1637_DIO_LOW();
}

// Stop condition for TM1637
void TM1637_Stop(void) {
	TM1637_CLK_LOW();
	TM1637_DIO_LOW();
	_delay_us(2); // Short delay
	TM1637_CLK_HIGH();
	TM1637_DIO_HIGH();
}

// Write a byte to TM1637
void TM1637_WriteByte(unsigned char data) {
	for (unsigned char i = 0; i < 8; i++) {
		TM1637_CLK_LOW();
		if (data & 0x01) {
			TM1637_DIO_HIGH();
			} else {
			TM1637_DIO_LOW();
		}
		data >>= 1;
		TM1637_CLK_HIGH();
		_delay_us(2); // Short delay
	}

	// Wait for the acknowledgment
	TM1637_CLK_LOW();
	TM1637_DIO_HIGH();
	TM1637_CLK_HIGH();
	_delay_us(2); // Short delay
	TM1637_CLK_LOW();
}

// Send a command to TM1637
void TM1637_SendCommand(unsigned char command) {
	TM1637_Start();
	TM1637_WriteByte(command);
	TM1637_Stop();
}

// Display digits on TM1637
void TM1637_Display(unsigned char *digits) {
	TM1637_SendCommand(0x40); // Data command

	TM1637_Start();
	TM1637_WriteByte(0xC0); // Address command (start from the first digit)
	
	for (unsigned char i = 0; i < 4; i++) {
		TM1637_WriteByte(digits[i]);
	}
	
	TM1637_Stop();

	// Set display control command (brightness level)
	TM1637_SendCommand(0x8F);
}

// Digit to 7-segment mapping (0-9)
unsigned char digitToSegment[] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

unsigned char digitToSegment1(unsigned char digit) {
	switch(digit) {
		case 0: return 0b00111111; // 0
		break;
		case 1: return 0b00000110; // 1
		break;
		case 2: return 0b01011011; // 2
		break;
		case 3: return 0b01001111; // 3
		break;
		case 4: return 0b01100110; // 4
		break;
		case 5: return 0b01101101; // 5
		break;
		case 6: return 0b01111101; // 6
		break;
		case 7: return 0b00000111; // 7
		break;
		case 8: return 0b01111111; // 8
		break;
		case 9: return 0b01101111; // 9
		break;
		default: return 0b00000000; // Invalid digit, turn off all segments
	}
}


