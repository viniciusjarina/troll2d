// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SURFACE_H__)
#define __TROLL2D_SURFACE_H__

#include "troll/basic_geo.h"
#include "troll/color.h"
#include "troll/system.h"

namespace Troll
{

class Surface  
{
public:
	Surface();
	virtual ~Surface();

public:
	virtual bool Create(int width,int height,ColorDepth depth = depthAuto) = 0;

	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;

	virtual void SetClip(const Rect & rect) = 0;
	virtual Rect GetClip() const = 0;
	virtual void ResetClip() = 0;

	virtual void Clear(const Color & color = Color::BLACK) = 0;
	virtual void Blit(const Surface & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1)) = 0;
};

}
#endif // !defined(__TROLL2D_SURFACE_H__)
