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

#include "troll.h" // include troll header

#include <SDL.h>   // **provisorie** : This is hear because I´m current using the "entry point" method of SDL
                   // TODO: Write Troll method of entry point like Application class or just using defines like SDL and allegro


extern "C" int main(int argc,char * argv[])
{
	using namespace Troll;
	
	System::Init();			// Inialize (input, sound, files, etc)

	System::SetupScreen();	// Setup and create screen with defaul size
	
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	
	Image image;	

	if(!image.LoadImage("troll.bmp")) // Try to load image
	{
		return 1; // Fail to load image
	}
	
	const Surface & test = image.GetSurface();
	
	int x = 0;
	int y = 0;

	int xInc = 1;
	int yInc = 1;

	const int h = test.GetHeight();
	const int w = test.GetWidth();
	const int total_w = buff.GetWidth();
	const int total_h = buff.GetHeight();

	Graphics g(buff);

	Color c(0,0,0);

	buff.Clear(c);
	
	while(!KeyInput::IsKeyDown(Key::RIGHT)) // was ESC key pressed?
	{
		Color c2(190,0,0);
		
		c2.RotateHue( ((255 * x)/total_w) );

		// Bounce logic
		if( x > ( total_w - w ) )
			xInc = -5;
		else if( x <= 0 )
			xInc =  5;
		
		if( y > (total_h - h) )
			yInc = -5;
		else if(y <= 0)
			yInc =  5;

		x += xInc;
		y += yInc;
		
		// draw logo with alpha
		buff.DrawAlpha(test, Point(x,y), (( y * 255)/total_h)); 
		
		// Draw box	
		g.DrawLine(Point(x    , y + h), Point(x    , y    ),c2);
		g.DrawLine(Point(x    , y    ), Point(x + w, y    ),c2);
		g.DrawLine(Point(x    , y + h), Point(x + w, y + h),c2);
		g.DrawLine(Point(x + w, y + h), Point(x + w, y    ),c2);
		
		Screen::Flip();		// Flip screen
		System::Sleep(30);  // Wait 
		// TODO: FPS system (sleep should be inside Flip() )
	}

	System::Cleanup();
	return 0;
}
