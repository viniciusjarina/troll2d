// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__ALLEGRO_TROLL2D_SYSTEM_H__
#define __ALLEGRO_TROLL2D_SYSTEM_H__

#include "troll/system.h"

namespace Troll
{
	
class AllegroSurface;


class AllegroSystem  : public System
{
private:
	AllegroSurface * m_pScreenBuffer;

public:
	AllegroSystem();
	virtual ~AllegroSystem();
public:
	virtual bool Init();
	virtual bool SetupScreen(int nWidth,int nHeight,bool fScreen = false,ColorDepth depth = depthAuto);
	virtual void Destroy();

	Surface * GetScreen() const;
};

}

#endif // !defined(__ALLEGRO_TROLL2D_SYSTEM_H__)
