// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////
#include <SDL.h>

#include "troll/surface.h"
#include "troll/sdl_surface.h"
#include "troll/basic_geo.h"
#include "troll/sdl_system.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

SDLSurface::SDLSurface()
{
	m_surface = NULL;
}

SDLSurface::~SDLSurface()
{
	if(m_surface != NULL)
		SDL_FreeSurface(m_surface);
}

bool SDLSurface::Create( int width,int height,ColorDepth depth /*= depthAuto*/)
{
	Uint32 rmask, gmask, bmask, amask;
	int bpp;
	
    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
	on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
	if(depth == depthAuto)
		bpp = SDLSystem::GetSystemDepth();
	else
		bpp = depth*8;
		
    m_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, bpp,rmask, gmask, bmask, amask);
    if(m_surface == NULL)
		return false;

	return true;
}

int SDLSurface::GetHeight() const
{
	return m_surface->h;
}

int SDLSurface::GetWidth() const
{
	return m_surface->w;
}

void SDLSurface::SetClip(const Rect & rect)
{
	SDL_Rect r;
	r.x = rect.x;
	r.y = rect.y;
	r.h = rect.height;
	r.w = rect.width;
	
	SDL_SetClipRect(m_surface,&r);
}

Rect SDLSurface::GetClip() const
{
	Rect rect;
	SDL_Rect r;
	SDL_GetClipRect(m_surface,&r);

	rect.x = r.x;
	rect.y = r.y;
	rect.height = r.h;
	rect.width = r.w;

	return rect;
}

void SDLSurface::ResetClip()
{
	SDL_SetClipRect(m_surface,NULL);
}

void SDLSurface::Clear(const Color & color /*= Color::INVISIBLE*/)
{
	SDL_Rect rect;
	Uint32 sdl_color;
	rect.x = 0;
	rect.y = 0;
	rect.w = m_surface->w;
	rect.h = m_surface->h;
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());// alpha isn´t used
	SDL_FillRect(m_surface,&rect,sdl_color);
}

void SDLSurface::Blit(const Surface & src,const Point& ptDest /*Point(0,0)*/,const Rect& rSource /*Rect(0,0,-1,-1)*/)
{
	SDL_Rect rect1;
	SDL_Rect rect2;

	int width;
	int height;

	SDL_Surface * source = ((SDLSurface *)&src)->m_surface;
	SDL_Surface * dest = m_surface;

	if(rSource.width < 0)
		width  = source->w;
	if(rSource.height < 0)
		height = source->h;

	rect1.x = rSource.x;
	rect1.y = rSource.y;
	rect1.h = height;
	rect1.w = width;

	rect2.x = ptDest.x;
	rect2.y = ptDest.y;
	rect2.h = height;
	rect2.w = width;
	
	SDL_BlitSurface(source,&rect1,dest,&rect2);
}


SDLSurface::SDLSurface( SDL_Surface * screen ):
m_surface(screen)
{
	
}