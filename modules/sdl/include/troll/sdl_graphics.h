#ifndef __TROLL_SDL_GRAPHICS_H__
#define __TROLL_SDL_GRAPHICS_H__

#include "troll/graphics_impl.h"

namespace Troll
{

class SDLGraphics : public GraphicsImpl
{
public:
	SDLGraphics(SDLSurface * surface);

protected:
	int DrawLine(const Point& ptStart, const Point & ptEnd,Color color);
	int DrawCircle(const Point& ptCenter, short radius,Color color);

private:
	SDL_Surface * m_surface;
};

}

#endif // __TROLL_SDL_GRAPHICS_H__