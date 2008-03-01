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
m_screen(NULL)
{
	allegro_init();
}

AllegroSystem::~AllegroSystem()
{
	if(m_screen != NULL)
		delete m_screen;
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

	if(nHeight == -1 && nWidth == -1)
	{
		nWidth  = 640;
		nHeight = 480;
	}

	// Set palette
	set_palette(desktop_palette);
	set_color_depth(bpp);

	int nMode = fFullScreen ? GFX_AUTODETECT_FULLSCREEN : GFX_AUTODETECT_WINDOWED;
	if (set_gfx_mode(nMode, nWidth, nHeight, 0, 0))
	{
		return false;
	}

	m_screen = new AllegroScreen(nWidth,nHeight);
	
	return true;
}


void AllegroSystem::Sleep( int mili )
{
	rest(mili);
}