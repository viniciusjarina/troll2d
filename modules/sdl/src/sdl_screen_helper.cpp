#include <SDL.h>

#include "troll/surface.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_screen.h"

#include "troll/sdl_screen_helper.h"

using Troll::Surface;

using Troll::SDLSurface;
using Troll::SDLScreen;
using Troll::SDLScreenHelper;


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


void SDLScreenHelper::StartFrame()
{
	start_frame_tick = SDL_GetTicks();

	if ( (end_frame_tick - start_frame_tick) < m_nFrameTicks )
	{
		SDL_Delay(m_nFrameTicks - (end_frame_tick - start_frame_tick));
	}

	real_start_frame_tick = SDL_GetTicks();
}

void SDLScreenHelper::FlipScreen()
{
	SDL_Flip(m_nativeSurface);

	end_frame_tick = SDL_GetTicks();;

	total_frame_time = end_frame_tick - real_start_frame_tick + 1;
}

bool SDLScreenHelper::SkipFrame()
{
	Uint32 current_tick = SDL_GetTicks();
	Uint32 last_frame_tick;

	last_frame_tick = (current_tick - start_frame_tick);
	if(last_frame_tick > m_nFrameTicks)
	{
		end_frame_tick = current_tick;
		return false;
	}
	return false;
}


bool SDLScreenHelper::CreateScreenSurface(int w, int h,int bpp,bool fullscreen,int nFPS)
{
#if	defined(__SYMBIAN32__)
	Uint32 flags = SDL_SWSURFACE | SDL_ANYFORMAT ; // Symbian does not support SDL_HWSURFACE
#else
	Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF ;
#endif
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	
	SDL_Surface * buffer = SDL_SetVideoMode(w, h, bpp ,flags);

	if(!buffer)
		return false;
	
	SDLScreenSurfaceImpl * pSDLSurfaceImpl = new SDLScreenSurfaceImpl(buffer);
	Surface * pSurface = new SDLScreenSurface(pSDLSurfaceImpl);
	
	if(nFPS == 0)
		nFPS = 1;

	m_nFPS = nFPS;
	m_nFrameTicks = 1000/nFPS;
	
	m_nativeSurface = buffer;
	m_screenSurface = pSurface;
	m_screen_bpp = bpp;
	return true;
}


SDLScreen * SDLScreenHelper::SetupScreen( int w, int h, int bpp, bool fullscreen, int nFPS)
{
	const SDL_VideoInfo *info;
	Uint8  video_bpp;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return NULL;

	info = SDL_GetVideoInfo();

	if(h == -1 && w == -1)
	{
#if defined(_WIN32_WCE) || defined(__SYMBIAN32__)
		SDL_Rect **modes;

		fullscreen = true;
		modes = SDL_ListModes(NULL, SDL_FULLSCREEN);
		
		if (modes == NULL || modes == (SDL_Rect**) -1)
		{
				w  = 240; // Probably 240x320 :P
				h  = 320;
		}
		else
		{
			while(*modes != NULL)
			{
				w = (*modes)->w;
				h = (*modes)->h;
				if(h > w) // Skip "landscape" modes
					break;
				modes++;
			}
		}
#else
		w  = 640;
		h  = 480;
#endif
	}
	
	if(bpp == depthAuto)
	{
		if(info && info->vfmt)
			video_bpp = info->vfmt->BitsPerPixel;
		else
			video_bpp = 16;
	}
	else
	{
		video_bpp =	bpp * 8;
	}

	SDLScreen * screen = new SDLScreen(w, h, video_bpp, fullscreen, nFPS);
	
	return screen;
}

