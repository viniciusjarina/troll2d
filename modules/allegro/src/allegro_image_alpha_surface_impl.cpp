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

#include <math.h>

#include <allegro.h>

#include "aastr2/aastr.h"
#include "aastr2/round.h"

#include "troll/surface.h"

#include "troll/allegro_surface.h"
#include "troll/allegro_image.h"

#include "troll/surface.h"

#include "troll/allegro_image_alpha_surface_impl.h"

using Troll::Point;
using Troll::Rect;

using Troll::Surface;
using Troll::SurfaceImpl;

using Troll::AllegroSurface;
using Troll::AllegroImageAlphaSurfaceImpl;

using Troll::DrawFlags;
using Troll::AlphaComponent;


void AllegroImageAlphaSurfaceImpl::Draw( SurfaceImpl & destination, const Point& ptDest /*= Point(0,0)*/, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;

	int aa_flags = AA_MASKED | AA_BLEND;

	if(flags & DrawFlags::horizontalFlip)
		aa_flags |= AA_HFLIP;

	if(flags & DrawFlags::verticalFlip)
		aa_flags |= AA_VFLIP;

	// TODO: Fix AASTR bug AA_NO_AA not working when using alpha channel or global alpha

	if(opacity == Color::alphaOpaque)
	{
		aa_flags |= AA_NO_AA;	

		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			aa_flags);
	}
	else
	{
		aa_flags |= AA_ALPHA;

		aa_set_trans(255 - opacity);

		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			aa_flags);

		aa_set_trans(0);
	}
}

void AllegroImageAlphaSurfaceImpl::Draw( SurfaceImpl & destination, const Point& ptDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	int aa_flags = AA_MASKED | AA_BLEND;
	
	if(flags & DrawFlags::horizontalFlip)
		aa_flags |= AA_HFLIP;
	
	if(flags & DrawFlags::verticalFlip)
		aa_flags |= AA_VFLIP;
	
	// TODO: Fix AASTR bug AA_NO_AA not working when using alpha channel or global alpha
	
	if(opacity == Color::alphaOpaque)
	{
		aa_flags |= AA_NO_AA;	
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			aa_flags);
	}
	else
	{
		aa_flags |= AA_ALPHA;
		
		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.y,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			aa_flags);
		
		aa_set_trans(0);
	}
}

void AllegroImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	int aa_flags = AA_MASKED | AA_BLEND | AA_ALPHA;
	
	if(flags & DrawFlags::horizontalFlip)
		aa_flags |= AA_HFLIP;
	
	if(flags & DrawFlags::verticalFlip)
		aa_flags |= AA_VFLIP;

	
	// TODO: Fix AASTR bug AA_NO_AA not working when using alpha channel or global alpha
	
	if(opacity == Color::alphaOpaque)
	{
		if(flags & DrawFlags::noAntiAlias)
			aa_flags |= AA_NO_AA;
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			aa_flags);
	}
	else
	{
		/* TODO: Fix AA_NO_AA with opacity != opaque
		if(flags & DrawFlags::drawNoAntiAlias)
			aa_flags |= AA_NO_AA;*/

		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
			iround(ldexp(source->w,aa_BITS)), iround(ldexp(source->h,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)),  
			aa_flags);
		
		aa_set_trans(0);
	}
}

void AllegroImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination, const Rect& rcDest, const Rect& rSource, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	int aa_flags = AA_MASKED | AA_BLEND | AA_ALPHA;
	
	if(flags & DrawFlags::horizontalFlip)
		aa_flags |= AA_HFLIP;
	
	if(flags & DrawFlags::verticalFlip)
		aa_flags |= AA_VFLIP;

	// TODO: Fix AASTR bug AA_NO_AA not working when using alpha channel or global alpha
	
	if(opacity == Color::alphaOpaque)
	{
		if(flags & DrawFlags::noAntiAlias)
			aa_flags |= AA_NO_AA;

		 _aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			aa_flags);
	}
	else
	{
		/* TODO: Fix AA_NO_AA with opacity != opaque
		if(flags & DrawFlags::drawNoAntiAlias)
			aa_flags |= AA_NO_AA;*/

		aa_set_trans(255 - opacity);
		
		_aa_stretch_blit (source, dest, 
			iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.x,aa_BITS)), 
			iround(ldexp(rSource.width,aa_BITS)), iround(ldexp(rSource.height,aa_BITS)), 
			iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
			iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
			aa_flags);
		
		aa_set_trans(0);
	}
}

void AllegroImageAlphaSurfaceImpl::DrawRotate( SurfaceImpl & destination, const Point& ptDest, short angle, DrawFlags flags /*= none*/, AlphaComponent opacity /*= Color::alphaOpaque*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;

	int scalex = 1;
	int scaley = 1;

	int astr_flags = AA_MASKED | AA_BLEND | AA_ALPHA;
	
	if(flags & DrawFlags::horizontalFlip)
		scalex = -1;
	
	if(flags & DrawFlags::verticalFlip)
		scaley = -1;
	
	if(opacity == Color::alphaOpaque)
	{
		if(flags & DrawFlags::noAntiAlias)
			astr_flags |= AA_NO_AA;

		_aa_rotate_bitmap (source, dest, 
			ptDest.x, ptDest.y, 
			itofix((angle<<8)/360),
			itofix(scalex),itofix(scaley),
			astr_flags);
	}
	else
	{
		/* TODO: Fix AA_NO_AA with opacity != opaque
		if(flags & DrawFlags::drawNoAntiAlias)
			aa_flags |= AA_NO_AA;*/

		aa_set_trans(255 - opacity);
		
		_aa_rotate_bitmap (source, dest, 
			ptDest.x, ptDest.y, 
			itofix((angle<<8)/360),
			itofix(scalex),itofix(scaley),
			astr_flags);
		
		aa_set_trans(0);
	}
}