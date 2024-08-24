

#include "UART_Interrupt.h"
#include "../HAL/LCD_16x2_H_file.h"
void UART_Init(unsigned int baud)
{
	unsigned int ubrr = F_CPU/16/baud-1;
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN)|(1<<TXEN);    // Enable receiver and transmitter
	UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1); // 8-bit data format
}


char UART_RXChar()									/* Data receiving function */
{
	while (!(UCSRA & (1 << RXC)));					/* Wait until new data receive */
	return(UDR);									/* Get and return received data */
}

void UART_TxChar(char data)						/* Data transmitting function */
{
	UDR = data;										/* Write data to be transmitting in UDR */
	while (!(UCSRA & (1<<UDRE)));					/* Wait until data transmit and buffer get empty */
}

void UART_SendString(char *str)					/* Send string of USART data function */
{
	int i=0;
	while (str[i]!=0)
	{
		UART_TxChar(str[i]);						/* Send each char of string till the NULL */
		i++;
	}
}


char UART_Receive_With_Timeout(uint16_t timeout)
{
	uint16_t count = 0;
	while (!(UCSRA & (1<<RXC))) // Wait for data to be received
	{
		_delay_us(1); // Delay for 1 microsecond (adjust if necessary)
		count++;
		if (count >= timeout) // Check if the timeout has been reached
		{
			return '\0'; // Return null character if timeout occurs
		}
	}
	return UDR; // Get and return received data from buffer
}


u8 frame(u8 *str,u8 *s1,u8*s2,u8*pnum1,u8*pnum2)
{
	u8 i=0,j=0,k=0,flag=0,temp,status=1;
	u16 num1=0,num2=0;
	while(str[i]!='\0')
	{
		if (str[i]==',')
		{
			flag++;
		}
		else
		{
			if (flag==0)
			{
				s1[j]=str[i];
				j++;
			}
			else if (flag==1)
			{
				if ((str[i]>='0')&&(str[i]<='9'))
				{
					temp=str[i]-'0';
					num1=num1*10+temp;
				}
				else
				status=0;
				
			}
			else if (flag==2)
			{
				s2[k]=str[i];
				k++;
			}
			else if (flag==3)
			{
				temp=str[i]-'0';
				num2=num2*10+temp;
			}
		}
		
		i++;
	}
	s1[j]='\0';
	s2[k]='\0';
	*pnum1=num1;
	*pnum2=num2;
	if (flag!=3)
	{
		status=0;
	}
	return status;
}
void UART_SendString_MYProtocol(u8 * str)
{
	u8 lenth;
	u16 sum;
	for(lenth=0;str[lenth];lenth++)
	{
		sum+=str[lenth];
	}
	UART_TxChar(lenth);
	
	for(lenth=0;str[lenth];lenth++)
	{
		UART_TxChar(str[lenth]);
	}

UART_TxChar((u8)sum);
UART_TxChar((u8)(sum >> 8));

}

u8 UART_receiveString_MYProtocol(u8 * str)
{
	u8 lenth=UART_RXChar();
	u8 i,first,second;
	u16 cheaksum_local=0,cheaksum_recieve=0;
	for(i=0;i,lenth;i++)
	{
		str[i]=UART_RXChar();
		cheaksum_local+=str[i];
	}
	str[i]=0;
	first=UART_RXChar();
	second=UART_RXChar();
	cheaksum_recieve=(first|(second<<8));
	if(cheaksum_recieve==cheaksum_local)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}
void UART_ReceiveString(u8*str)
{
u8 i=0;
str[i]=UART_RXChar();
while(str[i]!=13)
{
	i++;
	str[i]=UART_RXChar();
	
}
str[i]=0;
}



void UART_ReceiveString_no_wait(u8*str)
{
	u8 i=0;
	if((UCSRA & (1 << RXC)))
	{
	str[i]=UART_RXChar();
	while(str[i]!=13)
	{
		i++;
		str[i]=UART_RXChar();
		
	}
	str[i]=0;
	}
	else
	{
		
	}
}
void UART_SendInteger(int num) {
	char buffer[10]; // Buffer to hold the converted string
	itoa(num, buffer, 10); // Convert integer to string (base 10)
	UART_SendString(buffer); // Send the string via UART
}