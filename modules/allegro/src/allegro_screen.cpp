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
	delete m_surface;
}

Surface * AllegroScreen::GetSurface() const
{
	return m_surface;
}


void AllegroScreen::Flip()
{
	// TODO: page flipping (just see the flip example of allegro)

	blit(m_surface->m_surface,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}