// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__SDL_TROLL2D_SYSTEM_H__
#define __SDL_TROLL2D_SYSTEM_H__

#include "troll/system.h"

namespace Troll
{
	
class SDLSurface;


class SDLSystem  : public System
{
private:
	SDLSurface * m_pScreenBuffer;

public:
	SDLSystem();
	virtual ~SDLSystem();
public:
	virtual bool Init();
	virtual bool SetupScreen(int nWidth,int nHeight,bool fScreen = false,ColorDepth depth = depthAuto);
	virtual void Destroy();

	Suface * GetScreen() const;
};

}

#endif // !defined(__ALLEGRO_TROLL2D_SYSTEM_H__)
