/*
 * TM1637_func.h
 *
 * Created: 8/19/2024 8:16:13 AM
 *  Author: esah2
 */ 


#ifndef TM1637_FUNC_H_
#define TM1637_FUNC_H_

void TM1637_Init(void);


void TM1637_Start(void);

void TM1637_Stop(void);

void TM1637_WriteByte(unsigned char data);

void TM1637_SendCommand(unsigned char command);

void TM1637_Display(unsigned char *digits);

unsigned char digitToSegment1(unsigned char digit);

#endif /* TM1637_FUNC_H_ */