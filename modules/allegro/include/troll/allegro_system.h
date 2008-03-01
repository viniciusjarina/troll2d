// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined __ALLEGRO_TROLL2D_SYSTEM_H__
#define __ALLEGRO_TROLL2D_SYSTEM_H__

#include "troll/color.h"
#include "troll/system_impl.h"

namespace Troll
{

class Screen;
class AllegroScreen;


class AllegroSystem  : public SystemImpl
{
private:
	AllegroScreen * m_screen;

public:
	AllegroSystem();
	virtual ~AllegroSystem();
	
public:
	
	virtual bool SetupScreen(int nWidth,int nHeight,bool fScreen = false,ColorDepth depth = depthAuto);
	virtual void Sleep(int mili);
};

}

#endif // !defined(__ALLEGRO_TROLL2D_SYSTEM_H__)
