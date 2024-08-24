/*
 * USART_Interrupt.h
 *
 * Created: 05/09/2016 4:57:37 PM
 *  Author: amrut
 */ 


#ifndef USART_INTERRUPT_H_
#define USART_INTERRUPT_H_
#define F_CPU 8000000UL						/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>							/* Include AVR std. library file */
#include <avr/interrupt.h>
#include "Std_Types.h"
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)	/* Define prescale value */

void UART_Init(unsigned int baud)	;			/* UART initialize function */
char UART_RxChar();						/* Data receiving function */
void UART_TxChar(char);					/* Data transmitting function */
void UART_SendString(char*);				/* Send string of USART data function */
char UART_Receive_With_Timeout(uint16_t timeout);
void UART_SendString_MYProtocol(u8 * str);
u8 UART_receiveString_MYProtocol(u8 * str);
void UART_ReceiveString(u8*str);
void UART_ReceiveString_no_wait(u8*str);
void UART_SendInteger(int num);






#endif /* USART_INTERRUPT_H_ */