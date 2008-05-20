// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
#define __ALLEGRO_TROLL2D_SURFACE_H__

#include "troll/surface_impl.h"

struct BITMAP;

namespace Troll
{

class AllegroSurface  : public SurfaceImpl
{
	friend class AllegroGraphics;

protected:
	AllegroSurface(BITMAP * surface);
public:
	AllegroSurface();
	virtual ~AllegroSurface();

public:
	virtual	bool Create(int width,int height,ColorDepth depth = depthAuto);

	virtual int GetHeight() const;
	virtual int GetWidth() const;
	
	virtual void SetClip(const Rect & rect);
	virtual Rect GetClip() const;
	virtual void ResetClip();

	virtual void Clear(const Color & color = Color::BLACK);
	virtual void Blit(const SurfaceImpl & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1));

private:

	BITMAP	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
