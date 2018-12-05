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
#ifndef KEYBOARD_HAL_AVR_H
#define KEYBOARD_HAL_AVR_H

#include <stdint.h>
#include <avr/io.h>
#include "devices/keyboard/KeyEvent.h"
#include "devices/keyboard/KeyboardHAL.h"


class KeyboardHALAVR : public KeyboardHAL
{
public:
	KeyboardHALAVR()
	{
		PORTA |= (1 << PA0);
		PORTA |= (1 << PA1);
		PORTA |= (1 << PA2);
		PORTA |= (1 << PA3);
		PORTA |= (1 << PA4);
		PORTA |= (1 << PA5);
	}
	KeyState keyState(Key key)
	{
		switch(key)
		{
			case Key::Left:
				return (PINA & (1 << PA0)) ? KeyState::Released : KeyState::Pressed;
			case Key::Right:
				return (PINA & (1 << PA1)) ? KeyState::Released : KeyState::Pressed;
			case Key::Up:
				return (PINA & (1 << PA2)) ? KeyState::Released : KeyState::Pressed;
			case Key::Down:
				return (PINA & (1 << PA3)) ? KeyState::Released : KeyState::Pressed;
			case Key::Escape:
				return (PINA & (1 << PA4)) ? KeyState::Released : KeyState::Pressed;
			case Key::Enter:
				return (PINA & (1 << PA5)) ? KeyState::Released : KeyState::Pressed;
			default:
				return KeyState::Released;
		}
	}
};


#endif // KEYBOARD_HAL_AVR_H
