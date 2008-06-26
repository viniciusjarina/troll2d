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

// FPS sync was inspired in the article http://wiki.allegro.cc/Timers

volatile int ticks = 0;
void ticker()
{
        ticks++;
}
END_OF_FUNCTION(ticker)

volatile int game_time = 0;//the new time keeping variable

void game_time_ticker()
{
	game_time++;
}
END_OF_FUNCTION(game_time_ticker)


static int fps = 0;//how many total frames we have done last second
static int frames_done = 0;//how many frames we have done so far this second
static int old_time = 0;//the last time we updated our fps variable

using namespace Troll;

AllegroScreen::AllegroScreen(int w,int h,int nFPS)
{
	m_screenHelper.CreateScreenSurface(w,h,nFPS);

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

bool AllegroScreen::SkipFrame()
{
	return m_screenHelper.SkipFrame();
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

AllegroScreenHelper::AllegroScreenHelper():
m_nativeSurface(NULL),
m_screenSurface(NULL),
m_nFPS(60),
old_ticks(0),
m_fShowCursor(true)
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


	if(game_time >= old_time + 10)//i.e. a second has passed since we last counted the frames
	{
		fps = frames_done;//update the fps
		frames_done = 0;//reset the frames done
		old_time += 10;
    }
	if(m_fShowCursor)
	{
		show_mouse(m_nativeSurface);
		blit(m_nativeSurface,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		show_mouse(NULL);
	}
	else
	{
		blit(m_nativeSurface,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	
	frames_done++;//we drew a frame!
}

void AllegroScreenHelper::CreateScreenSurface( int w, int h , int fps)
{
	LOCK_VARIABLE(ticks);
	LOCK_FUNCTION(ticker);
	install_int_ex(ticker, BPS_TO_TIMER(fps));
	
	LOCK_VARIABLE(game_time);
	LOCK_FUNCTION(game_time_ticker);
	install_int_ex(game_time_ticker, BPS_TO_TIMER(10));//i.e. game_time is in tenths of seconds
	
    
	// TODO: create_video_bitmap?  is really necessary?
	BITMAP * buffer = create_bitmap(w ,h);

	AllegroScreenSurfaceImpl * pAllegroSurfaceImpl = new AllegroScreenSurfaceImpl(buffer);
	Surface * pSurface = new AllegroScreenSurface(pAllegroSurfaceImpl);
	
	m_nativeSurface = buffer;
	m_screenSurface = pSurface;
	m_nFPS = fps;
}

void AllegroScreenHelper::StartFrame()
{
	while(ticks == 0)
	{
		rest(100 / m_nFPS);
	}

	if(ticks > 0)
	{
		old_ticks = ticks;
	}
}

bool AllegroScreenHelper::SkipFrame()
{
	if(ticks > 0)
	{
		ticks--;
		if(old_ticks <= ticks)
		{
			return false;
		}
		return ticks > 0;
	}
	return false;
}

int AllegroScreen::GetFPS() const
{
	return m_screenHelper.GetFPS();
}

void AllegroScreen::StartFrame()
{
	m_screenHelper.StartFrame();
}


void Troll::AllegroScreen::ShowCursor(bool show)
{
	m_screenHelper.ShowCursor(show);
}