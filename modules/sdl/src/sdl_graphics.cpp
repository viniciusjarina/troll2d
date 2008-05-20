#include <SDL.h>

#include "SDL_gfxPrimitives.h"

#include "troll.h"

#include "troll/graphics.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_graphics.h"

using namespace Troll;

SDLGraphics::SDLGraphics( SDLSurface * surface )
{
	m_surface =  surface->m_surface;
}

int SDLGraphics::DrawLine( const Point& ptStart, const Point & ptEnd,Color color )
{
	return lineRGBA(m_surface,ptStart.x,ptStart.y,ptEnd.x,ptEnd.y,color.GetRed(),color.GetGreen(),color.GetBlue(),color.GetAlpha());
}

int SDLGraphics::DrawCircle( const Point& ptCenter, short radius,Color color )
{
	return 0;
}

