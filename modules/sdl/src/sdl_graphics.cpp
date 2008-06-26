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

#include "SDL_gfxPrimitives.h"

#include "troll.h"

#include "troll/graphics.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_graphics.h"

using namespace Troll;

SDLGraphics::SDLGraphics( SDLSurface * surface )
{
	m_surface =  surface->m_surface;
}

void SDLGraphics::DrawPixel(const Point& pt,const Color & color)
{
	pixelRGBA(m_surface, pt.x, pt.y, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color & color )
{
	lineRGBA(m_surface,ptStart.x,ptStart.y,ptEnd.x,ptEnd.y,color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawVLine(const Point& ptStart,int size,const Color & color)
{
	vlineRGBA(m_surface,ptStart.x,ptStart.y, ptStart.y + size,color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawHLine(const Point& ptStart,int size,const Color & color)
{
	hlineRGBA(m_surface, ptStart.x, ptStart.x + size, ptStart.y, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawCircle( const Point& ptCenter, short radius, const Color & color )
{
	circleRGBA(m_surface, ptCenter.x, ptCenter.y, radius, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawCircleFill(const Point& ptCenter,short radius,const Color& color)
{
	filledCircleRGBA(m_surface, ptCenter.x, ptCenter.y, radius, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawRect(const Rect& rect,const Color& color)
{
	rectangleRGBA(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawRectFill(const Rect& rect,const Color& color)
{
	boxRGBA(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawEllipse(const Point& pt,short radx,short rady,const Color& color)
{
	ellipseRGBA(m_surface, pt.x, pt.y, radx, rady, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawEllipseFill(const Point& pt,short radx,short rady,const Color& color)
{
	filledEllipseRGBA(m_surface, pt.x, pt.y, radx, rady, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawArc(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	arcRGBA(m_surface, pt.x, pt.y, rad, start_angle, end_angle, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawArcFill(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	filledPieRGBA(m_surface, pt.x, pt.y, rad, start_angle, end_angle, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawText(const Point& pt,const char * text,const Color& color)
{
	stringRGBA(m_surface, pt.x, pt.y, text, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawTriangle( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	trigonRGBA(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawTriangleFill( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	filledTrigonRGBA(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawPolygon( const Point * pts,int n,const Color& color )
{
	if(n < 3)
		return;

	Sint16 * arr_x = new Sint16[n];
	Sint16 * arr_y = new Sint16[n];

	for(int i = 0; i < n; i++)
	{
		arr_x[i] = (Sint16)pts[n].x;
		arr_y[i] = (Sint16)pts[n].y;
	}

	polygonRGBA(m_surface, arr_x, arr_y, n, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());

	delete [] arr_x;
	delete [] arr_y;
}

void SDLGraphics::DrawPolygonFill( const Point * pts,int n,const Color& color )
{
	if(n < 3)
		return;
	
	Sint16 * arr_x = new Sint16[n];
	Sint16 * arr_y = new Sint16[n];
	
	for(int i = 0; i < n; i++)
	{
		arr_x[i] = (Sint16)pts[n].x;
		arr_y[i] = (Sint16)pts[n].y;
	}
	
	filledPolygonRGBA(m_surface, arr_x, arr_y, n, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
		
	delete [] arr_x;
	delete [] arr_y;
}