
#include "troll.h"

#include <SDL.h> // incluido para usarmos a WinMain da SDLmain.lib =)

using namespace Troll;

extern "C" int main(int argc,char * argv[])
{
	Color c(0,0,0);
	
	System::Init();

	System::SetupScreen();
	
	Surface & buff	= Screen::GetSurface();
	
	Surface test(100,100);
	
	int x = 0;
	int y = 0;

	int xInc = 1;
	int yInc = 1;

	buff.Clear(c);
	
	while(!KeyInput::IsKeyDown(Key::ESCAPE))
	{
		Color c2(255,0,0);

		//buff.Clear(c);

		c2.IncraseLuminance(((255*y)/buff.GetWidth()) - 127);
		c2.RotateHue(((255*x)/buff.GetHeight()));

		if(x > buff.GetWidth() - test.GetWidth() )
			xInc = -3;
		else if(x <= 0)
			xInc =  3;
		
		if(y > buff.GetHeight() - test.GetHeight() )
			yInc = -3;
		else if(y <= 0)
			yInc =  3;

		x += xInc;
		y += yInc;
		
		test.Clear(c2);
		buff.Blit(test,Point(x,y));
		
		Screen::Flip();
		System::Sleep(20);
	}

	System::Cleanup();
	return 0;
}
