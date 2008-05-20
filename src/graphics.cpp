
#include "troll.h"

#include "troll/graphics.h"
#include "troll/graphics_impl.h"

#include "troll/graphics_factory.h"


using namespace Troll;

Graphics::Graphics( Surface & surface )
{
	m_impl = GraphicsFactory::CreateGraphics(surface);
}

Graphics::~Graphics()
{
	if(m_impl)
		delete m_impl;
}

int Graphics::DrawLine( const Point& ptStart, const Point & ptEnd,const Color& color )
{
	return m_impl->DrawLine(ptStart,ptEnd,color);
}

int Graphics::DrawCircle( const Point& pt,short rad, const Color& color )
{
	return m_impl->DrawCircle(pt, rad, color);
}

