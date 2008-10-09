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
#include <string.h>

using namespace Troll;

int DrawInfoBox(Graphics & g,DrawFlags flags,int state,AlphaComponent alpha);

#ifdef _WIN32
	extern "C" int __stdcall WinMain(void *hInst, void *hPrev, char *Cmd, int nShow)
#else
	int main(int argc, char *argv[])
#endif
{

	if(!System::Init())			// Inialize (input, sound, files, etc)
		return 0;

	if(!System::SetupScreen())	// Setup and create screen with defaul size
		return 0;

	System::SetScreenTitle("Blit/Flip/Rotate/Alpha PNG Test");

	Image image;
	
	if(!image.LoadImage("images/troll.png"))
		return 0;
		
	const Surface & logo = image.GetSurface();

	Surface & screen = Screen::GetSurface(); // Get current screen Surface
	Graphics g(screen); // Create Graphics object to draw primitives on the screen

	Point middlePos((screen.GetWidth() - logo.GetWidth())/2, (screen.GetHeight() - logo.GetHeight())/2);

	bool quit = false;
	bool clip = false;
	bool cliping = false;
	int state = 0;
	short angle = 0;
	Size szLogo(200,200);

	Rect rcClip(screen.GetWidth() / 2, 0 ,screen.GetWidth()/2,screen.GetHeight()/2);// clip a quarter of screen

	DrawFlags df(DrawFlags::none);
	AlphaComponent alpha = 255;

	
		
	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

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
			if(alpha > 2)
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

		// UpdateLogic(); // Add the logic o current frame

		

		if(!Screen::SkipFrame()) // Frame can be rendered
		{
			Rect rc(MouseInput::GetPosition(),szLogo);
			
			//screen.DrawStretch(logo, rc, Rect(50,50,50,50), df, alpha);
			screen.Clear(Color::WHITE);

			// RenderFrame(); Add draw code, to render current frame
			g.DrawText(Point(10,5),"(Press esc to exit, space bar to toggle clipping)",Color::RED);
			g.DrawText(Point(10,15),"Right/Left:Change Blit V/H:flip R:Rotate +/-: Change alpha X/Y:Size ",Color::DARKRED);
						

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
									

			switch(state)
			{
			case 0:
				screen.DrawFast(logo, rc.GetPosition());
				break;

			case 1:
				screen.Draw(logo,rc.GetPosition(), df, alpha);
				break;

			case 2:
				screen.Draw(logo,rc.GetPosition(), Rect(0,0,64,128), df, alpha);
				break;

			case 3:
				screen.DrawStretch(logo, rc, df, alpha);
				break;

			case 4:
				screen.DrawStretch(logo, rc, Rect(0,0,64,128), df, alpha);				
				break;

			case 5:
				screen.DrawRotate(logo, rc.GetPosition(), angle, df, alpha);
				break;

			}
			DrawInfoBox(g,df,state,alpha);

			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup();
	return 0;
}

int DrawInfoBox(Graphics & g,DrawFlags flags,int state,AlphaComponent alpha)
{
	Rect rc(10,30,550,30);

	static const char * szFuncs [] = 
	{
		"DrawFast",
		"Draw",
		"Draw + Clip Source",
		"DrawStretch",
		"DrawStretch + Clip Source",
		"DrawRotate",
	};

	g.DrawRoundRectFill(rc, 5,Color(45,10,200,200));
	g.DrawRoundRect(rc, 5,Color(45,10,200));

	g.DrawText(Point(15,40),szFuncs[state],Color(255,255,0,200));

	long lastpos = strlen(szFuncs[state])*8;

	if(flags.HasFlag(DrawFlags::horizontalFlip) && state > 0)
	{
		g.DrawText(Point(15 + lastpos,40)," + flipH",Color(255,255,0,200));
		lastpos += 8*8;
	}

	if(flags.HasFlag(DrawFlags::verticalFlip) && state > 0)
	{
		g.DrawText(Point(15 + lastpos,40)," + flipV",Color(255,255,0,200));
		lastpos += 8*8;
	}

	if(flags.HasFlag(DrawFlags::noAntiAlias) && state > 2)
	{
		g.DrawText(Point(15 + lastpos,40)," + noAntiAlias",Color(255,255,0,200));
		lastpos += 14*8;
	}

	if(alpha < 255 && state > 0)
	{
		char szAlpha[20];
		sprintf(szAlpha," (alpha %d)",alpha);

		g.DrawText(Point(15 + lastpos,40),szAlpha,Color(150,255,0,210));
		lastpos += strlen(szAlpha)*8;
	}

	return 0;
}