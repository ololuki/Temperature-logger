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
#include <stdbool.h>

#define USART_BAUD_RATE 9600
#define CHECK_BAUD_RATE_EXACT_MATCHING 0


#define UBRR (F_CPU/16/USART_BAUD_RATE - 1)

#if CHECK_BAUD_RATE_EXACT_MATCHING
#if (F_CPU/16/(UBRR + 1)) != USART_BAUD_RATE
  #warning not exact match between F_CPU and USART_BAUD_RATE
#endif
#endif


static inline void usart_enableTransmitter();
static inline void usart_setTxPinAsOutput();
static inline void usart_writeUBRR();
static inline bool usart_isDataRegisterEmpty();

void usart_init()
{
	usart_enableTransmitter();
	usart_writeUBRR();
	usart_setTxPinAsOutput();
}

/// Put one character to Usart. Non blocking function.
void usart_putchar(char c)
{
	UDR = c;
}

/// Put one character to Usart. First wait until data is sent.
void usart_putcharBlocking(char c)
{
	// wait until last char is emited
	while (!usart_isDataRegisterEmpty());
	UDR = c;
}

/// Send c-string. Put chars until '\0'. Function waits until whole data is sent.
void usart_sendStr(const char* str)
{
	while (*str)
	{
		usart_putcharBlocking(*str++);
	}
}

/// Send data. Put size bytes from buffer data. Function waits until whole data is sent.
void usart_sendData(uint8_t* data, uint16_t size)
{
	for (uint16_t i = 0; i < size; i++)
	{
		usart_putcharBlocking(data[i]);
	}
}

void usart_enableTransmitter()
{
	UCSRB |= (1 << TXEN);
}

void usart_setTxPinAsOutput()
{
	DDRD |= (1 << PD1);
}

void usart_writeUBRR()
{
	UBRRL = UBRR % 256;
	UBRRH = UBRR / 256;
}

bool usart_isDataRegisterEmpty()
{
	return (UCSRA & (1 << UDRE));
}
