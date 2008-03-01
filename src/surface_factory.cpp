#include "troll/surface_factory.h"
#include "troll/surface_impl.h"

#include "troll/interface.h"


using namespace Troll;

SurfaceImpl * SurfaceFactory::CreateSurface()
{
	return Troll_AllocSurface();
}