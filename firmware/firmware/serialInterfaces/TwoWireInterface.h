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
#ifndef TWOWIREINTERFACE_H
#define TWOWIREINTERFACE_H

#include <stdint.h>


class TwoWireInterface
{
public:
	static void init();
	static void onTimer();
	static void start();
	static void stop();
	static void sendByte(uint8_t byte, bool* isAck = nullptr);
	static uint8_t receiveByte(bool sendAck);
	static void sendData(uint8_t address, uint8_t* data, uint8_t size);
	static void receiveData(uint8_t address, uint8_t* data, uint8_t size, bool* isError = nullptr);
	static void sendAndReceiveData(uint8_t address, uint8_t* sendBuffer, uint8_t sendSize, uint8_t* receiveBuffer, uint8_t receiveSize);

private:
	static volatile uint8_t timeoutCounter;
	static bool isError;
	static bool isErrorOccured();
	static inline bool isSetTwint();

	static const uint8_t I2C_WRITE = 0;
	static const uint8_t I2C_READ = 1;
	static const uint8_t I2C_ACK = 1;
	static const uint8_t I2C_NACK = 0;
};


#endif // TWOWIREINTERFACE_H
