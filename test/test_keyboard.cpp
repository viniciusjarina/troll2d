/*
 *
 *  ______             ___    ___      
 * /\__  _\           /\_ \  /\_ \     
 * \/_/\ \/ _ __   ___\//\ \ \//\ \    
 *    \ \ \/\`'__\/ __`\\ \ \  \ \ \   
 *     \ \ \ \ \//\ \L\ \\_\ \_ \_\ \_ 
 *      \ \_\ \_\\ \____//\____\/\____\
 *       \/_/\/_/ \/___/ \/____/\/____/
 *
 * Copyright (c) 2008, JarinSoft
 * All rights reserved.
 *
 * Vinicius Jarina (viniciusjarina@gmail.com)
 *
 * Visit: http://troll2d.googlecode.com
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JarinSoft nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JarinSoft ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL JARINSOFT BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <troll.h> // include troll header
#include <stdio.h> // for sprintf

static const char * key_names[Troll::TOTAL_KEYS] =
{
	0,
	"BACKSPACE", // <-
	"TAB",       //		
	"RETURN",    // "Enter"
	"PAUSE", 
	"ESCAPE", 
	"SPACE",
	"EXCLAIM",// !
	"QUOTEDBL", // "
	"SHARP", // #
	"DOLLAR",// "$"
	"AMPERSAND",// &
	"QUOTE",// '
	"LEFTPAREN",// (
	"RIGHTPAREN",// )
	"ASTERISK",// *
	"PLUS",// +
	"COMMA",//,
	"MINUS",// -
	"PERIOD",// .
	"SLASH",// /
	"0",// 0
	"1",// 1
	"2",// 2
	"3",// 3
	"4",// 4
	"5",// 5
	"6",// 6
	"7",// 7
	"8",// 8
	"9",// 9
	"COLON",// :
	"SEMICOLON",// ;
	"LESS",// <
	"EQUALS",// =
	"GREATER",// >
	"QUESTION",// ?
	"AT",// @
	"A",// "A"
	"B",// "B"
	"C",// "C"
	"D",// "D"
	"E",// "E"
	"F",// "F"
	"G",// "G"
	"H",// "H"
	"I",// "I"
	"J",// "J"
	"K",// "K"
	"L",// "L"
	"M",// "M"
	"N",// "N"
	"O",// "O"
	"P",// "P"
	"Q",// "Q"
	"R",// "R"
	"S",// "S"
	"T",// "T"
	"U",// "U"
	"V",// "V"
	"W",// "W"
	"X",// "X"
	"Y",// "Y"
	"Z",// "Y"
	"LEFTBRACKET",// {
	"BACKSLASH",// 
	"RIGHTBRACKET",// }
	"CARET",// ^
	"UNDERSCORE",// "_"
	"BACKQUOTE",// `
	"DELETE",
	"NUMERIC_0",
	"NUMERIC_1",
	"NUMERIC_2",
	"NUMERIC_3",
	"NUMERIC_4",
	"NUMERIC_5",
	"NUMERIC_6",
	"NUMERIC_7",
	"NUMERIC_8",
	"NUMERIC_9",
	"NUMERIC_PERIOD",
	"NUMERIC_DIVIDE",
	"NUMERIC_MULTIPLY",
	"NUMERIC_MINUS",
	"NUMERIC_PLUS",
	"NUMERIC_ENTER",
	"NUMERIC_EQUAL",
	"UP",
	"DOWN",
	"RIGHT",
	"LEFT",
	"INSERT",
	"HOME",
	"END",
	"PAGEUP",
	"PAGEDOWN",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"NUMLOCK",
	"CAPSLOCK",
	"SCROLLOCK",
	"RIGHT_SHIFT",
	"LEFT_SHIFT",
	"RIGHT_CTRL",
	"LEFT_CTRL",
	"RIGHT_ALT",
	"LEFT_ALT",
};

#ifdef _WIN32
	extern "C" int __stdcall WinMain(void *hInst, void *hPrev, char *Cmd, int nShow)
#else
	int main(int argc, char *argv[])
#endif
{
	using namespace Troll;
	
	if(!System::Init())			// Inialize (input, sound, files, etc)
		return 0;

	if(!System::SetupScreen())	// Setup and create screen with defaul size
		return 0;

	System::SetScreenTitle("Keyboard Test");
	
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	Graphics g(buff); // Create Graphics object to draw primitives on the screen

	bool quit = false;

	Rect rc((buff.GetWidth() - 30)/2,(buff.GetHeight() - 30)/2,30,30);
	
	Color c1(167,193,254); // Normal color of rect
	Color c2(236,149,70);  // Hover color
	Color cBorder(11,67,159); // Border color

	char str[100];
	int i;

	int  pressed_count[TOTAL_KEYS];
	int  released_count[TOTAL_KEYS];
	bool key_down[TOTAL_KEYS];
	bool key_up[TOTAL_KEYS];

	for(i = FIRST_KEY; i < TOTAL_KEYS; i ++)
	{
		pressed_count[i] = 0;
		released_count[i] = 0;
		key_down[i] = false;
		key_up[i] = false;
	}

	Point ptOut;
	int max_y;

	max_y = buff.GetHeight();
		
	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

		MouseInput::Update();
		KeyInput::Update();
				

		quit = KeyInput::IsKeyDown(ESCAPE);

		if(KeyInput::IsKeyDown(DOWN))
			rc.y ++;
		if(KeyInput::IsKeyDown(UP))
			rc.y --;

		if(KeyInput::IsKeyDown(LEFT))
			rc.x --;
		if(KeyInput::IsKeyDown(RIGHT))
			rc.x ++;
				
		for(i = FIRST_KEY; i < TOTAL_KEYS; i++ )
		{
			if(KeyInput::IsKeyPressed((Key)i))
				pressed_count[i]++;
			if(KeyInput::IsKeyReleased((Key)i))
				released_count[i]++;
			
			key_down[i] = KeyInput::IsKeyDown((Key)i);
			key_up[i] = KeyInput::IsKeyUp((Key)i);
		}

		if(!Screen::SkipFrame()) // Frame can be rendered
		{
			buff.Clear(Color::WHITE);

			// RenderFrame(); Add draw code, to render current frame
			const Color & c =   c1; // Rect is hot or normal?
			
			g.DrawRectFill(rc,c);  // Draw rect
			g.DrawRect(rc,cBorder);// Draw rect border

			ptOut.y = 0;
			ptOut.x = 0;

			g.DrawText(ptOut,"(Press esc to exit)",Color::RED);
			ptOut.y += 10;
			g.DrawText(ptOut,"(p:pressed r:released",Color::BLUE);
			ptOut.y += 10;
			g.DrawText(ptOut," u:up d:down)",Color::BLUE);
			
			for(i = FIRST_KEY; i < TOTAL_KEYS; i++ )
			{
				ptOut.y += 10;
				if(ptOut.y + 10 > max_y)
				{
					ptOut.y = 0;
					ptOut.x += 210;
				}

				sprintf(str,"%s:p:%d r:%d u:%s d:%s",
					        key_names[i],
							pressed_count[i],
							released_count[i],
							key_up[i]   ? "1" : "0",
							key_down[i] ? "1" : "0"
							);
				g.DrawText(ptOut,str,Color::BLACK);
			}

			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup();
	return 0;
}