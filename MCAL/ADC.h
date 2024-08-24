/*
 * ADC.h
 *
 * Created: 8/12/2024 10:34:40 PM
 *  Author: esah2
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "Micro_config.h"
void ADC_Init(void);
void ADC_StartConversion(uint8_t channel);
void ADC_SetCallback(void (*callback)(uint16_t));
int  ADC_Read(uint8_t channel);




#endif /* ADC_H_ */