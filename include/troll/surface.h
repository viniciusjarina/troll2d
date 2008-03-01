// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL_SURFACE_H__)
#define __TROLL_SURFACE_H__

#include "troll/basic_geo.h"
#include "troll/color.h"


namespace Troll
{
	class SurfaceImpl;

	class Surface
	{
		SurfaceImpl * m_impl;
	protected:

		Surface(SurfaceImpl * impl);

	public:
		Surface();
		Surface(int width,int height,ColorDepth depth = depthAuto);

		virtual ~Surface();
		
	public:
		bool Create(int width,int height,ColorDepth depth = depthAuto);
		
		int GetHeight();
		int GetWidth();
		
		void SetClip(const Rect & rect);
		Rect GetClip();
		void ResetClip();
		
		void Clear(const Color & color = Color::BLACK);
		void Blit(const Surface & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1));
	};
	
}
#endif // !defined(__TROLL_SURFACE_IMPL_H__)
