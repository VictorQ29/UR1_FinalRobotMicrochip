/*
 * motorcontrol.c
 *
 * Created: 4/25/2022 3:56:50 PM
 * Author : vqueinnec
 */ 

#include "F_cpu_lib.h" 
#include <avr/io.h>
#include <util/delay.h>
#include "LCD_lib.h"
#include "Serial_lib2.h"

void ClearScreen();

int main(void)
{
		HBridgeInit();
		uint8_t CharData; // character received from PC via serial port
		char mystring[20];
		uint8_t NewString = 0;  // starting a new input string
		int StringValue = 0;  // accumulated numeric value for string received from PC
		uint8_t StrCount = 0;
		int tmpnum= 0;
		uint8_t num_char;
		DDRC |= 1 << PORTC2; // set DDRC for Pin2 to 1 – output – do not modify other pins (ERE controller board)
		char number_out[8];
		LCD_init();
		USART_vInit();
		sei();
		LCDGoToPosition(1,1);
		LCDSendString("Ready");
		_delay_ms(2000);
		
		
		while(1)
		{
			
			CharData =USART_vReceiveByte();
			LCDGoToPosition(1,3);
			LCDSendCharacter(CharData);
		
				if(CharData == 's')//if the character sent by visual studio is 's' then stop the motors
				{
					HBridgeCommand(0, 0, 1);
					HBridgeCommand(1, 0, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);	
				}
				else if(CharData == 'f')//if the character sent by visual studio is 'f' then go forward
				{
					HBridgeCommand(0, 50, 1); //motors go a the same speed to go straight 
					HBridgeCommand(1, 50, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);
				}
				else if(CharData == 'R')//hard right
				{
					HBridgeCommand(0, 50, 1);
					HBridgeCommand(1, 0, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);
				}
				else if(CharData == 'L')//hard left
				{
					HBridgeCommand(0, 0, 1);
					HBridgeCommand(1, 50, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);
				}
				else if(CharData == 'r')//slight right
				{
					HBridgeCommand(0, 50, 1);
					HBridgeCommand(1, 25, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);
				}
				else if(CharData == 'l')//slight left
				{
					HBridgeCommand(0, 25, 1);
					HBridgeCommand(1, 50, 1);
					LCDGoToPosition(1,3);
					LCDSendCharacter(CharData);
				}
			}
}
void ClearScreen()//function to clear the LCD
{
	LCDGoToPosition(1,1);
	LCDSendString("                    ");
	LCDGoToPosition(1,2);
	LCDSendString("                    ");
	LCDGoToPosition(1,3);
	LCDSendString("                    ");
	LCDGoToPosition(1,4);
	LCDSendString("                    ");
	
}