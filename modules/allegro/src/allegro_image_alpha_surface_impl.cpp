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

void AllegroImageAlphaSurfaceImpl::Draw( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,const Rect& rSource /*= Rect(0,0,-1,-1)*/ ) const
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

	_aa_stretch_blit (source, dest, 
		iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.y,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		AA_MASKED|AA_NO_AA|AA_ALPHA|AA_BLEND);
}

void AllegroImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource /*= Rect(0,0,-1,-1)*/ ) const
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
	
	_aa_stretch_blit (source, dest, 
		iround(ldexp(rSource.x,aa_BITS)), iround(ldexp(rSource.y,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		iround(ldexp(rcDest.x,aa_BITS)), iround(ldexp(rcDest.y,aa_BITS)), 
		iround(ldexp(rcDest.width,aa_BITS)), iround(ldexp(rcDest.height,aa_BITS)), 
		AA_MASKED|AA_ALPHA|AA_BLEND|AA_NO_AA);
}

void AllegroImageAlphaSurfaceImpl::DrawAlpha( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,unsigned char alpha /*= 128*/ ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	int width;
	int height;
	
	width  = source->w;
	height = source->h;
	
	aa_set_trans(255 - alpha);
	
	_aa_stretch_blit (source, dest, 
		iround(ldexp(0,aa_BITS)), iround(ldexp(0,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		iround(ldexp(ptDest.x,aa_BITS)), iround(ldexp(ptDest.y,aa_BITS)), 
		iround(ldexp(width,aa_BITS)), iround(ldexp(height,aa_BITS)), 
		AA_MASKED|AA_ALPHA|AA_BLEND);

	aa_set_trans(0);
}

void AllegroImageAlphaSurfaceImpl::DrawRotate( SurfaceImpl & destination,const Point& ptDest,short angle ) const
{
	BITMAP * source = m_surface;
	BITMAP * dest = ((AllegroSurface *)&destination)->m_surface;
	
	_aa_rotate_bitmap (source, dest, 
		ptDest.x, ptDest.y, 
		itofix((angle<<8)/360),
		itofix(1),itofix(1),
		AA_MASKED|AA_ALPHA|AA_BLEND|AA_NO_AA);
}