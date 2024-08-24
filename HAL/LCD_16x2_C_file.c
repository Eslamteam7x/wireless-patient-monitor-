


#include "LCD_16x2_H_file.h"						/* Include LCD header file */


void LCD_Command (char cmd)							/* LCD command write function */
{
	LCD_Data_Port = cmd;							/* Write command data to LCD data port */
	LCD_Command_Port &= ~((1<<RS)|(1<<RW));			/* Make RS LOW (command reg.), RW LOW (Write) */
	LCD_Command_Port |= (1<<EN);					/* High to Low transition on EN (Enable) */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);									/* Wait little bit */
}

void LCD_Char (char char_data)						/* LCD data write function */
{
	LCD_Data_Port = char_data;						/* Write data to LCD data port */
	LCD_Command_Port &= ~(1<<RW);					/* Make RW LOW (Write) */
	LCD_Command_Port |= (1<<EN)|(1<<RS);			/* Make RS HIGH (data reg.) and High to Low transition on EN (Enable) */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);									/* Wait little bit */
}

void LCD_Init (void)								/* LCD Initialize function */
{
	LCD_Command_Dir |= (1<<RS)|(1<<RW)|(1<<EN);		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;							/* Make LCD data port direction as o/p */
	
	_delay_ms(20);									/* LCD power up time to get things ready, it should always >15ms */
	LCD_Command (0x38);								/* Initialize 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);								/* Display ON, Cursor OFF command */
	LCD_Command (0x06);								/* Auto Increment cursor */
	LCD_Command (0x01);								/* Clear LCD command */
	LCD_Command (0x80);	
	//LCD_Command(CURSOR_ON);	
	LCD_Command(LCD_CURSOR_BLINK_ON);						/* 8 is for first line and 0 is for 0th position */
}

void LCD_String (char *str)							/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);							/* Call LCD data write */
	}
}

void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD function */
{
	if (row == 1)
		LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
		LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command(0x01);								/* clear display */
}


void LCD_GoToRowCol(char row, char col)
{
	char address;
	switch (row)
	{
		case 0:
		address = col;
		break;
		case 1:
		address = col + 0x40;
		break;
	}
	LCD_Command(address | SET_CURSOR_LOCATION);
}




void LCD_int_to_str(int num) {
	char buffer[32];  // Buffer to hold the string representation of the number
	int i = 0;
	int isNegative = 0;

	// Handle negative numbers
	if (num < 0) {
		isNegative = 1;
		num = -num;
	}

	// Process each digit
	do {
		buffer[i++] = (num % 10) + '0';  // Get next digit and convert to character
		num /= 10;
	} while (num > 0);

	// Add negative sign if the number was negative
	if (isNegative) {
		buffer[i++] = '-';
	}

	// Null-terminate the string
	buffer[i] = '\0';

	// Reverse the string (since the digits were added in reverse order)
	int start = 0;
	int end = i - 1;
	char temp;
	while (start < end) {
		temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;
		start++;
		end--;
	}

	// Print the string on the LCD
	LCD_String(buffer);
}
