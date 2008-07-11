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

#ifndef __TROLL_GRAPHICS_H__
#define __TROLL_GRAPHICS_H__

namespace Troll
{

class Color;

class Point;
class Rect;

class GraphicsImpl;
class Surface;

class Graphics
{
	GraphicsImpl * m_impl;
public:

	Graphics(Surface & surface);
	virtual ~Graphics();

public:

	void EnableAntiAlias(bool enable);
	
	void DrawPixel(const Point& pt,const Color & color);
	void DrawLine(const Point& ptStart,const Point& ptEnd,const Color & color);

	void DrawVLine(const Point& ptStart,int size,const Color & color);
	void DrawHLine(const Point& ptStart,int size,const Color & color);
	
	void DrawCircle(const Point& pt,short rad,const Color& color);
	void DrawCircleFill(const Point& pt,short rad,const Color& color);
	
	void DrawRect(const Rect& rect,const Color& color);
	void DrawRectFill(const Rect& rect,const Color& color);

	void DrawRoundRect(const Rect& rect,int rad,const Color& color);
	void DrawRoundRectFill(const Rect& rect,int rad,const Color& color);
	
	void DrawEllipse(const Point& pt,short radx,short rady,const Color& color);
	void DrawEllipseFill(const Point& pt,short radx,short rady,const Color& color);
	
	void DrawArc(const Point& pt,short rad,short start_angle,short end_angle,const Color& color);
	void DrawArcFill(const Point& pt,short rad,short start_angle,short end_angle,const Color& color);

	void DrawTriangle(const Point& pt1,const Point& pt2,const Point& pt3,const Color& color);
	void DrawTriangleFill(const Point& pt1,const Point& pt2,const Point& pt3,const Color& color);
	
	void DrawPolygon(const Point * pts,int n,const Color& color);
	void DrawPolygonFill(const Point * pts,int n,const Color& color);
	
	void DrawText(const Point& pt,const char * text,const Color& color);
};




}
#endif //__TROLL_GRAPHICS_H__