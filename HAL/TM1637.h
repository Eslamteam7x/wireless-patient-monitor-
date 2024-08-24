#include <avr/io.h>
#include <util/delay.h>

// Define TM1637 GPIO pins
#define TM1637_CLK_PORT PORTC
#define TM1637_CLK_DDR  DDRC
#define TM1637_CLK_PIN  PINC0

#define TM1637_DIO_PORT PORTC
#define TM1637_DIO_DDR  DDRC
#define TM1637_DIO_PIN  PINC1

// Define GPIO operations
#define TM1637_CLK_HIGH() (TM1637_CLK_PORT |= (1 << TM1637_CLK_PIN))
#define TM1637_CLK_LOW()  (TM1637_CLK_PORT &= ~(1 << TM1637_CLK_PIN))

#define TM1637_DIO_HIGH() (TM1637_DIO_PORT |= (1 << TM1637_DIO_PIN))
#define TM1637_DIO_LOW()  (TM1637_DIO_PORT &= ~(1 << TM1637_DIO_PIN))


