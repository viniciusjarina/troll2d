#ifndef __TROLL_GRAPHICS_FACTORY_H__
#define __TROLL_GRAPHICS_FACTORY_H__

namespace Troll
{
	
	class GraphicsImpl;
	
	class GraphicsFactory
	{
		
	public:
		static GraphicsImpl * CreateGraphics(Surface & surface);
		
	};
	
}

#endif // __TROLL_SURFACE_FACTORY_H__