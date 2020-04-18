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
#include "DateTime.h"


uint16_t DateTime::getYear()
{
	return year;
}

uint8_t DateTime::getMonth()
{
	return month;
}

uint8_t DateTime::getDay()
{
	return day;
}

uint8_t DateTime::getHour()
{
	return hour;
}

uint8_t DateTime::getMinute()
{
	return minute;
}

uint8_t DateTime::getSecond()
{
	return second;
}

void DateTime::setYear(uint16_t year)
{
	this->year = year;
}

void DateTime::setMonth(uint8_t month)
{
	this->month = month;
}

void DateTime::setDay(uint8_t day)
{
	this->day = day;
}

void DateTime::setHour(uint8_t hour)
{
	this->hour = hour;
}

void DateTime::setMinute(uint8_t minute)
{
	this->minute = minute;
}

void DateTime::setSecond(uint8_t second)
{
	this->second = second;
}
