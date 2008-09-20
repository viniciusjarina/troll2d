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

// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////
#include <math.h>

#include <allegro.h>

#include "aastr2/aastr.h"
#include "aastr2/round.h"


#include "troll/surface.h"
#include "troll/allegro_surface.h"

#include "troll/surface_factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

AllegroSurface::AllegroSurface():
m_surface(NULL)
{
}

AllegroSurface::AllegroSurface( BITMAP * surface ):
m_surface(surface)
{
	
}

AllegroSurface::~AllegroSurface()
{
	if(m_surface)
		destroy_bitmap(m_surface);
}

bool AllegroSurface::Create(int width,int height,ColorDepth depth /*= depthAuto*/)
{
	if(m_surface != NULL)
		return false;
	
	if(depth == depthAuto)
		m_surface = create_bitmap(width,height);
	else
		m_surface = create_bitmap_ex(width,height,depth*8);
	
	return true;
}

int AllegroSurface::GetHeight() const
{
	ASSERT(m_surface != NULL);
	return m_surface->h;
}

int AllegroSurface::GetWidth() const
{
	ASSERT(m_surface != NULL);
	return m_surface->w;
}

void AllegroSurface::SetClip(const Rect & rect)
{
	set_clip_rect(m_surface, rect.x, rect.y, rect.x + rect.width,rect.y + rect.height);
}

Rect AllegroSurface::GetClip() const
{
	Rect r;
	int x2,y2;
	get_clip_rect(m_surface, &r.x, &r.y,&x2,&y2);
	r.width  = r.x - x2;
	r.height = r.y - y2;
	return r;
}

void AllegroSurface::ResetClip()
{
	Rect r(0,0,m_surface->w,m_surface->h);

	AllegroSurface::SetClip(r);
}

void AllegroSurface::Clear(const Color & color /*= Color::BLACK*/)
{
	clear_to_color(m_surface,makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
}

#if 0

void AllegroSurface::Draw(SurfaceImpl & destination,const Point& ptDest /*Point(0,0)*/,const Rect& rSource /*Rect(0,0,-1,-1)*/) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	int width;
	int height;

	if(rSource.width < 0)
		width  = source->w;
	else
		width = rSource.width;

	if(rSource.height < 0)
		height = source->h;
	else
		width = rSource.height;

	masked_blit(source,dest,rSource.x,rSource.y,ptDest.x,ptDest.y,width,height);
}

void AllegroSurface::DrawAlpha( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,unsigned char alpha /*= 128*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;

	set_trans_blender(0,0,0,alpha);

	draw_trans_sprite(dest,source,ptDest.x,ptDest.y);

	set_trans_blender(0,0,0,255);
}

void AllegroSurface::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource /*= Rect(0,0,-1,-1)*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP *dest = ((AllegroSurface *)&destination)->m_surface;
	int width;
	int height;
	
	if(rSource.width < 0)
		width  = source->w;
	else
		width = rSource.width;
	
	if(rSource.height < 0)
		height = source->h;
	else
		width = rSource.height;

#if 0 
	// TODO AA-flag
	_aa_stretch_blit (source, dest, 
		iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.y,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
		iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
		AA_MASKED);
#endif
	
	masked_stretch_blit(source, dest, rSource.x, rSource.y, width, height, rcDest.x, rcDest.y,rcDest.width, rcDest.height);
}

void AllegroSurface::DrawRotate( SurfaceImpl & destination,const Point& ptDest,short angle ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;

	rotate_sprite(dest,source,ptDest.x - (source->w>>1),ptDest.y - (source->h>>1),itofix((angle<<8)/360));
}

#endif

void AllegroSurface::DrawFast( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	blit(source, dest, 0, 0, ptDest.x, ptDest.y, source->w, source->h);
}

void AllegroSurface::Draw( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,DrawFlags flags /*= none*/,AlphaComponent opacity) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;

	if(opacity == Color::alphaOpaque)
	{
		if(! (flags&drawHorizontalFlip) )
		{
			if(! (flags&drawVerticalFlip) )
			{
				draw_sprite(dest, source, ptDest.x, ptDest.y);
			}
			else
			{
				draw_sprite_v_flip(dest, source, ptDest.x, ptDest.y);
			}
		}
		else
		{
			if(! (flags&drawVerticalFlip) )
			{
				draw_sprite_h_flip(dest, source, ptDest.x, ptDest.y);
			}
			else
			{
				draw_sprite_vh_flip(dest, source, ptDest.x, ptDest.y);
			}
		}
	}
	else
	{
		if(!(flags&drawHorizontalFlip) && !(flags&drawVerticalFlip))
		{
			set_trans_blender(0,0,0,opacity);
			
			draw_trans_sprite(dest, source, ptDest.x, ptDest.y);
			
			set_trans_blender(0,0,0,255);
			
			return;
		}
		
		int astr_flags = AA_MASKED|AA_BLEND|AA_NO_FILTER;
		
		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;
		
		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			astr_flags);
		
		aa_set_trans(0);
	}
}


void AllegroSurface::Draw( SurfaceImpl & destination,const Point& ptDest ,const Rect& rSource,DrawFlags flags /*= none*/,AlphaComponent opacity) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	int astr_flags;

	if(opacity == Color::alphaOpaque)
	{
		if(!(flags&drawHorizontalFlip) && !(flags&drawVerticalFlip))
		{
			masked_blit(source, dest, rSource.x,rSource.y, ptDest.x, ptDest.y, rSource.width, rSource.height);
			return;
		}

		astr_flags = AA_NO_AA | AA_MASKED;

		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;

		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			astr_flags);
	}
	else
	{
		astr_flags = AA_BLEND | AA_MASKED;
		
		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;

		aa_set_trans(255 - opacity);

		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			astr_flags);

		aa_set_trans(0);
	}
}

void AllegroSurface::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,DrawFlags flags /*= none*/,AlphaComponent opacity) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	int astr_flags;

	if(opacity == Color::alphaOpaque)
	{
		if(!(flags&drawHorizontalFlip) && !(flags&drawVerticalFlip))
		{
			masked_stretch_blit(source, dest, 0, 0, source->w, source->h, rcDest.x, rcDest.y, rcDest.width, rcDest.height);
			return;
		}

		astr_flags = AA_NO_AA | AA_MASKED;
		
		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			astr_flags);
	}
	else
	{
		astr_flags = AA_BLEND | AA_MASKED;

		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;
		
		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			astr_flags);
		
		aa_set_trans(0);
	}
}


void AllegroSurface::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource,DrawFlags flags /*= none*/ ,AlphaComponent opacity) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	int astr_flags;
	
	if(opacity == Color::alphaOpaque)
	{
		if(!(flags&drawHorizontalFlip) && !(flags&drawVerticalFlip))
		{
			masked_stretch_blit(source, dest, rSource.x, rSource.y, rSource.width, rSource.width, rcDest.x, rcDest.y, rcDest.width, rcDest.height);
			return;
		}
		
		astr_flags = AA_NO_AA | AA_MASKED;
		
		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			astr_flags);
	}
	else
	{
		astr_flags = AA_BLEND | AA_MASKED;
		
		if(flags&drawHorizontalFlip)
			astr_flags |= AA_HFLIP;
		
		if(flags&drawVerticalFlip)
			astr_flags |= AA_VFLIP;
		
		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			astr_flags);
		
		aa_set_trans(0);
	}
}

void AllegroSurface::DrawRotate( SurfaceImpl & destination,const Point& ptDest,short angle,DrawFlags flags /*= none*/,AlphaComponent opacity /*= Color::alphaOpaque*/)  const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	int astr_flags;
	
	if(opacity == Color::alphaOpaque)
	{
		if(!(flags&drawHorizontalFlip))
		{
			if(!(flags&drawVerticalFlip))
			{
				rotate_sprite(dest,source,ptDest.x - (source->w>>1),ptDest.y - (source->h>>1),itofix((angle<<8)/360));
			}
			else
			{
				rotate_sprite_v_flip(dest,source,ptDest.x - (source->w>>1),ptDest.y - (source->h>>1),itofix((angle<<8)/360));
			}
		}
		else
		{
			if(!(flags&drawVerticalFlip))
			{
				rotate_sprite_v_flip(dest,source,ptDest.x - (source->w>>1),ptDest.y - (source->h>>1),itofix((angle<<8)/360) + itofix(128));
			}
			else
			{
				rotate_sprite(dest,source,ptDest.x - (source->w>>1),ptDest.y - (source->h>>1),itofix((angle<<8)/360) + itofix(128));
			}
		}
	}
	else
	{
		astr_flags = AA_MASKED | AA_BLEND;
		int scalex = 1;
		int scaley = 1;
		
		if(flags&drawHorizontalFlip)
			scalex = -1;
		
		if(flags&drawVerticalFlip)
			scaley = -1;
		
		aa_set_trans(255 - opacity);

		_aa_rotate_bitmap (source, dest, 
			ptDest.x, ptDest.y, 
			itofix((angle<<8)/360),
			itofix(scalex),itofix(scaley),
			astr_flags);

		aa_set_trans(0);
	}

}
