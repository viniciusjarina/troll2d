
#ifndef __TROLL_ALLEGRO_GRAPHICS_H__
#define __TROLL_ALLEGRO_GRAPHICS_H__

#include "troll/graphics_impl.h"

namespace Troll
{

class AllegroGraphics: public GraphicsImpl
{
public:
	AllegroGraphics(AllegroSurface * surface);
protected:
	virtual int DrawLine(const Point& ptStart, const Point & ptEnd,const Color& color);
	virtual int DrawCircle(const Point& ptCenter, short radius,const Color& color);

private:
	BITMAP * m_surface;
};

}

#endif // __TROLL_ALLEGRO_GRAPHICS_H__