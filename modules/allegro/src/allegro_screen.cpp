// AllegroScreen.cpp: implementation of the AllegroScreen class.
//
//////////////////////////////////////////////////////////////////////
#include <allegro.h>

#include "troll/allegro_screen.h"
#include "troll/allegro_surface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

AllegroScreen::AllegroScreen(int w,int h)
{
	m_surface = new AllegroSurface;
	m_surface->Create(w,h);
}

AllegroScreen::~AllegroScreen()
{

}

Surface * AllegroScreen::GetSurface() const
{
	return m_surface;
}


void AllegroScreen::Flip()
{
	blit(m_surface->m_surface,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}