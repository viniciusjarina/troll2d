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

#include "troll/surface.h"
#include "troll/sdl_surface.h"

#include "troll/sdl_system.h"

using namespace Troll;

SDLSurface::SDLSurface()
{
	m_surface = NULL;
}


SDLSurface::SDLSurface( SDL_Surface * screen ):
m_surface(screen)
{
	
}


SDLSurface::~SDLSurface()
{
	if(m_surface != NULL)
		SDL_FreeSurface(m_surface);
}

bool SDLSurface::Create(int width, int height, ColorDepth depth /*= depthAuto*/)
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


void SDLSurface::DrawFast( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/ ) const
{
	SDL_Rect rect1;
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	
	rect1.x = ptDest.x;
	rect1.y = ptDest.y;
	//rect1.h = 0; Only the position is used in the dstrect (the width and height are ignored).
	//rect1.w = 0; so why waste time setting h or w :)
		
	SDL_BlitSurface(source,NULL,dest,&rect1);	
}


void SDLSurface::Draw( SurfaceImpl & destination, const Point& ptDest /*= Point(0,0)*/, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Rect rect1;
		
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	rect1.x = ptDest.x;
	rect1.y = ptDest.y;
	
	if(opacity == Color::alphaOpaque)
	{
		if( !(flags & DrawFlags::horizontalFlip))
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SDL_BlitSurface(source,NULL,dest,&rect1);
				return;
			}

			SPG_TransformSurface(source, dest, 0.0f, 1.0f, -1.0, 0, 0, rect1.x, rect1.y + source->h, SPG_TCOLORKEY);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,1.0,0,0,rect1.x + source->w,rect1.y,SPG_TCOLORKEY);		
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,-1.0,0,0,rect1.x + source->w,rect1.y + source->h,SPG_TCOLORKEY);		
			}
		}		
	}
	else
	{
		SDL_SetAlpha(source,SDL_SRCALPHA,opacity);

		if( !(flags & DrawFlags::horizontalFlip))
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SDL_BlitSurface(source,NULL,dest,&rect1);
				SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
				return;
			}
			
			SPG_TransformSurface(source,dest,0.0f, 1.0f, -1.0,0,0,rect1.x,rect1.y + source->h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, 1.0,0,0,rect1.x + source->w,rect1.y,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA);	
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, -1.0,0,0,rect1.x + source->w,rect1.y + source->h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA);
			}
		}	
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}

void SDLSurface::Draw( SurfaceImpl & destination, const Point& ptDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Rect rect1; // destination rect
	SDL_Rect rect2; // source rect
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	if(rSource.width == 0 || rSource.height == 0)
		return;
	
	rect1.x = ptDest.x;
	rect1.y = ptDest.y;

	rect2.x = rSource.x;
	rect2.y = rSource.y;
	rect2.w = rSource.width;
	rect2.h = rSource.height;
	
	SDL_Rect rcClip;
		
	rcClip.x = rSource.x; 
	rcClip.y = rSource.y;
	rcClip.h = rSource.height;
	rcClip.w = rSource.width;	
	
	if(opacity == Color::alphaOpaque)
	{
		if( !(flags & DrawFlags::horizontalFlip))
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SDL_BlitSurface(source,&rect2,dest,&rect1);
				return;
			}
			
			SPG_TransformSurface(source,dest,0.0f, 1.0f,-1.0,rect2.x,rect2.y,rect1.x, rect1.y + rect2.h,SPG_TCOLORKEY, &rcClip);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,1.0,rect2.x,rect2.y,rect1.x + rect2.w, rect1.y,SPG_TCOLORKEY, &rcClip);		
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,-1.0,rect2.x,rect2.y,rect1.x + rect2.w,rect1.y + rect2.h,SPG_TCOLORKEY, &rcClip);		
			}
		}		
	}
	else
	{
		SDL_SetAlpha(source,SDL_SRCALPHA,opacity);
		
		if( !(flags & DrawFlags::horizontalFlip))
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SDL_BlitSurface(source,&rect2,dest,&rect1);
				SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
				return;
			}
			SPG_TransformSurface(source,dest,0.0f, 1.0f, -1.0,rect2.x,rect2.y,rect1.x, rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rcClip);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, 1.0,rect2.x,rect2.y,rect1.x + rect2.w, rect1.y,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rcClip);	
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, -1.0,rect2.x,rect2.y,rect1.x + rect2.w,rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rcClip);
			}
		}	
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}

void SDLSurface::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint8 sprig_flags = SPG_TCOLORKEY;
		
	if(source->w == 0 || source->w == 0)
		return;
	
	float zoomx = ((float)rcDest.width /(float)source->w);
	float zoomy = ((float)rcDest.height/(float)source->h);

	Uint16 w_offset = 0;
	Uint16 h_offset = 0;
	
	if(flags & DrawFlags::verticalFlip)
	{
		zoomx = -zoomx;
		w_offset = rcDest.width;
	}

	if(flags & DrawFlags::horizontalFlip)
	{
		zoomy = -zoomy;
		h_offset = rcDest.height;
	}

	if(!(flags & DrawFlags::noAntiAlias))
		sprig_flags |= SPG_TAA;

	if(opacity == Color::alphaOpaque)
	{
		SPG_TransformSurface(source,dest, 0.0f, zoomx, zoomy, 0, 0, rcDest.x + w_offset, rcDest.y + h_offset, sprig_flags );
	}
	else
	{
		SDL_SetAlpha(source,SDL_SRCALPHA,opacity);
		SPG_TransformSurface(source, dest, 0.0f, zoomx, zoomy, 0, 0, rcDest.x + w_offset, rcDest.y + h_offset, sprig_flags | SPG_TBLEND | SPG_TSURFACE_ALPHA);
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
	
}

void SDLSurface::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint16 w_offset = 0;
	Uint16 h_offset = 0;

	Uint8 sprig_flags = SPG_TCOLORKEY;
	
	if(rSource.width == 0 || rSource.height == 0 || rcDest.height == 0 || rcDest.width == 0)
		return;
	
	float zoomx = ((float)rcDest.width /(float)rSource.width);
	float zoomy = ((float)rcDest.height/(float)rSource.height);
	
	if(flags & DrawFlags::verticalFlip)
	{
		zoomx    = -zoomx;
		w_offset = rcDest.width;
	}
	
	if(flags & DrawFlags::horizontalFlip)
	{
		zoomy    = -zoomy;
		h_offset = rcDest.height;
	}

	if(!(flags & DrawFlags::noAntiAlias))
		sprig_flags |= SPG_TAA;
	
	SDL_Rect rcClip;
		
	rcClip.x = rSource.x; 
	rcClip.y = rSource.y;
	rcClip.h = rSource.height;
	rcClip.w = rSource.width;
	
	if(opacity == Color::alphaOpaque)
	{
		SPG_TransformSurface(source,
							 dest,
							 0.0f,
							 zoomx, zoomy,
							 rSource.x, rSource.y,
							 rcDest.x + w_offset,rcDest.y + h_offset,
							 sprig_flags, 
							 &rcClip);
		
	}
	else
	{
		SDL_SetAlpha(source,SDL_SRCALPHA,opacity);
	
		SPG_TransformSurface(source,
			dest,
			0.0f,
			zoomx, zoomy,
			rSource.x, rSource.y,
			rcDest.x + w_offset,rcDest.y + h_offset,
			sprig_flags|SPG_TBLEND|SPG_TSURFACE_ALPHA, 
			&rcClip);	
		
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}

void SDLSurface::DrawRotate( SurfaceImpl & destination, const Point& ptDest, short angle, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint8 sprig_flags = SPG_TCOLORKEY;

	float zoomx = 1.0f;
	float zoomy = 1.0f;

	if(flags & DrawFlags::verticalFlip)
		zoomx = -zoomx;
	
	if(flags & DrawFlags::horizontalFlip)
		zoomy = -zoomy;

	if(!(flags & DrawFlags::noAntiAlias))
		sprig_flags |= SPG_TAA;
	
	if(opacity == Color::alphaOpaque)
	{
		SPG_TransformSurface(source,dest,(float)angle,zoomx,zoomy,(source->w >> 1),(source->h >> 1),ptDest.x,ptDest.y,sprig_flags);	
	}
	else
	{
		SDL_SetAlpha(source,SDL_SRCALPHA,opacity);
		SPG_TransformSurface(source,dest,(float)angle,zoomx,zoomy,(source->w >> 1),(source->h >> 1),ptDest.x,ptDest.y,sprig_flags|SPG_TBLEND|SPG_TSURFACE_ALPHA);	
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}
