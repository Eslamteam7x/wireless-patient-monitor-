/*
 * LCD_16x2_H_file.h
 * http://www.electronicwings.com
 *
 */

#ifndef LCD_16x2_H_H_					/* Define library H file if not defined */
#define LCD_16x2_H_H_

#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8MHz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include Delay header file */

#define LCD_Data_Dir DDRB				/* Define LCD data port direction */
#define LCD_Command_Dir DDRD			/* Define LCD command port direction register */
#define LCD_Data_Port PORTB			    /* Define LCD data port */
#define LCD_Command_Port PORTD	        /* Define LCD data port */
#define EN PD7							/* Define Enable signal pin */
#define RW PD6							/* Define Read/Write signal pin */
#define RS PD5							/* Define Register Select (data reg./command reg.) signal pin */


#define Eight_Bit_Mode			0x38
#define CLEAR_COMMAND			0x01
#define CURSOR_OFF				0x0C
#define CURSOR_ON				0x0E
#define SET_CURSOR_LOCATION		0x80
#define LCD_CURSOR_BLINK_ON     0x0F
#define LCD_CURSOR_BLINK_OFF    0x0E
#define LCD_SHIFT_LEFT          0x18
#define LCD_SHIFT_RIGHT         0x1C
#define LCD_FUNCTION_SET        0x28
#define LCD_SET_CURSOR          0x80
#define LCD_CURSOR_LINE1        0x80
#define LCD_CURSOR_LINE2        0xC0


void LCD_Command (char);				/* LCD command write function */
void LCD_Char (char);					/* LCD data write function */
void LCD_Init (void);					/* LCD Initialize function */
void LCD_String (char*);				/* Send string to LCD function */
void LCD_String_xy (char,char,char*);	/* Send row, position and string to LCD function */
void LCD_Clear();						/* Clear LCD*/
void LCD_GoToRowCol(char row, char col);
void LCD_int_to_str(int num);

#endif									/* LCD_16x2_H_FILE_H_ */