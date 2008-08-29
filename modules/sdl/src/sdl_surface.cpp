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

#include "sprig.h"
#include "sge.h"
#include "SDL_rotozoom.h"

#include "troll/surface.h"
#include "troll/sdl_surface.h"

#include "troll/sdl_system.h"

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
		bpp = SDLSystem::GetScreenBPP();
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

void SDLSurface::Draw(SurfaceImpl & destination,const Point& ptDest /*Point(0,0)*/,const Rect& rSource /*Rect(0,0,-1,-1)*/) const
{
	SDL_Rect rect1;
	SDL_Rect rect2;

	int width;
	int height;

	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	if(rSource.width < 0)
		width = source->w;
	else
		width = rSource.width;

	if(rSource.height < 0)
		height = source->h;
	else
		height = rSource.height;

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

void SDLSurface::DrawAlpha( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,unsigned char alpha /*= 128*/ ) const
{
	SDL_Rect rect1;
	SDL_Rect rect2;
		
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	rect1.x = 0;
	rect1.y = 0;
	rect1.h = source->h;
	rect1.w = source->w;
	
	rect2.x = ptDest.x;
	rect2.y = ptDest.y;
	rect2.h = source->h;
	rect2.w = source->w;
#if  0
	SDL_SetAlpha(source,SDL_SRCALPHA,alpha);

	SDL_BlitSurface(source,&rect1,dest,&rect2);
#else
	
	SDL_SetAlpha(source,SDL_SRCALPHA,alpha);
	SPG_Blit(source,&rect1,dest,&rect2);
#endif
}


void SDLSurface::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource /*= Rect(0,0,-1,-1)*/ ) const
{
	SDL_Rect rect1;
	SDL_Rect rect2;
	
	int width;
	int height;
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	if(rSource.width < 0)
		width = source->w;
	else
		width = rSource.width;
	
	if(rSource.height < 0)
		height = source->h;
	else
		height = rSource.height;
	
	rect1.x = rSource.x;
	rect1.y = rSource.y;
	rect1.h = height;
	rect1.w = width;
	
	rect2.x = rcDest.x;
	rect2.y = rcDest.y;
	rect2.h = rcDest.height;
	rect2.w = rcDest.width;

	float zoomx = ((float)rect2.w/(float)rect1.w);
	float zoomy = ((float)rect2.h/(float)rect1.h);
	
#if 1
	// TODO: Found a better way to transform surfaces, considering colokey+alpha 
	SPG_TransformSurface(source,dest,0.0f,zoomx,zoomy,0,0,rect2.x,rect2.y,SPG_TCOLORKEY|SPG_TAA|SPG_TSAFE);
#else
	sge_transform(source,dest,0.0f,zoomx,zoomy,0,0,rect2.x,rect2.y,0);
#endif
}