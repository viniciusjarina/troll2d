// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////

#include "troll/surface.h"
#include "troll/allegro_surface.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

AllegroSurface::AllegroSurface()
{

}

AllegroSurface::~AllegroSurface()
{

}

int AllegroSurface::GetHeight() const
{
	ASSERT(m_surface != NULL);
	return m_surface->h;
}

int AllegroSurface::GetWidth() const
{
	ASSERT(m_surface != NULL);
	return m_surface->w;
}