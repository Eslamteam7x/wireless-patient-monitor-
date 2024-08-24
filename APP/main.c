
/*
 * wireless patien health monitor.c
 *
 * Created: 8/12/2024 10:04:12 PM
 * Author : esah2
 */

#include "../MCAL/Micro_config.h"
#include "../HAL/LCD_16x2_H_file.h"
#include "../HAL/Keypad.h"
#include "../HAL/TM1637_func.h"
#define BEAT_DETECTION_THRESHOLD 512  // Adjust this based on your sensor
#define MEASUREMENT_PERIOD_MS 60000   // 1 minute in milliseconds

uint16_t calculate_BPM (uint8_t channel) ;

/*########################################################################################################################*/
/*Global Variable*/
static u8 password[4]="";	//password before build no password
static u8 state=0;			//to know the state
static u8 trial='1';			//  global variable for trials
float temperature = 0;
float temperature1 = 0;


float read=0;
float read1=0;
float reslution=1024;
float v_ref=5;
float  volt=0;
float volt1;
/*########################################################################################################################*/

int main(void)
{
  LCD_Init();
   UART_Init(9600);
    Keypad_Init();
    ADC_Init();
    DDRD =0xff;
    Clear_Bit(PORTD,PIND3);
    Set_Bit(PORTD,PIND3);
	Clear_Bit(PORTD,PIND);
	
    char num=0;
    char BPM=0;
    DDRA=0;
LCD_String_xy(1,5,"WELCOME");
LCD_String_xy(2,0,"Dr.Ashraf Rmdan");
_delay_ms(1000);
LCD_Clear();

    LCD_String_xy(1,0,"Temp1");
	LCD_String_xy(1,11,"Temp2");
	LCD_String_xy(1,6,"BPM");
	_delay_ms(100);

	Clear_Bit(PORTD,PIND0);
	Set_Bit(PORTD,PIND0);
	Clear_Bit(PORTD,PIND1);
	Set_Bit(PORTD,PIND1);
while(1)
    {

		read=ADC_Read(0);
		read1=ADC_Read(1);
		if(BPM||(READ_BIT(PIND,PIND3))){
		if(READ_BIT(PIND,PIND4))
		{
			BPM++;
			if(BPM==80)
			BPM=0;
		}
		}
		LCD_GoToRowCol(1,7);
		LCD_String("   ");
		LCD_GoToRowCol(1,7);
        LCD_int_to_str(BPM);
		UART_SendString("tmp1: ");
		UART_SendInteger((int)temperature);
		UART_SendString("   tmp2: ");
		UART_SendInteger((int)temperature1);
		UART_SendString("   BPM: ");
		UART_SendInteger((int)BPM);
		UART_TxChar('\r');
		
		
						 
    }
 
 
 
 
 
		
    return 0;
}









ISR(ADC_vect)
{


    volt= (read  /reslution* v_ref);
    temperature = (volt - 0.5)*100 ;

    LCD_GoToRowCol(1,0);
    LCD_String("   ");
    LCD_GoToRowCol(1,0);
    LCD_int_to_str(temperature);
	 volt1= (read1  /reslution* v_ref);
	 temperature1 = (volt1 - 0.5)*100 ;

	 LCD_GoToRowCol(1,12);
	 LCD_String("   ");
	 LCD_GoToRowCol(1,12);
	 LCD_int_to_str(temperature1);
    _delay_ms(100);
	

}










u8 scan_password(void)
{
    u8 PASS_entry[4]="";
    u8 i,temp;
    LCD_Clear();
    LCD_String("ENTER PASWWORD");

    LCD_GoToRowCol(1,0);
    LCD_String("try ");
    LCD_Char(trial);
    LCD_String(" : ");
    for(i=0; i<4; i++)
    {
        while(1)
        {
            temp=Keypad_GetKey();
            if(temp!=0xff)
            {
                PASS_entry[i]=temp;
                LCD_Char('*')	;
                _delay_ms(150);
                if(PASS_entry[i]=='+')
                {
                    state='+';
                    return state;
                }

                break;
            }

        }
    }
    for(i=0; i<4; i++)
    {
        if(PASS_entry[i]==password[i]);
        else
        {
            LCD_Clear();
            LCD_String("FALSE PASS");
            _delay_ms(1000);
            trial++;
            if(trial=='4')
            {
                return '-';
            }
            return 0;
        }

    }
    LCD_Clear();
    LCD_GoToRowCol(2,0);
    LCD_String("TRUE PASS");
    trial='1';
    return 1;

}



uint16_t calculate_BPM (uint8_t channel) {
	uint16_t bpm = 0;
	uint16_t threshold = 512; // ﬁÌ„… ⁄ »… · ÕœÌœ «·ﬁ„„ (ÌÃ» ÷»ÿÂ« Õ”» «·≈‘«—…)
	uint16_t signal;
	uint16_t peak_count = 0;
	uint16_t time_interval = 0;

	// ﬁ—«¡… «·≈‘«—… ·„œ… 10 ÀÊ«‰Ú ·Õ”«» BPM
	for (uint16_t i = 0; i < 10000; i++) {
		signal = ADC_Read(channel);

		// «ﬂ ‘«› «·ﬁ„…
		if (signal > threshold) {
			peak_count++;
			// «‰ Ÿ«— ‰“Ê· «·≈‘«—…  Õ  «·⁄ »… · Ã‰» «·⁄œ «·„ ﬂ—— ·‰›” «·ﬁ„…
			while (ADC_Read(channel) > threshold) {
				_delay_ms(1);
			}
		}

		_delay_ms(1); //  √ŒÌ— 1 „·Ì À«‰Ì… »Ì‰ ﬂ· ﬁ—«¡…
	}

	// Õ”«» BPM: ⁄œœ «·ﬁ„„ ›Ì 10 ÀÊ«‰Ú * 6 = BPM
	bpm = peak_count * 6;

	return bpm;
}






