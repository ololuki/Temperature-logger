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
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "devices/keyboard/KeyEvent.h"
#include "devices/keyboard/KeyboardHAL.h"


const uint8_t numberOfKeys = static_cast<uint8_t>(Key::Escape);

/// times button must be read pressed in onTimer to count as pressed
const uint8_t minPressed = 2;

/// times button must be read released in onTimer to count as released
const uint8_t minReleased = 3;

struct ButtonState
{
	ButtonState() : ticksPressed(0), ticksReleased(0) {}
	uint8_t ticksPressed : 6;
	uint8_t ticksReleased : 2;
	KeyState confirmedState = KeyState::Released;
};

class KeyEventQueue
{
public:
	KeyEvent front()
	{
		return event[0];
	}
	void pop()
	{
		event[0] = KeyEvent();
	}
	void lockAndClear(); // TODO: will disable input
	void unlock(); // TODO: will unlock keyboard and allow new events
	void push_back(KeyEvent keyEvent)
	{
		event[0] = keyEvent;
	}
private:
	KeyEvent event[1];
};

class Keyboard
{
public:
	Keyboard(KeyboardHAL* hal) : hal(hal)
	{
		
	}
	KeyEventQueue& getQueue()
	{
		return queue;
	}
	/// This function must be called in period of 10ms
	void onTimer()
	{
		for (uint8_t i = 0; i < numberOfKeys; i++)
		{
			Key currentkey = static_cast<Key>(i+1);
			KeyState halState = hal->keyState(currentkey);
			if (state[i].confirmedState != halState)
			{
				if (halState == KeyState::Pressed)
				{
					if (state[i].ticksPressed < minPressed)
					{
						++(state[i].ticksPressed);
					}
					else
					{
						state[i].confirmedState = KeyState::Pressed;
						queue.push_back(KeyEvent(currentkey, state[i].confirmedState));
						state[i].ticksReleased = 0;
					}
				}
				else
				{
					if (state[i].ticksReleased < minReleased)
					{
						++(state[i].ticksReleased);
					}
					else
					{
						state[i].confirmedState = KeyState::Released;
						queue.push_back(KeyEvent(currentkey, state[i].confirmedState));
						state[i].ticksPressed = 0;
					}
				}
			}
		}
	}

private:
	KeyboardHAL* hal;
	KeyEventQueue queue;
	ButtonState state[numberOfKeys];
};




#endif // KEYBOARD_H
