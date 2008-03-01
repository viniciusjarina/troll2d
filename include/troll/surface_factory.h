#ifndef __TROLL_SURFACE_FACTORY_H__
#define __TROLL_SURFACE_FACTORY_H__

namespace Troll
{

class SurfaceImpl;

class SurfaceFactory
{

public:
	static SurfaceImpl * CreateSurface();
	
};

}

#endif // __TROLL_SURFACE_FACTORY_H__