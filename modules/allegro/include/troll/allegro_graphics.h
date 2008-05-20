
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
	int DrawLine(const Point& ptStart, const Point & ptEnd,Color color);
	int DrawCircle(const Point& ptCenter, short radius,Color color);

private:
	BITMAP * m_surface;
};

}

#endif // __TROLL_ALLEGRO_GRAPHICS_H__