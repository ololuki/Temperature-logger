/*
Copyright (C) 2018 - 2020 Ololuki
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
#ifndef DateTime_H
#define DateTime_H

#include "gui/View.h"
#include "gui/ViewStack.h"
#include "gui/MenuView.h"
#include "serialInterfaces/Usart.h"


class DateTime
{
public:
	uint16_t getYear();
	uint8_t getMonth();
	uint8_t getDay();
	uint8_t getHour();
	uint8_t getMinute();
	uint8_t getSecond();

	void setYear(uint16_t year);
	void setMonth(uint8_t month);
	void setDay(uint8_t day);
	void setHour(uint8_t hour);
	void setMinute(uint8_t minute);
	void setSecond(uint8_t second);
private:
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
};

#endif // DateTime_H
