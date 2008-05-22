// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL_SURFACE_IMPL_H__)
#define __TROLL_SURFACE_IMPL_H__

#include "troll/basic_geo.h"
#include "troll/color.h"


namespace Troll
{

class SurfaceImpl  
{
public:
	SurfaceImpl();
	virtual ~SurfaceImpl();

public:
	virtual bool Create(int width,int height,ColorDepth depth = depthAuto) = 0;

	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;

	virtual void SetClip(const Rect & rect) = 0;
	virtual Rect GetClip() const = 0;
	virtual void ResetClip() = 0;

	virtual void Clear(const Color & color = Color::BLACK) = 0;
	virtual void Blit(const SurfaceImpl & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1)) = 0;
	virtual void DrawAlpha(const SurfaceImpl & sprite,const Point& ptDest = Point(0,0),unsigned char alpha = 128) = 0;
};

}
#endif // !defined(__TROLL_SURFACE_IMPL_H__)
