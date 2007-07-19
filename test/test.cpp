
#ifdef WIN32
	#define TROLL_USE_ALLEGRO 1
#else
	#define TROLL_USE_ALLEGRO 0
#endif

#include <troll/system.h>
#include <troll/screen.h>
#include <troll/surface.h>

/***************** TODO: Implementar algum jeito de abstrair a funcao WinMain *********/

/****************************/

/**** TODO: Colocar este include na classe de Factory da Allegro */
#include <troll/allegro_system.h>
#include <troll/allegro_keyinput.h>
#include <troll/allegro_surface.h>
/*****************************************/

/****************************/

/**** TODO: Colocar este include na classe de Factory da SDL */
#include <troll/sdl_system.h>
#include <troll/sdl_keyinput.h>
#include <troll/sdl_surface.h>

/*****************************************/
#if TROLL_USE_ALLEGRO
	#include <allegro.h>
#else
	#include <SDL.h> // incluido para usarmos a WinMain da SDLmain.lib =)
#endif

using namespace Troll;

int main()
{
	Color c(0,0,0);
	System * pSystem;
	Screen * pScreen;
	Surface * pBuff;
	KeyInput * key;
	Surface * pTest;
/*****************/
	// TODO: Código que deve estar dentro da Factory de Systems
#if TROLL_USE_ALLEGRO
	pSystem = new AllegroSystem;
	key		= new AllegroKeyInput;
	pTest	= new AllegroSurface;
#else
	pSystem = new SDLSystem;
	key		= new SDLKeyInput;
	pTest	= new SDLSurface;
#endif

/*****************/

	pSystem->SetupScreen(640,480);
	
	pScreen = pSystem->GetScreen();
	pBuff	= pScreen->GetSurface();

	pTest->Create(100, 100);
	int x = 0;
	int y = 0;

	int xInc = 1;
	int yInc = 1;

	pBuff->Clear(c);
	
	while(!key->IsKeyDown(Key::ESCAPE))
	{
		Color c2(255,0,0);
		//pBuff->Clear(c);

		c2.IncraseLuminance(((255*y)/pBuff->GetWidth()) - 127);
		c2.RotateHue(((255*x)/pBuff->GetHeight()));

		if(x > pBuff->GetWidth() - pTest->GetWidth() )
			xInc = -3;
		else if(x <= 0)
			xInc =  3;
		
		
		if(y > pBuff->GetHeight() - pTest->GetHeight() )
			yInc = -3;
		else if(y <= 0)
			yInc =  3;

		x += xInc;
		y += yInc;

		
		pTest->Clear(c2);
		pBuff->Blit(*pTest,Point(x,y));


		
		pScreen->Flip();
		pSystem->Sleep(20);
	}

	
	
	delete pTest;
	delete pSystem;
	delete key;
	
	return 0;
}
#if TROLL_USE_ALLEGRO
END_OF_MAIN()
#endif