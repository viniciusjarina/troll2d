// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
#define __ALLEGRO_TROLL2D_SURFACE_H__

namespace Troll
{


class AllegroSurface  
{
public:
	AllegroSurface();
	virtual ~AllegroSurface();

public:

	virtual int GetHeight() const;
	virtual int GetWidth() const;

protected:

	BITMAP	* m_surface;

};

}
#endif // !defined(__ALLEGRO_TROLL2D_SURFACE_H__)
