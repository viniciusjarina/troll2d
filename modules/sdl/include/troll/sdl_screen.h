// SDLScreen.h: interface for the SDLScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SDL_SCREEN_H__)
#define __TROLL2D_SDL_SCREEN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen_impl.h"
#include "troll/surface.h"

namespace Troll
{

class SDLSurface;
class SDLScreen;

class SDLScreenHelper
{
	SDL_Surface * m_nativeSurface;
	Surface * m_screenSurface;
	static int m_screen_bpp;

public:
	static SDLScreen * SetupScreen(int w, int h, int bpp, bool fullscreen);

	Surface & GetSurface() const
	{
		return *m_screenSurface;
	}
	
	void FlipScreen();
	bool CreateScreenSurface(int w, int h,int bpp,bool fullscreen);

	inline static int GetScreenBPP() { return m_screen_bpp; }
	
	SDLScreenHelper();
	virtual ~SDLScreenHelper();
};

class SDLScreen : public ScreenImpl
{
	public:
		SDLScreen(int w, int h,int bpp,bool fullscreen);
		virtual ~SDLScreen();
		
	public:
		
		virtual Surface & GetSurface() const;
		virtual void Flip();
		
	private:
		
		SDLScreenHelper  m_screenHelper;
};
	
}// Troll

#endif // !defined(__TROLL2D_SDL_SCREEN_H__AFX_SDLSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_)