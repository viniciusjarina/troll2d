// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__SDL_TROLL2D_SURFACE_H__)
#define __SDL_TROLL2D_SURFACE_H__

#include "troll/surface_impl.h"

struct SDL_Surface;

namespace Troll
{


class SDLSurface  : public SurfaceImpl
{
protected:
	SDLSurface(::SDL_Surface * screen); //Used only by Screen class

public:
	SDLSurface();
	virtual ~SDLSurface();

public:
	virtual bool Create(int width,int height,ColorDepth depth = depthAuto);

	virtual int GetHeight() const;
	virtual int GetWidth() const;

	virtual void SetClip(const Rect & rect);
	virtual Rect GetClip() const;
	virtual void ResetClip();

	virtual void Clear(const Color & color = Color::INVISIBLE);
	virtual void Blit(const SurfaceImpl & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1));

private:

	SDL_Surface	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
