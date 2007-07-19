// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SDL_TROLL2D_SYSTEM_H__
#define __SDL_TROLL2D_SYSTEM_H__

#include "troll/system.h"

namespace Troll
{
	
class SDLScreen;


class SDLSystem  : public System
{
private:
	SDLScreen * m_screen;
	int	screen_bpp;

	static SDLSystem * m_system;

public:
	SDLSystem();
	virtual ~SDLSystem();
public:
// Overrides to back-end	
	virtual bool SetupScreen(int nWidth,int nHeight,bool fScreen = false,ColorDepth depth = depthAuto);
	virtual void Sleep(int mili);
	
	Screen * GetScreen() const;

//internal use
	inline static int GetSystemDepth() { return m_system->screen_bpp; }
};

}

#endif // !defined(__ALLEGRO_TROLL2D_SYSTEM_H__)
