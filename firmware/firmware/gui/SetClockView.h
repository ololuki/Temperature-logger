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
#ifndef SETCLOCKVIEW_H
#define SETCLOCKVIEW_H

#include "gui/View.h"
#include "gui/ViewStack.h"
#include "gui/MenuView.h"
#include "objects/DateTime.h"
#include "serialInterfaces/Usart.h"


class SetClockView : public View
{
public:
	SetClockView(ViewStack* gui) : View(gui)
	{
		usart_printf("SetClockView constructor\r\n");
	}
	void onButton(KeyEvent keyEvent) override
	{
		switch(keyEvent.getKey())
		{
			case Key::Enter:
				usart_printf("SetClockView on enter\r\n");
				// save data to RTC
				break;
			case Key::Escape:
				break;
			case Key::Right:
				// next digit edit
				if(position < secondsOnes)
					++position;
				break;
			case Key::Left:
				// previous digit edit
				if(position > 0)
					--position;
				break;
			case Key::Up:
				//digit++
				break;
			case Key::Down:
				//digit--
				break;
			default:
				break;
		}
	}
	void render() override;

private:
	enum editedDigit
	{
		hourTens,
		hourOnes,
		minutesTens,
		minutesOnes,
		secondsTens,
		secondsOnes
	};
	void renderClock();
	uint8_t position;
	DateTime editedDateTime;
};

#endif // SETCLOCKVIEW_H
