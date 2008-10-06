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

#ifdef __APPLE__ // Under Mac OS X we will use SDLMain.m to wrap NSApplication and 
#include <SDL.h> // the entry point of a Cocoa application (this needed to be fixed)
#endif

#ifdef _WIN32
	extern "C" int __stdcall WinMain(void *hInst, void *hPrev, char *Cmd, int nShow)
#else
	extern "C" int main(int argc, char *argv[])
#endif
{
	using namespace Troll;      // set the namespace to Troll
	
	if(!System::Init())			// Initialize (input, sound, files, etc)
		return 0;

	if(!System::SetupScreen())	// Setup and create screen with default size
		return 0;

	System::SetScreenTitle("Mouse Test"); // Set the t
		
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	Graphics g(buff); // Graphics object to draw primitives
	
	bool quit = false;
	bool button_pressed  = false; // Button of mouse have just pressed?  (ButtonDown)
	bool button_released = false; // Button of mouse have just released? (ButtonUp)
	bool button_down = false;     // Is Button of mouse down?
	bool button_up = false;       // Is Button of mouse up?

	int pressed_count = 0;
	int released_count = 0;

	Point ptDelta; // delta x,y of mouse position
	Point pt;      // current mouse position

	Rect rc((buff.GetWidth() - 30)/2,(buff.GetHeight() - 30)/2,30,30);

	Color c1(167,193,254); // Normal color of rect
	Color c2(236,149,70);  // Hover color
	Color c3(236,149,70,128); // Dragging color
	Color cBorder(11,67,159); // Border color
	

	bool show_cursor = true; // Flag to show or hide cursor
	bool dragging  = false;  // Flag to indicate rect dragging
	bool hover     = false;  // Flag to control mouse is over rect
	
	char str[100]; // String to output information (use std::string?)

	while(!quit) // was ESC key pressed?
	{
		Screen::StartFrame(); // Start current frame

		MouseInput::Update(); // Update input
		KeyInput::Update();   // Update input

		quit = KeyInput::IsKeyDown(Key::ESCAPE);
				
		if(KeyInput::IsKeyReleased(Key::SPACE))
		{
			show_cursor = !show_cursor; // toggle cursor display
			Screen::ShowCursor(show_cursor);
		}

		ptDelta = MouseInput::GetRelativePosition();
		pt = MouseInput::GetPosition();

		button_pressed  = MouseInput::IsButtonPressed(0); // Button of mouse have just pressed
		button_released = MouseInput::IsButtonReleased(0);// Button of mouse have just released
		button_down     = MouseInput::IsButtonDown(0);    // Is Button of mouse down
		button_up       = MouseInput::IsButtonUp(0);      // Is Button of mouse up

		hover = rc.Contains(pt); // if point is inside rect

		if(button_pressed)
		{
			pressed_count++;
			if(hover)
			{
				dragging = true;
			}
		}

		if(button_released)
		{
			if(dragging)
			{
				dragging = false;
			}

			released_count++;
		}

		if(dragging) // if draging rect
		{
			rc.Offset(ptDelta); // move the rect
		}
		
		if(!Screen::SkipFrame())
		{
			buff.Clear(Color::WHITE);          // Clean the screen with withe color
			const Color & c =  dragging ? c3 : // Rect is being dragged?
							  (hover    ? c2 : c1); // Rect is hot or normal?

			g.DrawRectFill(rc,c);  // Draw rect
			g.DrawRect(rc,cBorder);// Draw rect border

			// Output information


			g.DrawText(Point(10,10),"(Press space bar to show/hide cursor, Esc to exit)",Color::RED);
			g.DrawText(Point(10,20),"Drag rect over screen",Color::BLUE);

			sprintf(str," Position: %d, %d",pt.x, pt.y);
			g.DrawText(Point(10,40),str,Color::BLACK);

			sprintf(str," Delta:    %d, %d",ptDelta.x, ptDelta.y);
			g.DrawText(Point(10,50),str,Color::BLACK);

			sprintf(str," Button(0) Pressed:  %s (count %d)",button_pressed ? "true" : "false",pressed_count);
			g.DrawText(Point(10,60),str,Color::BLACK);

			sprintf(str," Button(0) Released: %s (count %d)",button_released ? "true" : "false",released_count);
			g.DrawText(Point(10,70),str,Color::BLACK);

			sprintf(str," Button(0) Down:     %s",button_down ? "true" : "false");
			g.DrawText(Point(10,80),str,Color::BLACK);

			sprintf(str," Button(0) Up:       %s",button_up ? "true" : "false");
			g.DrawText(Point(10,90),str,Color::BLACK);			
			
						
			Screen::Flip();		// Flip screen
		}
	}
	
	System::Cleanup(); // cleanup system
	return 0;
}