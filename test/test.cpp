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

	System::SetScreenTitle("Test Mouse");
	
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	

	int x = 0;
	int y = 0;

	const int total_w = buff.GetWidth();
	const int total_h = buff.GetHeight();

	bool quit = false;
	bool button_pressed  = false;
	bool button_released = false;

	Graphics g(buff);

	Point pt;
	Rect rc(0,0,30,30);

	Color c1(167,193,254);
	Color c2(236,149,70);

	Color cSel1(192,211,252);
	Color cSel2(243,193,148);

	Color cBorder(11,67,159);

	static int grid[10][10];

	bool bShowCursor = true;

	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

		MouseInput::Update();
		KeyInput::Update();

		quit = KeyInput::IsKeyDown(Key::ESCAPE);
		quit = quit || KeyInput::IsKeyDown(Key::RIGHT);
		quit = quit || KeyInput::IsKeyDown(Key::RETURN);
		
		if(KeyInput::IsKeyReleased(Key::SPACE))
		{
			bShowCursor = !bShowCursor;
			Screen::ShowCursor(bShowCursor);
		}

		
			

		MouseInput::GetRelativePosition(pt);

		if(pt.x != 0 || pt.y != 0)
		{
			MouseInput::GetPosition(pt);
			x = pt.x;
			y = pt.y;

			x /= 30;
			y /= 30;
		}

		button_pressed  = MouseInput::IsButtonPressed(0);
		button_released = MouseInput::IsButtonReleased(0);

		if(button_pressed && x < 10 && y < 10)
		{
			Screen::ShowCursor(false);
			grid[y][x] = !grid[y][x];
		}

		if(button_released)
		{
			Screen::ShowCursor(true);
		}
		
		if(!Screen::SkipFrame())
		{
			buff.Clear(Color::WHITE);
			g.DrawLine(Point(0,0),Point(100,100),Color::RED);

			rc.x = 0;
			rc.y = 0;

			for(int i = 0; i < 10; i ++)
			{
				for(int j = 0; j < 10; j ++)
				{
					const Color & c	   = grid[i][j] ? c2 : c1;
					const Color & cSel = grid[i][j] ? cSel2 : cSel1;
					const Color & color = (i == y && j == x) ? cSel : c;
					g.DrawRectFill(rc,color);
					g.DrawRect(rc,cBorder);
					rc.x += 30;
				}

				rc.x = 0;
                rc.y += 30;
			}
			
			g.DrawTriangleFill(Point(0,0),Point(100,100),Point(10,100),Color(255,0,0,128));
			g.DrawEllipse(Point(100,100),50,80,Color(0,0,0,255));
			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup();
	return 0;
}