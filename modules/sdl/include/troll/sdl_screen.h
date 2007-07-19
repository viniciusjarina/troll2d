// SDLScreen.h: interface for the SDLScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SDL_SCREEN_H__)
#define __TROLL2D_SDL_SCREEN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen.h"

namespace Troll
{

class SDLSurface;
class SDLScreen : public Screen  
{
	friend class SDLSystem;
	
	private:
		SDLScreen(SDL_Surface * screen);
		virtual ~SDLScreen();
		
	public:
		
		virtual Surface * GetSurface() const;
		virtual void Flip();
		
	private:
		
		SDLSurface  * m_surface;
};
	
}// Troll

#endif // !defined(__TROLL2D_SDL_SCREEN_H__AFX_SDLSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_)