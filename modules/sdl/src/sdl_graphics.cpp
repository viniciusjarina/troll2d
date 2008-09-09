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
#include "SDL_gfxPrimitives_ex.h"

#include "sprig.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_graphics.h"

using Troll::Color;

using Troll::Point;
using Troll::Rect;

using Troll::SDLSurface;
using Troll::SDLGraphics;

using Troll::ColorComponent;

SDLGraphics::SDLGraphics( SDLSurface * surface )
{
	m_surface =  surface->m_surface;
}

void SDLGraphics::DrawPixel(const Point& pt,const Color & color)
{
	int sdl_color;

	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());

	ColorComponent alpha = color.GetAlpha();
	if(alpha == Color::alphaOpaque)
	{
		SPG_Pixel(m_surface, pt.x ,pt.y,sdl_color);
	}
	else
	{
		SPG_PixelBlend(m_surface, pt.x ,pt.y, sdl_color, alpha);
	}
}

void SDLGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color & color )
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	if(alpha == Color::alphaOpaque)
	{
		SPG_Line(m_surface, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, sdl_color);
	}
	else
	{
		SPG_LineBlend(m_surface, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, sdl_color, alpha);
	}
}

void SDLGraphics::DrawVLine(const Point& ptStart,int size,const Color & color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	if(alpha == Color::alphaOpaque)
	{
		SPG_LineV(m_surface, ptStart.x,ptStart.y + size,ptStart.y, sdl_color);
	}
	else
	{
		SPG_LineVBlend(m_surface, ptStart.x,ptStart.y + size,ptStart.y, sdl_color, alpha);
	}
}

void SDLGraphics::DrawHLine(const Point& ptStart,int size,const Color & color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	if(alpha == Color::alphaOpaque)
	{
		SPG_LineH(m_surface, ptStart.x, ptStart.y,ptStart.x + size,sdl_color);
	}
	else
	{
		SPG_LineHBlend(m_surface, ptStart.x, ptStart.y,ptStart.x + size, sdl_color, alpha);
	}
}

void SDLGraphics::DrawCircle( const Point& ptCenter, short radius, const Color & color )
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();

	if(alpha == Color::alphaOpaque)
	{
		SPG_Circle(m_surface, ptCenter.x, ptCenter.y, radius,sdl_color);
	}
	else
	{
		SPG_CircleBlend(m_surface, ptCenter.x, ptCenter.y, radius, sdl_color, alpha);
	}
}

void SDLGraphics::DrawCircleFill(const Point& ptCenter,short radius,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_CircleFilled(m_surface, ptCenter.x, ptCenter.y, radius,sdl_color);
	}
	else
	{
		SPG_CircleFilledBlend(m_surface, ptCenter.x, ptCenter.y, radius, sdl_color, alpha);
	}
}

void SDLGraphics::DrawRect(const Rect& rect,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_Rect(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(),sdl_color);
	}
	else
	{
		SPG_RectBlend(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(),sdl_color, alpha);
	}
}

void SDLGraphics::DrawRectFill(const Rect& rect,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_RectFilled(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(),sdl_color);
	}
	else
	{
		SPG_RectFilledBlend(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(),sdl_color , alpha);
	}
}

void SDLGraphics::DrawEllipse(const Point& pt,short radx,short rady,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_Ellipse(m_surface, pt.x, pt.y, radx, rady,sdl_color);
	}
	else
	{
		SPG_EllipseBlend(m_surface, pt.x, pt.y, radx, rady, sdl_color, alpha);
	}
}

void SDLGraphics::DrawEllipseFill(const Point& pt,short radx,short rady,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_EllipseFilled(m_surface, pt.x, pt.y, radx, rady,sdl_color);
	}
	else
	{
		SPG_EllipseFilledBlend(m_surface, pt.x, pt.y, radx, rady, sdl_color, alpha);
	}
}

void SDLGraphics::DrawArc(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_Arc(m_surface, pt.x, pt.y, rad,-end_angle,-start_angle,sdl_color);
	}
	else
	{
		SPG_ArcBlend(m_surface, pt.x, pt.y, rad,-end_angle,-start_angle, sdl_color, alpha);
	}
}

void SDLGraphics::DrawArcFill(const Point& pt,short rad,short start_angle,short end_angle,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_ArcFilled(m_surface, pt.x, pt.y, rad,-end_angle,-start_angle,sdl_color);
	}
	else
	{
		SPG_ArcFilledBlend(m_surface, pt.x, pt.y, rad,-end_angle,-start_angle, sdl_color, alpha);
	}
}

void SDLGraphics::DrawText(const Point& pt,const char * text,const Color& color)
{
	// TODO: SDL_ttf
	stringRGBA(m_surface, pt.x, pt.y, text, color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

void SDLGraphics::DrawTriangle( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_Trigon(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,sdl_color);
	}
	else
	{
		SPG_TrigonBlend(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, sdl_color, alpha);
	}
}

void SDLGraphics::DrawTriangleFill( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_TrigonFilled(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,sdl_color);
	}
	else
	{
		SPG_TrigonFilledBlend(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y, sdl_color, alpha);
	}
}

void SDLGraphics::DrawPolygon( const Point * pts,int n,const Color& color )
{
	if(n < 3)
		return;

	Sint16 * arr_x = new Sint16[n];
	Sint16 * arr_y = new Sint16[n];

	for(int i = 0; i < n; i++)
	{
		arr_x[i] = (Sint16)pts[i].x;
		arr_y[i] = (Sint16)pts[i].y;
	}

	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_Polygon(m_surface, n, arr_x, arr_y,sdl_color);
	}
	else
	{
		SPG_PolygonBlend(m_surface, n, arr_x, arr_y, sdl_color, alpha);
	}

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
		arr_x[i] = (Sint16)pts[i].x;
		arr_y[i] = (Sint16)pts[i].y;
	}

	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_PolygonFilled(m_surface, n, arr_x, arr_y,sdl_color);
	}
	else
	{
		SPG_PolygonFilledBlend(m_surface, n, arr_x, arr_y, sdl_color, alpha);
	}		
	delete [] arr_x;
	delete [] arr_y;
}

void SDLGraphics::EnableAntiAlias( bool enable )
{
	SPG_SetAA(enable);
}

void SDLGraphics::DrawRoundRect(const Rect& rect,int rad,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_RectRound(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), rad,sdl_color);
	}
	else
	{
		SPG_RectRoundBlend(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), rad, sdl_color, alpha);
	}
}

void SDLGraphics::DrawRoundRectFill(const Rect& rect,int rad,const Color& color)
{
	int sdl_color;
	
	sdl_color = SDL_MapRGB(m_surface->format,color.GetRed(),color.GetGreen(),color.GetBlue());
	
	ColorComponent alpha = color.GetAlpha();
	
	if(alpha == Color::alphaOpaque)
	{
		SPG_RectRoundFilled(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), rad,sdl_color);
	}
	else
	{
		SPG_RectRoundFilledBlend(m_surface, rect.x, rect.y, rect.GetRight(), rect.GetBottom(), rad, sdl_color, alpha);
	}
}

