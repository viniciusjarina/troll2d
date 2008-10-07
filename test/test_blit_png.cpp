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

#ifdef __APPLE__ // Under Mac OS X we will use SDLMain.m to wrap NSApplication and 
#include <SDL.h> // the entry point of a Cocoa application (this needed to be fixed)
#endif

#include <stdio.h>

#ifdef _WIN32
	extern "C" int __stdcall WinMain(void *hInst, void *hPrev, char *Cmd, int nShow)
#else
	int main(int argc, char *argv[])
#endif
{
	using namespace Troll;

	if(!System::Init())			// Initialize (input, sound, files, etc)
		return 0;

	if(!System::SetupScreen())	// Setup and create screen with default size
		return 0;

	System::SetScreenTitle("Blit PNG Test");

	Image image;

	if(!image.LoadImage("images/troll.png"))
		return 0;

	const Surface & logo = image.GetSurface();

	Surface & screen = Screen::GetSurface(); // Get current screen Surface
	Graphics g(screen); // Create Graphics object to draw primitives on the screen

	Point middlePos((screen.GetWidth() - logo.GetWidth())/2, (screen.GetHeight() - logo.GetHeight())/2);
	char buff[250];

	bool quit = false;
	bool clip = false;
	bool cliping = false;
	int  state = 0;
	short angle = 0;
	Size szLogo(200,200);

	Rect rcClip(screen.GetWidth() / 2, 0 ,screen.GetWidth()/2,screen.GetHeight()/2);// clip a quarter of screen

	DrawFlags df(DrawFlags::none);
	AlphaComponent alpha = 255;
	int i = 0;
	int s = 0 ,m = 0,h = 0;
	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

		i++;
		if(i == 60)
		{
			s++;
			i = 0;
		}
		if(s == 60)
		{
			m++;
			s = 0;
		}
		if(m == 60)
		{
			h++;
			m = 0;
		}

		sprintf(buff,"%02d:%02d:%02d",h,m,s);

		MouseInput::Update();
		KeyInput::Update();

		quit = KeyInput::IsKeyDown(Key::ESCAPE);

		if(KeyInput::IsKeyReleased(Key::SPACE))
		{
			clip = !clip;
		}

		if(KeyInput::IsKeyReleased(Key::H))
		{
			df.ToggleFlag(DrawFlags::horizontalFlip);
		}
		if(KeyInput::IsKeyReleased(Key::V))
		{
			df.ToggleFlag(DrawFlags::verticalFlip);
		}
		if(KeyInput::IsKeyDown(Key::R))
		{
			if(KeyInput::IsKeyDown(Key::RIGHT_SHIFT) || KeyInput::IsKeyDown(Key::LEFT_SHIFT))
				angle -= 5;
			else
				angle += 5;
		}

		if(KeyInput::IsKeyDown(Key::X))
		{
			if(KeyInput::IsKeyDown(Key::RIGHT_SHIFT) || KeyInput::IsKeyDown(Key::LEFT_SHIFT))
				szLogo.x -= 5;
			else
				szLogo.x += 5;
		}

		if(KeyInput::IsKeyDown(Key::Y))
		{
			if(KeyInput::IsKeyDown(Key::RIGHT_SHIFT) || KeyInput::IsKeyDown(Key::LEFT_SHIFT))
				szLogo.y -= 5;
			else
				szLogo.y += 5;
		}

		if(KeyInput::IsKeyReleased(Key::A))
		{
			df.ToggleFlag(DrawFlags::noAntiAlias);
		}

		if(KeyInput::IsKeyDown(Key::NUMERIC_MINUS))
		{
			if(alpha > 0)
				alpha -= 2;
		}

		if(KeyInput::IsKeyDown(Key::NUMERIC_PLUS))
		{
			if(alpha < 255)
				alpha += 2;
		}

		if(KeyInput::IsKeyReleased(Key::LEFT) && state > 0)
		{
			state--;
		}

		if(KeyInput::IsKeyReleased(Key::RIGHT) && state < 5)
		{
			state++;
		}

		if(!Screen::SkipFrame()) // Frame can be rendered
		{
			screen.Clear(Color::WHITE);

			g.DrawText(Point(10,10),"(Press esc to exit, space bar to toggle clipping)",Color::RED);
			g.DrawText(Point(10,30),"Simple Blit",Color::BLUE);
			g.DrawText(Point(10,40),buff,Color::DARKGREEN);

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

			Rect rcPos(middlePos,Size(50,50));

			g.DrawRectFill(rcPos, Color::RED);
			rcPos.Offset(30,30);
			g.DrawRectFill(rcPos, Color::GREEN);
			rcPos.Offset(30,30);
			g.DrawRectFill(rcPos, Color::BLUE);

			Rect rc(MouseInput::GetPosition(),szLogo);

			switch(state)
			{
			case 0:
				screen.DrawFast(logo, rc.GetPosition());
				break;

			case 1:
				screen.Draw(logo,rc.GetPosition(), df, alpha);
				break;

			case 2:
				screen.Draw(logo,rc.GetPosition(), Rect(10,20,100,90), df, alpha);
				break;

			case 3:
				screen.DrawStretch(logo, rc, df, alpha);
				break;

			case 4:
				screen.DrawStretch(logo, rc, Rect(10,20,100,90), df, alpha);
				break;

			case 5:
				screen.DrawRotate(logo, rc.GetPosition(), angle, df, alpha);
				break;

			}
			Screen::Flip();		// Flip screen
		}
	}	
	System::Cleanup();
	return 0;
}