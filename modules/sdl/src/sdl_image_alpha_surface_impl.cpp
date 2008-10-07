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
#include "troll/draw_flags.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_image.h"

#include "troll/sdl_image_surface_impl.h"
#include "troll/sdl_image_alpha_surface_impl.h"

using Troll::Point;
using Troll::Rect;

using Troll::DrawFlags;
using Troll::AlphaComponent;
using Troll::Surface;

using Troll::SurfaceImpl;

using Troll::SDLSurface;
using Troll::SDLImageSurfaceHelper;

using Troll::SDLImageAlphaSurfaceImpl;

void SDLImageAlphaSurfaceImpl::Draw( SurfaceImpl & destination, const Point& ptDest /*= Point(0,0)*/, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
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
			SPG_TransformSurface(source,dest,0.0f, 1.0f,-1.0,0,0,rect1.x,rect1.y + source->h,SPG_TCOLORKEY|SPG_TBLEND);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,1.0,0,0,rect1.x + source->w,rect1.y,SPG_TCOLORKEY|SPG_TBLEND);		
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,-1.0,0,0,rect1.x + source->w,rect1.y + source->h,SPG_TCOLORKEY|SPG_TBLEND);		
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
				SPG_Blit(source,NULL,dest,&rect1);
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

void SDLImageAlphaSurfaceImpl::Draw( SurfaceImpl & destination, const Point& ptDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Rect rect1; // destination rect
	SDL_Rect rect2; // source rect
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	rect1.x = ptDest.x;
	rect1.y = ptDest.y;

	rect2.x = rSource.x;
	rect2.y = rSource.y;
	rect2.w = rSource.width;
	rect2.h = rSource.height;

	
	
	
		
	if(opacity == Color::alphaOpaque)
	{
		if( !(flags & DrawFlags::horizontalFlip))
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SDL_BlitSurface(source,&rect2,dest,&rect1);
				return;
			}
			
			SPG_TransformSurface(source,dest,0.0f, 1.0f,-1.0,rect2.x,rect2.y,rect1.x, rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND,&rect2);		
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,1.0,rect2.x,rect2.y,rect1.x + rect2.w, rect1.y,SPG_TCOLORKEY|SPG_TBLEND,&rect2);		
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f,-1.0,rect2.x,rect2.y,rect1.x + rect2.w,rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND,&rect2);		
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
				SPG_Blit(source,&rect2,dest,&rect1);
				SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
				return;
			}
			
			SPG_TransformSurface(source,dest,0.0f, 1.0f, -1.0,rect2.x,rect2.y,rect1.x, rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rect2);
		}
		else
		{
			if(!(flags & DrawFlags::verticalFlip))
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, 1.0,rect2.x,rect2.y,rect1.x + rect2.w, rect1.y,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rect2);	
			}
			else
			{
				SPG_TransformSurface(source,dest,0.0f, -1.0f, -1.0,rect2.x,rect2.y,rect1.x + rect2.w,rect1.y + rect2.h,SPG_TCOLORKEY|SPG_TBLEND|SPG_TSURFACE_ALPHA, &rect2);
			}
		}	
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}

void SDLImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint8 sprig_flags = SPG_TCOLORKEY | SPG_TBLEND;
		
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
		SPG_TransformSurface(source, dest, 0.0f, zoomx, zoomy, 0, 0, rcDest.x + w_offset, rcDest.y + h_offset, sprig_flags | SPG_TSURFACE_ALPHA);
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}	
}

void SDLImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint16 w_offset = 0;
	Uint16 h_offset = 0;

	Uint8 sprig_flags = SPG_TCOLORKEY|SPG_TBLEND;
	
	if(rSource.width == 0 || rSource.height == 0)
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
			sprig_flags|SPG_TSURFACE_ALPHA, &rcClip);	
		
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}

void SDLImageAlphaSurfaceImpl::DrawRotate( SurfaceImpl & destination, const Point& ptDest, short angle, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;

	Uint8 sprig_flags = SPG_TCOLORKEY|SPG_TBLEND;

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
		SPG_TransformSurface(source,dest,(float)angle,zoomx,zoomy,(source->w >> 1),(source->h >> 1),ptDest.x,ptDest.y,sprig_flags|SPG_TSURFACE_ALPHA);	
		SDL_SetAlpha(source,SDL_SRCALPHA,SDL_ALPHA_OPAQUE);
	}
}
