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

// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL_SURFACE_IMPL_H__)
#define __TROLL_SURFACE_IMPL_H__

#include "troll/color.h"
#include "troll/draw_flags.h"

#include "troll/size.h"
#include "troll/point.h"
#include "troll/rect.h"


namespace Troll
{

class SurfaceImpl  
{
public:
	SurfaceImpl();
	virtual ~SurfaceImpl();

public:
	virtual bool Create(int width,int height,ColorDepth depth = depthAuto) = 0;

	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;

	virtual void SetClip(const Rect & rect) = 0;
	virtual Rect GetClip() const = 0;
	virtual void ResetClip() = 0;

	virtual void Clear(const Color & color = Color::BLACK) = 0;

	
	virtual void DrawFast(SurfaceImpl & destination,const Point& ptDest = Point(0,0)) const = 0;
	
	virtual void Draw(SurfaceImpl & destination,
					  const Point& ptDest = Point(0,0),
					  DrawFlags flags = none,
					  AlphaComponent opacity = Color::alphaOpaque) const = 0;

	virtual void Draw(SurfaceImpl & destination,
					  const Point& ptDest,
					  const Rect& rSource,
					  DrawFlags flags = none,
					  AlphaComponent opacity = Color::alphaOpaque) const = 0;
	
	virtual void DrawStretch(SurfaceImpl & destination,
							 const Rect& rcDest,
							 DrawFlags flags = none,
							 AlphaComponent opacity = Color::alphaOpaque) const = 0;

	virtual void DrawStretch(SurfaceImpl & destination,
							 const Rect& rcDest,
							 const Rect& rSource,
							 DrawFlags flags = none,
							 AlphaComponent opacity = Color::alphaOpaque) const = 0;
		
	virtual void DrawRotate(SurfaceImpl & destination,
							const Point& ptDest,
							short angle,
							DrawFlags flags = none,
							AlphaComponent opacity = Color::alphaOpaque) const = 0;

};

}
#endif // !defined(__TROLL_SURFACE_IMPL_H__)
