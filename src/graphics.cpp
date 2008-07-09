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

#include "troll.h"

#include "troll/graphics.h"
#include "troll/graphics_impl.h"

#include "troll/graphics_factory.h"


using namespace Troll;

Graphics::Graphics( Surface & surface )
{
	m_impl = GraphicsFactory::CreateGraphics(surface);
}

Graphics::~Graphics()
{
	if(m_impl)
		delete m_impl;
}

void Graphics::DrawPixel( const Point& pt,const Color & color )
{
	m_impl->DrawPixel(pt,color);
}

void Graphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color& color )
{
	m_impl->DrawLine(ptStart,ptEnd,color);
}

void Graphics::DrawVLine( const Point& ptStart, int size,const Color& color )
{
	m_impl->DrawVLine(ptStart, size,color);
}

void Graphics::DrawHLine( const Point& ptStart, int size,const Color& color )
{
	m_impl->DrawHLine(ptStart, size,color);
}

void Graphics::DrawCircle( const Point& pt,short rad, const Color& color )
{
	m_impl->DrawCircle(pt, rad, color);
}


void Graphics::DrawCircleFill( const Point& pt,short rad,const Color& color )
{
	m_impl->DrawCircleFill(pt,rad,color);
}

void Graphics::DrawRect( const Rect& rect,const Color& color )
{
	m_impl->DrawRect(rect,color);
}

void Graphics::DrawRectFill( const Rect& rect,const Color& color )
{
	m_impl->DrawRectFill(rect,color);
}

void Graphics::DrawRoundRect(const Rect& rect,const Color& color)
{
	m_impl->DrawRoundRect(rect,color);
}

void Graphics::DrawRoundRectFill(const Rect& rect,const Color& color)
{
	m_impl->DrawRoundRectFill(rect,color);
}

void Graphics::DrawEllipse(const Point& pt,short radx,short rady,const Color& color)
{
	m_impl->DrawEllipse(pt, radx, rady, color);
}

void Graphics::DrawEllipseFill(const Point& pt,short radx,short rady,const Color& color)
{
	m_impl->DrawEllipseFill(pt, radx, rady, color);
}

void Graphics::DrawArc(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	m_impl->DrawArc(pt, rad, start_angle, end_angle, color);
}

void Graphics::DrawArcFill(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	m_impl->DrawArcFill(pt, rad, start_angle, end_angle, color);
}

void Graphics::DrawText(const Point& pt,const char * text,const Color& color)
{
	m_impl->DrawText(pt, text, color);
}

void Graphics::DrawTriangle( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	m_impl->DrawTriangle(pt1,pt2,pt3,color);
}

void Graphics::DrawTriangleFill( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	m_impl->DrawTriangleFill(pt1,pt2,pt3,color);
}

void Graphics::DrawPolygon( const Point * pts,int n,const Color& color )
{
	m_impl->DrawPolygon(pts,n,color);
}

void Graphics::DrawPolygonFill( const Point * pts,int n,const Color& color )
{
	m_impl->DrawPolygonFill(pts,n,color);
}

void Graphics::EnableAntiAlias( bool enable )
{
	m_impl->EnableAntiAlias(enable);
}
