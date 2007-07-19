// AllegroScreen.h: interface for the AllegroScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_ALLEGRO_SCREEN_H__)
#define __TROLL2D_ALLEGRO_SCREEN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen.h"

namespace Troll
{


class AllegroSurface;

class AllegroScreen : public Screen  
{
	friend class AllegroSystem;

private:
	AllegroScreen(int w,int h);
	virtual ~AllegroScreen();

public:

	virtual Surface * GetSurface() const;
	virtual void Flip();

private:

	AllegroSurface  * m_surface;
};

}// Troll

#endif // !defined(__TROLL2D_ALLEGRO_SCREEN_H__)
