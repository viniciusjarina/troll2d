// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __SDL_TROLL2D_SYSTEM_H__
#define __SDL_TROLL2D_SYSTEM_H__

#include "troll/color.h"
#include "troll/system_impl.h"

namespace Troll
{

class Screen;
class SDLScreen;


class SDLSystem  : public SystemImpl
{
private:
	SDLScreen * m_screen;

public:
	SDLSystem();
	virtual ~SDLSystem();
public:
// Overrides to back-end	
	virtual bool SetupScreen(int nWidth,int nHeight,bool fScreen = false,ColorDepth depth = depthAuto);
	virtual void Sleep(int mili);

	static int GetScreenBPP();
	
};

}

#endif // !defined(__ALLEGRO_TROLL2D_SYSTEM_H__)
