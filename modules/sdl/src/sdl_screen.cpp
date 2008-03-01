// SDLScreen.cpp: implementation of the SDLScreen class.
//
//////////////////////////////////////////////////////////////////////
#include <SDL.h>

#include "troll/sdl_screen.h"
#include "troll/sdl_surface.h"
#include "troll/screen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

SDLScreen::SDLScreen(int w, int h,int bpp,bool fullscreen)
{
	m_screenHelper.CreateScreenSurface(w, h, bpp, fullscreen);
	Screen::SetSingleton(this);
}

SDLScreen::~SDLScreen()
{
}

Surface & SDLScreen::GetSurface() const
{
	return m_screenHelper.GetSurface();
}


void SDLScreen::Flip()
{
	m_screenHelper.FlipScreen();
}

/*******************************************************/

class SDLScreenSurfaceImpl: public SDLSurface
{
public:
	SDLScreenSurfaceImpl(SDL_Surface * surface):
	  SDLSurface(surface)
	  {
	  }
};

class SDLScreenSurface: public Surface
{
public:
	SDLScreenSurface(SDLScreenSurfaceImpl * impl):
	  Surface(impl)
	  {
	  }
};

int SDLScreenHelper::m_screen_bpp = 0;

SDLScreenHelper::SDLScreenHelper()
{
	
}

SDLScreenHelper::~SDLScreenHelper()
{
	if(m_screenSurface)
		delete m_screenSurface;
}

void SDLScreenHelper::FlipScreen()
{
	SDL_Flip(m_nativeSurface);
}

bool SDLScreenHelper::CreateScreenSurface(int w, int h,int bpp,bool fullscreen)
{
	Uint32 flags = SDL_HWSURFACE|SDL_DOUBLEBUF;
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	
	SDL_Surface * buffer = SDL_SetVideoMode(w, h, bpp ,flags);

	if(!buffer)
		return false;
	
	SDLScreenSurfaceImpl * pSDLSurfaceImpl = new SDLScreenSurfaceImpl(buffer);
	Surface * pSurface = new SDLScreenSurface(pSDLSurfaceImpl);
	
	m_nativeSurface = buffer;
	m_screenSurface = pSurface;
	m_screen_bpp = bpp;

	return true;
}

SDLScreen * SDLScreenHelper::SetupScreen( int w, int h, int bpp, bool fullscreen )
{
	const SDL_VideoInfo *info;
	
	Uint8  video_bpp;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	if(bpp == depthAuto)
	{
		info = SDL_GetVideoInfo();
		if(info && info->vfmt)
			video_bpp = info->vfmt->BitsPerPixel;
		else
			video_bpp = 16;
	}
	else
	{
		video_bpp =	bpp * 8;
	}

	SDLScreen * screen = new SDLScreen(w, h, video_bpp, fullscreen);
	
	return screen;
}