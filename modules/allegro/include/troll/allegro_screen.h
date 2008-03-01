// AllegroScreen.h: interface for the AllegroScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_ALLEGRO_SCREEN_H__)
#define __TROLL2D_ALLEGRO_SCREEN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen_impl.h"
#include "troll/surface.h"

namespace Troll
{


class AllegroSurface;

class AllegroScreenHelper
{
	BITMAP * m_nativeSurface;
	Surface * m_screenSurface;

public:
	
	Surface & GetSurface() const
	{
		return *m_screenSurface;
	}

	void FlipScreen();
	void CreateScreenSurface(int w, int h);

	AllegroScreenHelper();
	virtual ~AllegroScreenHelper();

};

class AllegroScreen : public ScreenImpl
{
public:
	AllegroScreen(int w,int h);
	virtual ~AllegroScreen();

public:

	virtual Surface & GetSurface() const;
	virtual void Flip();

private:

	AllegroScreenHelper m_screenHelper;
};

}// Troll

#endif // !defined(__TROLL2D_ALLEGRO_SCREEN_H__)
