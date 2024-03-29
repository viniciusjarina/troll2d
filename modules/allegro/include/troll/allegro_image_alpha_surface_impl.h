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

#ifndef __TROLL_ALLEGRO_IMAGE_ALPHA_SURFACE_IMPL_H__
#define __TROLL_ALLEGRO_IMAGE_ALPHA_SURFACE_IMPL_H__

#include "troll/image_impl.h"

#include "troll/allegro_image_surface_impl.h"

namespace Troll
{

class AllegroImageAlphaSurfaceImpl : public AllegroImageSurfaceImpl
{
public:
	AllegroImageAlphaSurfaceImpl(BITMAP * bmp):
	AllegroImageSurfaceImpl(bmp)
	{
		convert_alpha(bmp);
	}
	  
public:

/*
	virtual void DrawStretch(SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource = Rect(0,0,-1,-1)) const;
	virtual void DrawRotate(SurfaceImpl & destination,const Point& ptDest,short angle) const;
	virtual void Draw(SurfaceImpl & destination,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1)) const;
	virtual void DrawAlpha(SurfaceImpl & destination,const Point& ptDest = Point(0,0),unsigned char alpha = 128) const;
*/
	virtual void Draw(SurfaceImpl & destination,
					  const Point& ptDest = Point(0,0),
					  DrawFlags flags = DrawFlags::none,
					  AlphaComponent opacity = Color::alphaOpaque) const;

	virtual void Draw(SurfaceImpl & destination,
					  const Point& ptDest,
					  const Rect& rSource,
					  DrawFlags flags = DrawFlags::none,
					  AlphaComponent opacity = Color::alphaOpaque) const;
	
	virtual void DrawStretch(SurfaceImpl & destination,
							 const Rect& rcDest,
							 DrawFlags flags = DrawFlags::none,
							 AlphaComponent opacity = Color::alphaOpaque) const;

	virtual void DrawStretch(SurfaceImpl & destination,
							 const Rect& rcDest,
							 const Rect& rSource,
							 DrawFlags flags = DrawFlags::none,
							 AlphaComponent opacity = Color::alphaOpaque) const;
		
	virtual void DrawRotate(SurfaceImpl & destination,
							const Point& ptDest,
							short angle,
							DrawFlags flags = DrawFlags::none,
							AlphaComponent opacity = Color::alphaOpaque) const;	
};



}

#endif // __TROLL_ALLEGRO_IMAGE_ALPHA_SURFACE_IMPL_H__