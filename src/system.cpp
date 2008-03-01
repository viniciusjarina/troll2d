#include "troll/color.h"
#include "troll/system.h"
#include "troll/system_impl.h"
#include "troll/key_input.h"

#include "troll/interface.h"

using namespace Troll;

SystemImpl* System::m_singleton = 0;

System::System()
{
	
}

bool System::Init()
{
	// TODO:
	/*
	Initializer the KeyInput::m_singleton
	Initalize the System::m_singleton member
	Initialize the Screen::m_singleton member	
	*/
	m_singleton = Troll_AllocSystem();
	KeyInput::Init();

	return true;
}

void System::Cleanup()
{
	KeyInput::Cleanup();
	delete m_singleton;
}


bool System::SetupScreen( int nWidth /*= -1*/,int nHeight /*= -1*/,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ )
{
	return m_singleton->SetupScreen(nWidth,nHeight,fFullScreen,depth);
}

void System::Sleep( int mili )
{
	m_singleton->Sleep(mili);
}