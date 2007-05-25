// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




#include <allegro.h>

#include "troll/allegro_screen.h"
#include "troll/allegro_system.h"

using namespace Troll;


AllegroSystem::AllegroSystem():
m_pScreenBuffer(NULL)
{

}

AllegroSystem::~AllegroSystem()
{

}

bool AllegroSystem::Init()
{
	allegro_init();
	return false;
}

bool AllegroSystem::SetupScreen( int nWidth,int nHeight,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ )
{
	int bpp;
	if(depth == depthAuto)
	{
		bpp = desktop_color_depth();
		if (bpp == 0)
		{
			bpp = 16;
		}
	}
	else
	{
		bpp = depth * 8;
	}

	// Set palette
	set_palette(desktop_palette);
	set_color_depth(bpp);

	int nMode = fFullScreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED;
	if (set_gfx_mode(nMode, nWidth, nHeight, 0, 0))
	{
		return false;
	}

	m_pScreenBuffer = new AllegroScreen(nWidth,nHeight);
	return true;
}

void AllegroSystem::Destroy()
{
	if(m_pScreenBuffer != NULL)
		delete m_pScreenBuffer;

	allegro_exit();
}

Screen * AllegroSystem::GetScreen() const
{
	return m_pScreenBuffer;
}