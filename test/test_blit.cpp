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

	System::SetScreenTitle("Blit Test");

	Image image;
	
	if(!image.LoadImage("troll.bmp"))
		return 0;
		
	const Surface & logo = image.GetSurface();

	Surface & screen = Screen::GetSurface(); // Get current screen Surface
	Graphics g(screen); // Create Graphics object to draw primitives on the screen

	Point logoPos((screen.GetWidth() - logo.GetWidth())/2, (screen.GetHeight() - logo.GetHeight())/2);

	bool quit = false;
	bool clip = false;
	bool cliping = false;

	Rect rcClip(screen.GetWidth() / 2, 0 ,screen.GetWidth()/2,screen.GetHeight()/2);// clip a quarter of screen
	
	
	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

		MouseInput::Update();
		KeyInput::Update();

		quit = KeyInput::IsKeyDown(ESCAPE);
		
		if(KeyInput::IsKeyReleased(SPACE))
		{
			clip = !clip;
		}
		

		// UpdateLogic(); // Add the logic o current frame

		if(!Screen::SkipFrame()) // Frame can be rendered
		{
			screen.Clear(Color::WHITE);

			// RenderFrame(); Add draw code, to render current frame
			g.DrawText(Point(10,10),"(Press esc to exit, space bar to toggle clipping)",Color::RED);
			g.DrawText(Point(10,30),"Simple Blit",Color::BLUE);

			if(clip)
			{
				if(!cliping)
				{
					screen.SetClip(rcClip);
					cliping = true;
				}
			}
			else
			{
				if(cliping)
				{
					screen.ResetClip();
					cliping = false;
				}
			}

			screen.Blit(logo,logoPos);
			

			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup();
	return 0;
}