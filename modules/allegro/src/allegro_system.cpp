// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////

#include "troll/system.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace Troll;

#include "troll/system.h"
#include "troll/allegro_system.h"

#include <allegro.h>

AllegroSystem::AllegroSystem()
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
	return true;
}

void AllegroSystem::Destroy()
{
	allegro_exit();
}

Suface * AllegroSystem::GetScreen() const
{
	
}