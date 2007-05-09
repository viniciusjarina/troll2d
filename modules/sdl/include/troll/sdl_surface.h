// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__SDL_TROLL2D_SURFACE_H__)
#define __SDL_TROLL2D_SURFACE_H__

#include "troll/surface.h"

namespace Troll
{

class SDLSurface  : public Surface
{
public:
	SDLSurface();
	virtual ~SDLSurface();

public:

	virtual int GetHeight() const;
	virtual int GetWidth() const;

	virtual void SetClip(const Rect & rect);
	virtual Rect GetClip() const;
	virtual void ResetClip();

	virtual void Clear(const Color & color = Color::BLACK);
	virtual void Blit(const Surface & src);

protected:

	SDL_Surface	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
