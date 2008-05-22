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
	virtual int DrawLine(const Point& ptStart, const Point & ptEnd,const Color& color);
	virtual int DrawCircle(const Point& ptCenter, short radius,const Color& color);

private:
	SDL_Surface * m_surface;
};

}

#endif // __TROLL_SDL_GRAPHICS_H__