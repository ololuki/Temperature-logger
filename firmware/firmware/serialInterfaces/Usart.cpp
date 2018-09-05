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
#include "Usart.h"
#include <avr/io.h>


#define USART_BAUD_RATE 9600
#define CHECK_BAUD_RATE_EXACT_MATCHING 0


#define UBRR (F_CPU/16/USART_BAUD_RATE - 1)

#if CHECK_BAUD_RATE_EXACT_MATCHING
#if (F_CPU/16/(UBRR + 1)) != USART_BAUD_RATE
  #warning not exact match between F_CPU and USART_BAUD_RATE
#endif
#endif


void Usart::init()
{
	enableTransmitter();
	writeUBRR();
	setTxPinAsOutput();
}

/// Put one character to Usart. Non blocking function.
void Usart::putchar(char c)
{
	UDR = c;
}

/// Put one character to Usart. First wait until data is sent.
void Usart::putcharBlocking(char c)
{
	// wait until last char is emited
	while (!isDataRegisterEmpty());
	UDR = c;
}

/// Send c-string. Put chars until '\0'. Function waits until whole data is sent.
void Usart::sendStr(const char* str)
{
	while (*str)
	{
		putcharBlocking(*str++);
	}
}

/// Send data. Put size bytes from buffer data. Function waits until whole data is sent.
void Usart::sendData(uint8_t* data, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		putcharBlocking(data[i]);
	}
}

void Usart::enableTransmitter()
{
	UCSRB |= (1 << TXEN);
}

void Usart::setTxPinAsOutput()
{
	DDRD |= (1 << PD1);
}

void Usart::writeUBRR()
{
	UBRRL = UBRR % 256;
	UBRRH = UBRR / 256;
}

bool Usart::isDataRegisterEmpty()
{
	return (UCSRA & (1 << UDRE));
}
