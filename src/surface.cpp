
#include "troll/surface.h"
#include "troll/surface_factory.h"
#include "troll/surface_impl.h"

using namespace Troll;

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

void Surface::Blit(const Surface & src,const Point& ptDest/* = Point(0,0)*/,const Rect& rSource /*= Rect(0,0,-1,-1)*/)
{
	m_impl->Blit(*src.m_impl,ptDest,rSource);
}

void Surface::DrawAlpha( const Surface & sprite,const Point& ptDest,unsigned char alpha )
{
	m_impl->DrawAlpha(*sprite.m_impl,ptDest,alpha);
}