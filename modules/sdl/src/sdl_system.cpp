// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




#include <SDL.h>

#include "troll/sdl_surface.h"
#include "troll/sdl_system.h"

using namespace Troll;


SDLSystem::SDLSystem()
{

}

SDLSystem::~SDLSystem()
{

}

bool SDLSystem::Init()
{
	SDL_Init(0);
	return false;
}

bool SDLSystem::SetupScreen( int nWidth,int nHeight,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ )
{
	SDL_Init(SDL_INIT_VIDEO);

	return false;

}

void SDLSystem::Destroy()
{
	SDL_Quit();
}

Screen * SDLSystem::GetScreen() const
{
	return NULL;
}