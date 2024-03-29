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


#include <allegro.h>

#include "troll.h"

#include "troll/graphics.h"

#include "troll/allegro_surface.h"
#include "troll/allegro_graphics.h"

#include "gfx_ex.h"

#define DRAW_WITH_ALPHA(func ,alpha)		    	\
		drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);		\
		set_trans_blender(0, 0, 0, alpha);			\
		func;										\
		drawing_mode(DRAW_MODE_SOLID, 0, 0, 0)		




using	Troll::Color;
using	Troll::Point;
using	Troll::Rect;

using	Troll::AllegroSurface;

using	Troll::AllegroGraphics;

AllegroGraphics::AllegroGraphics(AllegroSurface * surface)
{
	m_surface =  surface->m_surface;
}

void AllegroGraphics::DrawPixel(const Point& pt,const Color & color)
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(putpixel(m_surface, pt.x, pt.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}

	putpixel(m_surface, pt.x, pt.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return;
}

void AllegroGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(line(m_surface, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	line(m_surface, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawVLine( const Point& ptStart,int size,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(vline(m_surface, ptStart.x, ptStart.y, ptStart.y + size, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	vline(m_surface, ptStart.x, ptStart.y, ptStart.y + size, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawHLine( const Point& ptStart,int size,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(hline(m_surface, ptStart.x, ptStart.y, ptStart.x + size, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	hline(m_surface, ptStart.x, ptStart.y, ptStart.x + size, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawCircle( const Point& ptCenter, short radius,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(circle(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	circle(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawCircleFill( const Point& ptCenter, short radius,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(circlefill(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	circlefill(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawRect(const Rect& r,const Color& color)
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(rect(m_surface, r.x, r.y, r.GetRight(), r.GetBottom(), makecol(color.GetRed(),color.GetGreen(),color.GetBlue())),color.GetAlpha());
		return;
	}
	rect(m_surface, r.x, r.y, r.GetRight(), r.GetBottom(), makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
}

void AllegroGraphics::DrawRectFill(const Rect& rect,const Color& color)
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(rectfill(m_surface, rect.x, rect.y,rect.GetRight(), rect.GetBottom(), makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	rectfill(m_surface, rect.x, rect.y,rect.GetRight(), rect.GetBottom(), makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawEllipse( const Point& pt,short radx,short rady,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(ellipse(m_surface, pt.x, pt.y, radx, rady, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	ellipse(m_surface, pt.x, pt.y, radx, rady, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawEllipseFill( const Point& pt,short radx,short rady,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(ellipsefill(m_surface, pt.x, pt.y, radx, rady, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	ellipsefill(m_surface, pt.x, pt.y, radx, rady, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawArc( const Point& pt,short rad,short start_angle,short end_angle,const Color& color )
{
	fixed ang1;
	fixed ang2;

	ang1 = itofix((start_angle * 256)/360);
	ang2 = itofix((end_angle   * 256)/360);
	
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(arc(m_surface, pt.x, pt.y, ang1, ang2, rad, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	arc(m_surface, pt.x, pt.y, ang1, ang2, rad, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawArcFill( const Point& pt,short rad,short start_angle,short end_angle,const Color& color )
{
	fixed ang1;
	fixed ang2;
	
	ang1 = itofix((start_angle * 256)/360);
	ang2 = itofix((end_angle   * 256)/360);
	
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(arc_fill(m_surface, pt.x, pt.y, ang1, ang2, rad, makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	arc_fill(m_surface, pt.x, pt.y, ang1, ang2, rad, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawText( const Point& pt,const char * text,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(textout_ex(m_surface,font,text,pt.x,pt.y,makecol(color.GetRed(), color.GetGreen(), color.GetBlue()),-1),color.GetAlpha());
		return;
	}
	textout_ex(m_surface,font,text,pt.x,pt.y,makecol(color.GetRed(), color.GetGreen(), color.GetBlue()),-1);
}

void AllegroGraphics::DrawTriangle( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	int col = makecol(color.GetRed(), color.GetGreen(), color.GetBlue());

	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA
		(
		line(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, col);
		line(m_surface, pt2.x, pt2.y, pt3.x, pt3.y, col);
		line(m_surface, pt3.x, pt3.y, pt1.x, pt1.y, col)	
		,color.GetAlpha());
		return;
	}
	
	line(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, col);
	line(m_surface, pt2.x, pt2.y, pt3.x, pt3.y, col);
	line(m_surface, pt3.x, pt3.y, pt1.x, pt1.y, col);
}

void AllegroGraphics::DrawTriangleFill( const Point& pt1,const Point& pt2,const Point& pt3,const Color& color )
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(triangle(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,makecol(color.GetRed(), color.GetGreen(), color.GetBlue())),color.GetAlpha());
		return;
	}
	triangle(m_surface, pt1.x, pt1.y, pt2.x, pt2.y, pt3.x, pt3.y,makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
}

void AllegroGraphics::DrawPolygon( const Point * pts,int n,const Color& color )
{
	if(n < 3)
		return;

	int col = makecol(color.GetRed(), color.GetGreen(), color.GetBlue());

	const Point  * pt1;
	const Point  * pt2;

	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA
		(
			pt1 = &pts[0];
			for(int i = 1; i < n; i++)
			{
				pt2 = &pts[i];
				line(m_surface, pt1->x, pt1->y, pt2->x, pt2->y, col);
				pt1 = pt2;
			}
			pt2 = &pts[0];
			line(m_surface, pt1->x, pt1->y, pt2->x, pt2->y, col)	
		,color.GetAlpha());
		return;
	}

	pt1 = &pts[0];
	for(int i = 1; i < n; i++)
	{
		pt2 = &pts[i];
		line(m_surface, pt1->x, pt1->y, pt2->x, pt2->y, col);
		pt1 = pt2;
	}
	pt2 = &pts[0];
	line(m_surface, pt1->x, pt1->y, pt2->x, pt2->y, col);
}

void AllegroGraphics::DrawPolygonFill( const Point * pts,int n,const Color& color )
{
	if(n < 3)
		return;

	int col = makecol(color.GetRed(), color.GetGreen(), color.GetBlue());

	int * arr_pts = new int[n * 2];
	int idx = 0;
	for(int i = 0; i < n; i ++)
	{
		const Point & pt = pts[i];

		arr_pts[idx]     = pt.x;
		arr_pts[idx + 1] = pt.y;

		idx += 2;
	}

	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(polygon(m_surface,n,arr_pts,col),color.GetAlpha());
		delete [] arr_pts;
		return;
	}
	polygon(m_surface,n,arr_pts,col);
	delete [] arr_pts;
}

void AllegroGraphics::EnableAntiAlias( bool enable )
{
	/* Does nothing. allegro doesn't support anti-alias */
}

void AllegroGraphics::DrawRoundRect(const Rect& rect,int rad,const Color& color)
{
	int col = makecol(color.GetRed(), color.GetGreen(), color.GetBlue());
	int x = rect.x;
	int y = rect.y;
	int w = rect.width;
	int h = rect.height;


	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA
		(
			arc(m_surface,x + w - rad,y + rad,itofix(0),itofix(64),rad,col);
			hline(m_surface,x + rad + 1, y ,x + w - rad - 1,col);
			
			arc(m_surface,x + rad,y + rad,itofix(64),itofix(128),rad,col);
			vline(m_surface,x ,y + rad + 1,y + h - rad - 1,col);
			
			arc(m_surface,x + rad,y + h - rad,itofix(128),itofix(192),rad,col);
			hline(m_surface,x + rad + 1, y + h,x + w - rad - 1,col);
			
			arc(m_surface,x + w - rad,y + h - rad,itofix(192),itofix(255),rad,col);
			vline(m_surface,x + w,y + h - rad - 1,y + rad + 1,col);
		,color.GetAlpha()
		);
		return;
	}

	arc(m_surface,x + w - rad,y + rad,itofix(0),itofix(64),rad,col);
	hline(m_surface,x + rad + 1, y ,x + w - rad - 1,col);
	
	arc(m_surface,x + rad,y + rad,itofix(64),itofix(128),rad,col);
	vline(m_surface,x ,y + rad + 1,y + h - rad - 1,col);
	
	arc(m_surface,x + rad,y + h - rad,itofix(128),itofix(192),rad,col);
	hline(m_surface,x + rad + 1, y + h,x + w - rad - 1,col);
	
	arc(m_surface,x + w - rad,y + h - rad,itofix(192),itofix(255),rad,col);
	vline(m_surface,x + w,y + h - rad - 1,y + rad + 1,col);
}

void AllegroGraphics::DrawRoundRectFill(const Rect& rect,int rad,const Color& color)
{
	if(color.GetAlpha() != Color::alphaOpaque)
	{
		DRAW_WITH_ALPHA(round_rectfill(m_surface, rect.x, rect.y, rect.width, rect.height,rad,makecol(color.GetRed(),color.GetGreen(),color.GetBlue())),color.GetAlpha());
		return;
	}
	
	round_rectfill(m_surface, rect.x, rect.y, rect.width, rect.height,rad,makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
}
