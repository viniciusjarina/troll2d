// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




#include <SDL.h>

#include "troll/sdl_screen.h"
#include "troll/sdl_system.h"

using namespace Troll;

SDLSystem::SDLSystem()
{
	SDL_Init(0);
}

SDLSystem::~SDLSystem()
{
	if(m_screen != NULL)
		delete m_screen;

	SDL_Quit();
}


bool SDLSystem::SetupScreen( int nWidth,int nHeight,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ )
{
	if(nHeight == -1 && nWidth == -1)
	{
#ifdef _WIN32_WCE
		nWidth  = 240;
		nHeight = 320;
		fFullScreen = true;
#else
		nWidth  = 640;
		nHeight = 480;
#endif
	}

	m_screen = SDLScreenHelper::SetupScreen(nWidth,nHeight,depth,fFullScreen);
	if(!m_screen)
		return false;
	
	return true;
}

void SDLSystem::Sleep( int mili )
{
	SDL_Delay(mili);
}

int SDLSystem::GetScreenBPP()
{
	return SDLScreenHelper::GetScreenBPP();
}
