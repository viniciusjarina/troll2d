/*
 *
 *  ______             ___    ___      
 * /\__  _\           /\_ \  /\_ \     
 * \/_/\ \/ _ __   ___\//\ \ \//\ \    
 *    \ \ \/\`'__\/ __`\\ \ \  \ \ \   
 *     \ \ \ \ \//\ \L\ \\_\ \_ \_\ \_ 
 *      \ \_\ \_\\ \____//\____\/\____\
 *       \/_/\/_/ \/___/ \/____/\/____/
 *
 * Copyright (c) 2008, JarinSoft
 * All rights reserved.
 *
 * Vinicius Jarina (viniciusjarina@gmail.com)
 *
 * Visit: http://troll2d.googlecode.com
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JarinSoft nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JarinSoft ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL JARINSOFT BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <SDL.h>

#include "troll/sdl_screen.h"
#include "troll/sdl_surface.h"
#include "troll/screen.h"

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
	
	m_nativeSurface = buffer;
	m_screenSurface = pSurface;
	m_screen_bpp = bpp;
	return true;
}

SDLScreen * SDLScreenHelper::SetupScreen( int w, int h, int bpp, bool fullscreen )
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

	SDLScreen * screen = new SDLScreen(w, h, video_bpp, fullscreen);
	
	return screen;
}