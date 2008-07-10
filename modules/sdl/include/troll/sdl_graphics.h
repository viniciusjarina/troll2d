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

#ifndef __TROLL_SDL_GRAPHICS_H__
#define __TROLL_SDL_GRAPHICS_H__

#include "troll/graphics_impl.h"

namespace Troll
{

class SDLGraphics : public GraphicsImpl
{
public:
	SDLGraphics(SDLSurface * surface);

protected:

	virtual void EnableAntiAlias(bool enable);

	virtual void DrawPixel(const Point& pt,const Color & color);
	virtual void DrawLine(const Point& ptStart,const Point& ptEnd,const Color & color);

	virtual void DrawVLine(const Point& ptStart,int size,const Color & color);
	virtual void DrawHLine(const Point& ptStart,int size,const Color & color);
	
	virtual void DrawCircle(const Point& pt,short rad,const Color& color);
	virtual void DrawCircleFill(const Point& pt,short rad,const Color& color);
	
	virtual void DrawRect(const Rect& rect,const Color& color);
	virtual void DrawRectFill(const Rect& rect,const Color& color);

	virtual void DrawRoundRect(const Rect& rect,int rad,const Color& color);
	virtual void DrawRoundRectFill(const Rect& rect,int rad,const Color& color);
	
	virtual void DrawEllipse(const Point& pt,short radx,short rady,const Color& color);
	virtual void DrawEllipseFill(const Point& pt,short radx,short rady,const Color& color);
		
	virtual void DrawArc(const Point& pt,short rad,short start_angle,short end_angle,const Color& color);
	virtual void DrawArcFill(const Point& pt,short rad,short start_angle,short end_angle,const Color& color);
	
	virtual void DrawTriangle(const Point& pt1,const Point& pt2,const Point& pt3,const Color& color);
	virtual void DrawTriangleFill(const Point& pt1,const Point& pt2,const Point& pt3,const Color& color);
	
	virtual void DrawPolygon(const Point * pts,int n,const Color& color);
	virtual void DrawPolygonFill(const Point * pts,int n,const Color& color);
	
	virtual void DrawText(const Point& pt,const char * text,const Color& color);

private:
	SDL_Surface * m_surface;
};

}

#endif // __TROLL_SDL_GRAPHICS_H__