// SystemImpl.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL_SYSTEM_IMPL_H__)
#define __TROLL_SYSTEM_IMPL_H__

namespace Troll
{

class SystemImpl  
{
public:
	SystemImpl();
	virtual ~SystemImpl();

public:
	
	virtual bool SetupScreen(int nWidth,int nHeight,bool fFullScreen = false,ColorDepth depth = depthAuto) = 0;
	virtual void Sleep(int mili) = 0;
};

}

#endif // !defined(__TROLL_SYSTEM_IMPL_H__)
