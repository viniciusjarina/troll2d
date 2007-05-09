// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////
#include <SDL.h>

#include "troll/surface.h"
#include "troll/sdl_surface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

SDLSurface::SDLSurface()
{

}

SDLSurface::~SDLSurface()
{

}

int SDLSurface::GetHeight() const
{
	return 0;
}

int SDLSurface::GetWidth() const
{
	return 0;
}

void SDLSurface::SetClip(const Rect & rect)
{

}

Rect SDLSurface::GetClip() const
{
	Rect r;
	return r;
}

void SDLSurface::ResetClip()
{

}

void SDLSurface::Clear(const Color & color /*= Color::BLACK*/)
{

}

void SDLSurface::Blit(const Surface & src)
{

}