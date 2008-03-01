#include "troll/interface.h"

#include "troll/allegro_system.h"
#include "troll/allegro_keyinput.h"
#include "troll/allegro_surface.h"

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