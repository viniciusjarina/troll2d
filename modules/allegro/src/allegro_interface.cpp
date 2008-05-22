#include "troll/interface.h"

#include "troll/allegro_system.h"
#include "troll/allegro_keyinput.h"
#include "troll/allegro_surface.h"
#include "troll/allegro_graphics.h"
#include "troll/allegro_image.h"

using namespace Troll;

extern "C" SystemImpl * Troll_AllocSystem()
{
	return new AllegroSystem;
}

extern "C" KeyInputImpl * Troll_AllocKeyInput()
{
	return new AllegroKeyInput;
}

extern "C" SurfaceImpl * Troll_AllocSurface()
{
	return new AllegroSurface;
}


extern "C" GraphicsImpl * Troll_AllocGraphics(SurfaceImpl * surface_impl)
{
	AllegroSurface * surface = (AllegroSurface *)surface_impl;
	// TODO: use dynamic_cast<> ??
	// or create some method to get BITMAP from Surface object
	//		like:
	//			Surface s(100,100);
	//			NativeSurfaceAccessor access(s);
	//			BITMAP * buff = access.GetNativeSurface(); // return NULL in case of Surface is not a AllegroSurface
	//
	
	return new AllegroGraphics(surface);
}

extern "C" ImageImpl * Troll_AllocImage()
{
	return new AllegroImage;
}