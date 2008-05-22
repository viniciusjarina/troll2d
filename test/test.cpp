
#include "troll.h"

#include <SDL.h> // incluido para usarmos a WinMain da SDLmain.lib =)

using namespace Troll;

extern "C" int main(int argc,char * argv[])
{
	System::Init();			// Inialize (input, sound, files, etc)
	System::SetupScreen();	// Setup and create screen with defaul size
	
	Surface & buff	= Screen::GetSurface(); // Get current screen Surface
	
	Image image;

	if(!image.LoadImage("troll.bmp")) // Try to load image
		return 1; // Fail to load image
	
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
	
	while(!KeyInput::IsKeyDown(Key::ESCAPE)) // was ESC key pressed?
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
		// TODO: FPS system
	}

	System::Cleanup();
	return 0;
}
