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


#include "troll/surface.h"
#include "troll/surface_factory.h"
#include "troll/surface_impl.h"

using Troll::Color;
using Troll::ColorDepth;

using Troll::Point;
using Troll::Rect;

using Troll::SurfaceImpl;
using Troll::SurfaceFactory;
using Troll::Surface;

Surface::Surface()
{
	m_impl = SurfaceFactory::CreateSurface();
}

Surface::Surface( SurfaceImpl * impl ):
m_impl(impl)
{
	
}

Surface::Surface(int width,int height,ColorDepth depth /*= depthAuto*/)
{
	m_impl = SurfaceFactory::CreateSurface();

	m_impl->Create(width,height,depth);
}

Surface::~Surface()
{
	if(m_impl)
		delete m_impl;
}

bool Surface::Create(int width,int height,ColorDepth depth/* = depthAuto*/)
{
	return m_impl->Create(width,height,depth);
}
		
int Surface::GetHeight() const
{
	return m_impl->GetHeight();
}

int Surface::GetWidth() const
{
	return m_impl->GetWidth();
}
		
void Surface::SetClip(const Rect & rect)
{
	m_impl->SetClip(rect);
}

Rect Surface::GetClip()
{
	return m_impl->GetClip();
}

void Surface::ResetClip()
{
	m_impl->ResetClip();
}

void Surface::Clear(const Color & color /*= Color::BLACK*/)
{
	m_impl->Clear(color);
}

void Surface::Draw(const Surface & src,const Point& ptDest/* = Point(0,0)*/,const Rect& rSource /*= Rect(0,0,-1,-1)*/)
{
	src.m_impl->Draw(*m_impl,ptDest,rSource);
}

void Surface::DrawStretch( const Surface & src,const Rect& rcDest /*= Point(0,0)*/,const Rect& rSource /*= Rect(0,0,-1,-1)*/ )
{
	src.m_impl->DrawStretch(*m_impl,rcDest,rSource);
}

void Surface::DrawAlpha( const Surface & sprite,const Point& ptDest,unsigned char alpha )
{
	sprite.m_impl->DrawAlpha(*m_impl,ptDest,alpha);
}

