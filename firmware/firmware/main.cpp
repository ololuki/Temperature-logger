/*
Copyright (C) 2018 Ololuki
https://ololuki.pl

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "serialInterfaces/Usart.h"
#include "devices/LcdHd44780.h"
#include "serialInterfaces/TwoWireInterface.h"
#include "devices/Ds3231.h"

#include <util/delay.h>
#include <stdio.h>


int main(void)
{
	usart_init();
	usart_printf("Hello %s\r\n", "test");
	usart_printf_P(PSTR("second %s from program memory\r\n"), "test");
	
	TwoWireInterface twi;
	twi.init();
	
	LcdHd44780 lcd;
	lcd.powerOnWait();
	lcd.init();
	lcd.print("Hello");
	lcd.cursor(1,0);
	lcd.print("Hello");

	while(1)
	{
		uint8_t dateTimeBuf[10];
		Ds3231::readDateTime(dateTimeBuf, 10);
		
		char time[20];
		sprintf(time, "%d%d:%d%d:%d%d",
				(dateTimeBuf[2] >> 4) & 0x03,
				dateTimeBuf[2] & 0x0F,
				dateTimeBuf[1] >> 4,
				dateTimeBuf[1] & 0x0F,
				dateTimeBuf[0] >> 4,
				dateTimeBuf[0] & 0x0F
				);
		
		char date[20];
		sprintf(date, "20%d%d-%d%d-%d%d",
				dateTimeBuf[6] >> 4,
				dateTimeBuf[6] & 0x0F,
				(dateTimeBuf[5] >> 4) & 0x01,
				dateTimeBuf[5] & 0x0F,
				dateTimeBuf[4] >> 4,
				dateTimeBuf[4] & 0x0F
				);
		
		lcd.cursor(0,0);
		lcd.print(time);

		lcd.cursor(1,0);
		lcd.print(date);

		_delay_ms(500);

	}
	;

	return 0;
}
