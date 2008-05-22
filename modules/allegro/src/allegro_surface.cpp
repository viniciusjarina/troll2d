// Surface.cpp: implementation of the Surface class.
//
//////////////////////////////////////////////////////////////////////
#include <allegro.h>


#include "troll/surface.h"
#include "troll/allegro_surface.h"

#include "troll/surface_factory.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

AllegroSurface::AllegroSurface():
m_surface(NULL)
{
}

AllegroSurface::AllegroSurface( BITMAP * surface ):
m_surface(surface)
{
	
}

AllegroSurface::~AllegroSurface()
{
	if(m_surface)
		destroy_bitmap(m_surface);
}

bool AllegroSurface::Create(int width,int height,ColorDepth depth /*= depthAuto*/)
{
	if(m_surface != NULL)
		return false;
	
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

void AllegroSurface::Blit(const SurfaceImpl & src,const Point& ptDest /*Point(0,0)*/,const Rect& rSource /*Rect(0,0,-1,-1)*/)
{
	BITMAP * source = ((AllegroSurface *)&src)->m_surface;
	BITMAP * dest = m_surface;
	int width;
	int height;

	if(rSource.width < 0)
		width  = source->w;
	else
		width = rSource.width;

	if(rSource.height < 0)
		height = source->h;
	else
		width = rSource.width;

	masked_blit(source,dest,rSource.x,rSource.y,ptDest.x,ptDest.y,width,height);
}




void AllegroSurface::DrawAlpha( const SurfaceImpl & sprite,const Point& ptDest /*= Point(0,0)*/,unsigned char alpha /*= 128*/ )
{
	BITMAP * source = ((AllegroSurface *)&sprite)->m_surface;
	BITMAP * dest = m_surface;

	set_trans_blender(0,0,0,alpha);

	draw_trans_sprite(dest,source,ptDest.x,ptDest.y);
}