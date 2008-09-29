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

#if !defined(__SDL_TROLL2D_SURFACE_H__)
#define __SDL_TROLL2D_SURFACE_H__

#include "troll/surface_impl.h"

struct SDL_Surface;

namespace Troll
{


class SDLSurface  : public SurfaceImpl
{
	friend class SDLGraphics;

	friend class SDLImageSurfaceImpl;
	friend class SDLImageAlphaSurfaceImpl;

protected:
	SDLSurface(::SDL_Surface * screen); //Used only by Screen class

public:
	SDLSurface();
	virtual ~SDLSurface();

public:
	virtual bool Create(int width,int height,ColorDepth depth = depthAuto);

	virtual int GetHeight() const;
	virtual int GetWidth() const;

	virtual void SetClip(const Rect & rect);
	virtual Rect GetClip() const;
	virtual void ResetClip();

	virtual void Clear(const Color & color = Color::INVISIBLE);

	virtual void DrawFast(SurfaceImpl & destination,const Point& ptDest = Point(0,0)) const;
	
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
private:

	SDL_Surface	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
