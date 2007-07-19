// SDLScreen.cpp: implementation of the SDLScreen class.
//
//////////////////////////////////////////////////////////////////////
#include <SDL.h>

#include "troll/sdl_screen.h"
#include "troll/sdl_surface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

SDLScreen::SDLScreen(SDL_Surface * screen)
{
	m_surface = new SDLSurface(screen);
}

SDLScreen::~SDLScreen()
{
	delete m_surface;
}

Surface * SDLScreen::GetSurface() const
{
	return m_surface;
}


void SDLScreen::Flip()
{
	SDL_Flip(m_surface->m_surface);
}