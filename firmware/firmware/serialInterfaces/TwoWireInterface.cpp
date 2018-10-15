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
#include "TwoWireInterface.h"

#include "serialInterfaces/Usart.h"
#include <avr/io.h>


#define ENABLE_TRACE 0

#if (ENABLE_TRACE == 1)
	#define TRACE(...) usart_printf(__VA_ARGS__);
#else
	#define TRACE(...)
#endif

volatile uint8_t TwoWireInterface::timeoutCounter;

bool TwoWireInterface::isError = false;
bool TwoWireInterface::isErrorOccured()
{
	return isError;
}

bool TwoWireInterface::isSetTwint()
{
	return (TWCR & (1 << TWINT));
}

void TwoWireInterface::init()
{
	// TODO: converting from fclk i FCPU to TWBR
	TWBR = 32;	// FCPU = 8MHz fclk = 100kHz
}

void TwoWireInterface::onTimer()
{
	timeoutCounter--;
}

void TwoWireInterface::start()
{
	TRACE((char*)"\r\nSTART  ");
	TWCR |= 0b10100100;
	
	timeoutCounter = 200;
	while(timeoutCounter)
	{
		if (isSetTwint())
		{
			TRACE((char*)"%x", (TWSR & 0xFC));
			return;
		}
	}
	isError = 1;
}

void TwoWireInterface::stop()
{
	TWCR |= 0b10010100;
	TRACE((char*)"\r\nSTOP %x", (TWSR & 0xFC));
}

void TwoWireInterface::sendByte(uint8_t byte, bool* isAck)
{
	TRACE((char*)"\r\nSend  ");
	TWDR = byte;
	TWCR = 0b10000100;
	timeoutCounter = 200;
	while(timeoutCounter)
	{
		if (isSetTwint())
		{
			TRACE((char*)"%x", (TWSR & 0xFC));
			//isAck // TODO: read ACK i NACK
			return;
		}
	}
	isError = 1;
	TRACE((char*)"\r\nSendError  %x", (TWSR & 0xFC));
	//isAck = 0;	// TODO: read ACK i NACK
	
	return;
}

uint8_t TwoWireInterface::receiveByte(bool sendAck)
{
	TWCR = (0b10000100 | (sendAck << TWEA)); // add ACK bit
	TRACE((char*)"\r\nGet  ");
	timeoutCounter = 200;
	while(timeoutCounter)
	{
		if (isSetTwint())
		{
			TRACE((char*)"%x", (TWSR & 0xFC));
			return TWDR;
		}
	}
	isError = 1;
	TRACE((char*)"\r\nReceiveError  %x", (TWSR & 0xFC));
	return 0;
}

void TwoWireInterface::sendData(uint8_t address, uint8_t* data, uint8_t size)
{
//	if(twi_isErrorOccured())
//	{
//		twi_reset();
//	}
	start();
	sendByte(address | I2C_WRITE);	// write to TEA5767
	for(uint8_t i = 0; i < size; i++)
	{
		sendByte(data[i]);
	}
	stop();
	//if(twi_isErrorOccured()) return 1;
	//return 0;
}

void TwoWireInterface::receiveData(uint8_t address, uint8_t* data, uint8_t size, bool* isError)
{
//	if(twi_isErrorOccured())
//	{
//		twi_reset();
//	}
	start();
	sendByte(address | I2C_READ);
	for(uint8_t i = 0; i < size-1; i++)	// for last byte do not send ACK
	{
		data[i] = receiveByte(I2C_ACK);
	}
	data[size-1] = receiveByte(I2C_NACK);	// send NACK for last byte
	stop();
	//if(twi_isErrorOccured()) return 1;
	//return 0;
}

void TwoWireInterface::sendAndReceiveData(uint8_t address, uint8_t* sendBuffer, uint8_t sendSize, uint8_t* receiveBuffer, uint8_t receiveSize)
{
//	if(twi_isErrorOccured())
//	{
//		twi_reset();
//	}
	start();
	sendByte(address | I2C_WRITE);
	for(uint8_t i = 0; i < sendSize; i++)
	{
		sendByte(sendBuffer[i]);
	}
	start();
	sendByte(address | I2C_READ);
	for(uint8_t i = 0; i < receiveSize-1; i++)	// for last byte do not send ACK
	{
		receiveBuffer[i] = receiveByte(I2C_ACK);
	}
	receiveBuffer[receiveSize-1] = receiveByte(I2C_NACK);	// send NACK for last byte
	stop();
	//if(twi_isErrorOccured()) return 1;
	//return 0;
}

//void twi_reset(void)
//{
//	twi_stop();
//	//isError = 0;
//}

