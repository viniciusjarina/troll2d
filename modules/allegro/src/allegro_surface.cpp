// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////
#include <allegro.h>


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

void AllegroSurface::SetClip(const Rect & rect)
{
	set_clip_rect(m_surface, rect.x, rect.y, rect.x + rect.width,rect.y + rect.height);
}

Rect AllegroSurface::GetClip() const
{
	Rect r;
	int x2,y2;
	get_clip_rect(m_surface, &r.x, &r.y,&x2,&y2);
	r.width  = r.x - x2;
	r.height = r.y - y2;
	return r;
}

void AllegroSurface::ResetClip() const
{
	
}

void AllegroSurface::Clear(const Color & color /*= Color::BLACK*/)
{
	clear_to_color(m_surface,makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
}

void AllegroSurface::Blit(const Surface & src)
{
	// TODO : blit or masked_blit
}