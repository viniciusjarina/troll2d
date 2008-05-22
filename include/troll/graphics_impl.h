#ifndef __GRAPHICS_IMPL_H__
#define __GRAPHICS_IMPL_H__

#include "troll/basic_geo.h"
#include "troll/color.h"

namespace Troll
{
	class SurfaceImpl;

	class GraphicsImpl
	{
	public:
		GraphicsImpl();
		virtual ~GraphicsImpl();

	public:
		virtual int DrawLine(const Point& ptStart, const Point & ptEnd,const Color& color) = 0;
		virtual int DrawCircle(const Point& ptCenter, short radius,const Color& color) = 0;
	};
}

#endif // __GRAPHICS_IMPL_H__