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
#include <stdlib.h>

enum 
{
	TEST_PIXEL,
	TEST_LINE,
	TEST_VLINE,
	TEST_HLINE,
	TEST_CIRCLE,
	TEST_CIRCLE_FILL,
	TEST_RECT,
	TEST_RECT_FILL,
	TEST_ELLIPSE,
	TEST_ELLIPSE_FILL,
	TEST_ARC,
	TEST_ARC_FILL,
	TEST_TRIANGLE,
	TEST_TRIANGLE_FILL,
	TEST_POLYGON,
	TEST_POLYGON_FILL,
	TEST_TEXT
};

using namespace Troll;

int rand_ex(int min, int max)
{
	return ( rand() % (max - min) ) + min;
}

void DrawPrimitiveColor(Graphics & g,int state,const Rect & rect,const Color & c);

void DrawPrimitive(Graphics & g,int state,const Rect & rect)
{
	Color c(rand()%255,rand()%255,rand()%255);
	DrawPrimitiveColor(g,state,rect,c);
}

void DrawPrimitiveWithAlpha(Graphics & g,int state,const Rect & rect)
{
	Color c(rand()%255,rand()%255,rand()%255,rand_ex(10,192));
	DrawPrimitiveColor(g,state,rect,c);
}

void DrawPrimitiveColor(Graphics & g,int state,const Rect & rect,const Color & c)
{
	Point pt;
	pt.x = rand_ex(rect.GetLeft() , rect.GetRight());
	pt.y = rand_ex(rect.GetTop() , rect.GetBottom());

	Point pt2;
	pt2.x = rand_ex(rect.GetLeft() , rect.GetRight());
	pt2.y = rand_ex(rect.GetTop() , rect.GetBottom());

	Point pt3;
	pt3.x = rand_ex(rect.GetLeft() , rect.GetRight());
	pt3.y = rand_ex(rect.GetTop() , rect.GetBottom());

	short size_h = rand_ex(30,rect.GetWidth()/3);
	short size_w = rand_ex(30,rect.GetHeight()/3);

	short ang = 0;
	short ang2 = -90;

	switch(state)
	{
		case TEST_PIXEL: 
			g.DrawPixel(pt,c);
			break;

		case TEST_LINE: 
			g.DrawLine(pt,pt2,c);
			break;

		case TEST_VLINE: 
			g.DrawVLine(pt,size_h,c);
			break;
			
		case TEST_HLINE:
			g.DrawHLine(pt,size_w,c);
			break;

		case TEST_CIRCLE:
			g.DrawCircle(pt,size_w,c);
			break;

		case TEST_CIRCLE_FILL: 
			g.DrawCircleFill(pt,size_w,c);
			break;

		case TEST_RECT: 
			g.DrawRect(Rect(pt.x , pt.y,size_w,size_h),c);
			break;
			
		case TEST_RECT_FILL: 
			g.DrawRectFill(Rect(pt.x , pt.y,size_w,size_h),c);
			break;

		case TEST_ELLIPSE: 
			g.DrawEllipse(pt,size_w,size_h,c);
			break;
			
		case TEST_ELLIPSE_FILL: 
			g.DrawEllipseFill(pt,size_w,size_h,c);
			break;
		case TEST_ARC: 
			g.DrawArc(pt,size_h,ang,ang2,c);
			break;
		case TEST_ARC_FILL: 
			g.DrawArcFill(pt,size_h,ang,ang2,c);
			break;

		case TEST_TRIANGLE: 
			g.DrawTriangle(pt,pt2,pt3,c);
			break;			

		case TEST_TRIANGLE_FILL: 
			g.DrawTriangleFill(pt,pt2,pt3,c);
			break;
			
		case TEST_POLYGON: break;
		case TEST_POLYGON_FILL: break;
		case TEST_TEXT: break;
	}

}

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

	System::SetScreenTitle("Graphics Test");
	
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	Graphics g(buff); // Create Graphics object to draw primitives on the screen

	bool quit = false;
	int state = TEST_PIXEL;
	int i;
	
	Rect rect;
	Rect rectClip;

	rect.width  = buff.GetWidth()/2;
	rect.height = buff.GetHeight()/2;

	rectClip.width  = rect.width/2;
	rectClip.height = rect.height/2;

	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame();

		MouseInput::Update();
		KeyInput::Update();

		quit = KeyInput::IsKeyDown(ESCAPE);

		if(KeyInput::IsKeyReleased(RIGHT) && state < TEST_TEXT)
			state++;

		if(KeyInput::IsKeyReleased(LEFT) && state > TEST_PIXEL)
			state--;

		srand(5122);

		
		// UpdateLogic(); // Add the logic o current frame

		if(!Screen::SkipFrame()) // Frame can be rendered
		{
			buff.Clear(Color::WHITE);

			rect.x = 0;
			rect.y = 0;
	

			for(i = 0; i < 10; i ++ )
				DrawPrimitive(g,state,rect);

			rect.y += rect.height;

			for(i = 0; i < 10; i ++ )
				DrawPrimitiveWithAlpha(g,state,rect);

			rect.y = 0;
			rect.x += rect.width;

			rectClip.x = rect.x;
			rectClip.y = rect.y;		

			buff.SetClip(rectClip);

			for(i = 0; i < 10; i ++ )
				DrawPrimitive(g,state,rect);
			
			rect.y += rect.height;

			rectClip.x = rect.x;
			rectClip.y = rect.y;
					
			buff.SetClip(rectClip);
			
			for(i = 0; i < 10; i ++ )
				DrawPrimitiveWithAlpha(g,state,rect);
		
			buff.ResetClip();
			// RenderFrame(); Add draw code, to render current frame
			g.DrawText(Point(10,10),"(Press esc to exit)",Color::RED);
			

			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup();
	return 0;
}