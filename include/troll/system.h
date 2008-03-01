#if !defined(__TROLL_SYSTEM_H__)
#define __TROLL_SYSTEM_H__

namespace Troll
{

class SystemImpl;


class System
{
private:
	System();

	static SystemImpl * m_singleton;
public:
	static bool Init();
	static void Cleanup();

	static bool SetupScreen(int nWidth = -1,int nHeight = -1,bool fFullScreen = false,ColorDepth depth = depthAuto);
	static void Sleep(int mili);
};




}



#endif // __TROLL_SYSTEM_H__