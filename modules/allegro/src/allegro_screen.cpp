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

// AllegroScreen.cpp: implementation of the AllegroScreen class.
//
//////////////////////////////////////////////////////////////////////
#include <allegro.h>

#include "troll/allegro_screen.h"
#include "troll/allegro_surface.h"
#include "troll/screen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

AllegroScreen::AllegroScreen(int w,int h)
{
	m_screenHelper.CreateScreenSurface(w,h);

	Screen::SetSingleton(this);
}

AllegroScreen::~AllegroScreen()
{
	
}

Surface & AllegroScreen::GetSurface() const
{
	return m_screenHelper.GetSurface();
}


void AllegroScreen::Flip()
{
	m_screenHelper.FlipScreen();
}

/********************************/
// Internal class to create a Surface passing BITMAP* (screen) as parameter
class AllegroScreenSurfaceImpl: public AllegroSurface
{
public:
	AllegroScreenSurfaceImpl(BITMAP * surface):
	AllegroSurface(surface)
	{
	}
};

class AllegroScreenSurface: public Surface
{
public:
	AllegroScreenSurface(AllegroScreenSurfaceImpl * impl):
	Surface(impl)
	{
	}
};

AllegroScreenHelper::AllegroScreenHelper()
{
}

AllegroScreenHelper::~AllegroScreenHelper()
{
	if(m_screenSurface)
		delete m_screenSurface;
}

void AllegroScreenHelper::FlipScreen()
{
	// TODO: page flipping (just see the flip example of allegro)
	
	blit(m_nativeSurface,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	vsync();// Is this realy needed?
}

void AllegroScreenHelper::CreateScreenSurface( int w, int h )
{
	// TODO: create_video_bitmap?  is really necessary?
	BITMAP * buffer = create_bitmap(w ,h);

	AllegroScreenSurfaceImpl * pAllegroSurfaceImpl = new AllegroScreenSurfaceImpl(buffer);
	Surface * pSurface = new AllegroScreenSurface(pAllegroSurfaceImpl);
	
	m_nativeSurface = buffer;
	m_screenSurface = pSurface;
}