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
#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "gui/MenuDefinitions.h"
#include "gui/View.h"

#include "devices/LcdHd44780.h"
#include "serialInterfaces/Usart.h"

#include "devices/keyboard/KeyEvent.h"


class MenuView : public View
{
public:
	/// @param gui - ptr to gui class
	/// @param items - ptr to table with menu items
	/// @param size - number of items in table of menu items
	MenuView(ViewStack* gui, MenuItem* items, int size) : View(gui), items(items), numberOfItems(size)
	{
		usart_printf("MenuView constructor\r\n");
	}
	~MenuView()
	{
		usart_printf("MenuView destructor\r\n");
	}
	void onButton(KeyEvent key) override
	{
		View::onButton(key); // escape handling
		usart_printf("on button\r\n");
		if (key.getKey() == Key::Down)
		{
			usart_printf("Key down\r\n");
			++selected;
			if(selected >= numberOfItems)
				selected = 0;
		}
		else if(key.getKey() == Key::Up)
		{
			usart_printf("Key up\r\n");
			if(selected > 0)
				--selected;
			else
				selected = numberOfItems - 1;
		}
		else if(key.getKey() == Key::Enter)
		{
			if(items[selected].onEnter != nullptr)
			{
				items[selected].onEnter(gui);
			}
		}
	}
	void render() override
	{
		if(selected < numberOfItems - 2) // lines of LCD
			offset = selected; //getViewOfset();
		else
			offset = numberOfItems - 2;
		usart_printf("Key down %u %u \r\n", selected, offset);
		// TODO: printf to gui.screenBuffer
		// TODO: numberOfScreenLines - number of lines that LCD can display
		LcdHd44780::cursor(0, 0);
		LcdHd44780::print(" ");
		LcdHd44780::print(getItem(offset)->getName());
		LcdHd44780::print(" ");
		
		LcdHd44780::cursor(1, 0);
		LcdHd44780::print(" ");
		LcdHd44780::print(getItem(offset + 1)->getName());
		LcdHd44780::print(" ");
		
		LcdHd44780::cursor(selected - offset, 0);
		LcdHd44780::print(">");
	}
	uint8_t getSelected();
	uint8_t getViewOfset()
	{
		return offset;
	}
	void setSelected(uint8_t selected);
	void setViewOfset(uint8_t offset);
	MenuItem* getItem(uint8_t index)
	{
		return &items[index];
	}

private:
	uint8_t selected = 0;
	uint8_t offset = 0;
	MenuItem* items;
	uint8_t numberOfItems;
};

#endif // MENUVIEW_H
