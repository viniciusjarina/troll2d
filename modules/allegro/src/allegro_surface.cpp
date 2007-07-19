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

AllegroSurface::AllegroSurface():
m_surface(NULL)
{
}

AllegroSurface::~AllegroSurface()
{
	if(m_surface)
		destroy_bitmap(m_surface);
}

bool AllegroSurface::Create(int width,int height,ColorDepth depth /*= depthAuto*/)
{
	ASSERT(m_surface == NULL);
	if(depth == depthAuto)
		m_surface = create_bitmap(width,height);
	else
		m_surface = create_bitmap_ex(width,height,depth*8);

	
	return true;
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

void AllegroSurface::ResetClip()
{
	Rect r(0,0,m_surface->w,m_surface->h);

	AllegroSurface::SetClip(r);
}

void AllegroSurface::Clear(const Color & color /*= Color::BLACK*/)
{
	clear_to_color(m_surface,makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
}

void AllegroSurface::Blit(const Surface & src,const Point& ptDest /*Point(0,0)*/,const Rect& rSource /*Rect(0,0,-1,-1)*/)
{
	BITMAP * source = ((AllegroSurface *)&src)->m_surface;
	BITMAP * dest = m_surface;
	int width;
	int height;

	if(rSource.width < 0)
		width  = source->w;
	if(rSource.height < 0)
		height = source->h;

	blit(source,dest,rSource.x,rSource.y,ptDest.x,ptDest.y,width,height);
}