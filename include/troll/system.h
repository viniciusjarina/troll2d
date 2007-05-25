// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SYSTEM_H__)
#define __TROLL2D_SYSTEM_H__

namespace Troll
{


enum ColorDepth
{
	depth1bpp = 1,
	depth2bpp = 2,	
	depth3bpp = 3,
	depth4bpp = 4,
	depthAuto = -1
};

class Surface;
class Screen;

class System  
{
public:
	System();
	virtual ~System();
public:
	virtual bool Init() = 0;
	virtual bool SetupScreen(int nWidth,int nHeight,bool fFullScreen = false,ColorDepth depth = depthAuto) = 0;
	virtual void Destroy() = 0;

	virtual Screen * GetScreen() const = 0;
};

}

#endif // !defined(__TROLL2D_SYSTEM_H__)
