#include "troll/interface.h"

#include "troll/sdl_system.h"
#include "troll/sdl_keyinput.h"
#include "troll/sdl_surface.h"
#include "troll/sdl_graphics.h"
#include "troll/sdl_image.h"

using namespace Troll;

extern "C" SystemImpl * Troll_AllocSystem()
{
	return new SDLSystem;
}

extern "C" KeyInputImpl * Troll_AllocKeyInput()
{
	return new SDLKeyInput;
}

extern "C" SurfaceImpl * Troll_AllocSurface()
{
	return new SDLSurface;
}

extern "C" GraphicsImpl * Troll_AllocGraphics(SurfaceImpl * surface_impl)
{
	SDLSurface * surface = (SDLSurface *)surface_impl;
	// TODO: use dynamic_cast<> ??
	// or create some method to get SDL_Surface from Surface object
	//		like:
	//			Surface s(100,100);
	//			NativeSurfaceAccessor access(s);
	//			BITMAP * buff = access.GetNativeSurface(); // return NULL in case of Surface is not a AllegroSurface
	//
	
	return new SDLGraphics(surface);
}

extern "C" ImageImpl * Troll_AllocImage()
{
	return new SDLImage;
}