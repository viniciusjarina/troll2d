#include <allegro.h>

#include "troll.h"

#include "troll/graphics.h"

#include "troll/allegro_surface.h"
#include "troll/allegro_graphics.h"


using namespace Troll;

AllegroGraphics::AllegroGraphics(AllegroSurface * surface)
{
	m_surface =  surface->m_surface;
}

int AllegroGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,Color color )
{
	line(m_surface,ptStart.x,ptStart.y,ptEnd.x,ptEnd.y,makecol(color.GetRed(),color.GetGreen(),color.GetBlue()));
	return 0;
}

int AllegroGraphics::DrawCircle( const Point& ptCenter, short radius,Color color )
{
	return 0;
}