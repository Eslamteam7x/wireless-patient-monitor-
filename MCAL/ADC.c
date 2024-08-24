#include "ADC.h"

static void (*ADC_Callback)(uint16_t) = 0;  // Function pointer for the ADC callback

void ADC_Init(void) {
	// Set ADC reference voltage to AVCC with external capacitor at AREF pin
	ADMUX = (1 << REFS0);

	// Enable ADC, enable ADC interrupt, set prescaler to 64 (for 8 MHz clock)
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1);

	// Enable global interrupts
	sei();
}

void ADC_StartConversion(uint8_t channel) {
	// Select ADC channel with safety mask (AND with 0b00001111 to ensure it’s between 0 and 7)
	channel &= 0x07;
	ADMUX = (ADMUX & 0xF8) | channel;

	// Start single conversion by setting ADSC bit
	ADCSRA |= (1 << ADSC);
}

void ADC_SetCallback(void (*callback)(uint16_t)) {
	ADC_Callback = callback;
}

/*ISR(ADC_vect) {
	// Check if a callback is set
	if (ADC_Callback != 0) {
		// Call the callback function with the ADC result
		ADC_Callback(ADC);
	}
}*/


int  ADC_Read(uint8_t channel) {
	// Select the ADC channel (0 to 7) with safety mask
	channel &= 0x07;  // Ensure the channel is between 0 and 7
	ADMUX = (ADMUX & 0xF8) | channel;

	// Start the conversion by setting the ADSC bit
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Return the ADC result
	return ADC;
}