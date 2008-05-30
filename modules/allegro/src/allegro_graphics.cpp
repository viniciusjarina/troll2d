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


using namespace Troll;

AllegroGraphics::AllegroGraphics(AllegroSurface * surface)
{
	m_surface =  surface->m_surface;
}

int AllegroGraphics::DrawPixel(const Point& pt,const Color & color)
{
	putpixel(m_surface, pt.x, pt.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color& color )
{
	line(m_surface, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawCircle( const Point& ptCenter, short radius,const Color& color )
{
	// TODO : consider alpha component
	circle(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawCircleFill( const Point& ptCenter, short radius,const Color& color )
{
	// TODO : consider alpha component
	circlefill(m_surface, ptCenter.x, ptCenter.y, radius, makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawRect(const Rect& r,const Color& color)
{
	rect(m_surface, r.x, r.y, r.GetLeft(), r.GetBottom(), makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawRectFill(const Rect& rect,const Color& color)
{
	rectfill(m_surface, rect.x, rect.y,rect.GetLeft(), rect.GetBottom(), makecol(color.GetRed(), color.GetGreen(), color.GetBlue()));
	return 0;
}



