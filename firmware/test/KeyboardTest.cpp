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
#include "lib/catch.hpp"
#include "devices/keyboard/Keyboard.h"
#include "devices/keyboard/KeyboardHAL.h"


// mock
class KeyboardHALTEST : public KeyboardHAL
{
public:
	KeyState leftBtnState{KeyState::Released};
	KeyState keyState(Key key) override
	{
		switch(key)
		{
			case Key::Left:
				return leftBtnState;
			case Key::Right:
				return KeyState::Released;
			case Key::Up:
				return KeyState::Released;
			case Key::Down:
				return KeyState::Released;
			case Key::Escape:
				return KeyState::Released;
			case Key::Enter:
				return KeyState::Released;
			default:
				return KeyState::Released;
		}
	}
};

TEST_CASE("Keyboard test")
{
	KeyboardHALTEST halTest;
	Keyboard keyboard(&halTest);
	SECTION("initial")
	{
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Released);
	}
	SECTION("pressed state after two timer periods, released after three")
	{
		halTest.leftBtnState = KeyState::Pressed;
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Released);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Released);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Pressed);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Pressed);
		halTest.leftBtnState = KeyState::Released;
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Pressed);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Pressed);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Pressed);
		keyboard.onTimer();
		REQUIRE(keyboard.getQueue().front().getState() == KeyState::Released);
	}
}
