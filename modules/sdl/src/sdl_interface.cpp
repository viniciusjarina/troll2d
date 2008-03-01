#include "troll/interface.h"

#include "troll/sdl_system.h"
#include "troll/sdl_keyinput.h"
#include "troll/sdl_surface.h"

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