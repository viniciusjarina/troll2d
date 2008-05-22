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