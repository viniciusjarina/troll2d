#ifndef __TROLL_GRAPHICS_H__
#define __TROLL_GRAPHICS_H__

namespace Troll
{

class GraphicsImpl;
class Surface;

class Graphics
{
	GraphicsImpl * m_impl;
public:

	Graphics(Surface & surface);
	virtual ~Graphics();

public:

	int DrawLine(const Point& ptStart,const Point& ptEnd,const Color & color);
	int DrawCircle(const Point& pt,short rad,const Color& color);

};




}
#endif //__TROLL_GRAPHICS_H__