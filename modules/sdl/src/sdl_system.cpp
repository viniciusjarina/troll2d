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

SDLSystem * SDLSystem::m_system = NULL;

SDLSystem::SDLSystem()
{
	m_system   = this;
	screen_bpp = 0;
	SDL_Init(0);
}

SDLSystem::~SDLSystem()
{
	SDL_Quit();
}


bool SDLSystem::SetupScreen( int nWidth,int nHeight,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ )
{
	const SDL_VideoInfo *info;
	SDL_Surface *screen;
	Uint8  video_bpp;
	Uint32 flags = SDL_HWSURFACE|SDL_DOUBLEBUF;

	SDL_Init(SDL_INIT_VIDEO);

	if(depth == depthAuto)
	{
		info = SDL_GetVideoInfo();
		if(info && info->vfmt)
			video_bpp = info->vfmt->BitsPerPixel;
		else
			video_bpp = 16;
	}
	else
	{
		video_bpp =	depth * 8;
	}

	if(fFullScreen)
		flags |= SDL_FULLSCREEN;

	screen = SDL_SetVideoMode(nWidth,nHeight,video_bpp,flags);
	if(screen == NULL)
		return false;
	screen_bpp = video_bpp;
	m_screen = new SDLScreen(screen);
	return false;

}

Screen * SDLSystem::GetScreen() const
{
	return m_screen;
}

void SDLSystem::Sleep( int mili )
{
	SDL_Delay(mili);
}