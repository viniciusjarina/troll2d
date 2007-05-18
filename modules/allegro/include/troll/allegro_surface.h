// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
#define __ALLEGRO_TROLL2D_SURFACE_H__

#include "troll/surface.h"

namespace Troll
{

class AllegroSurface  : public Surface
{
public:
	AllegroSurface();
	virtual ~AllegroSurface();

public:
	virtual	bool Create(const Size & size);

	virtual int GetHeight() const;
	virtual int GetWidth() const;
	
	virtual void SetClip(const Rect & rect);
	virtual Rect GetClip() const;
	virtual void ResetClip();

	virtual void Clear(const Color & color = Color::BLACK);
	virtual void Blit(const Surface & src);

protected:

	BITMAP	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
