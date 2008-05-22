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
		friend class GraphicsFactory;

		SurfaceImpl * m_impl; // Interface of implementation

	protected:

		Surface(SurfaceImpl * impl); // Protected ctor (user internally)

	public:
		Surface(); // Default ctor
		Surface(int width,int height,ColorDepth depth = depthAuto);

		virtual ~Surface();
		
	public:
		// Creates a surface with given width and heigh
		bool Create(int width,int height,ColorDepth depth = depthAuto); 
		
		int GetHeight() const; // Get the Height of surface
		int GetWidth() const;  // Get the Width of surface
		
		void SetClip(const Rect & rect); // Set clip rect of surface
		Rect GetClip();					 // Get current clipping rect
		void ResetClip();				 // Reset the clip rect
		
		void Clear(const Color & color = Color::BLACK); // Clean surface with color

		// Blits from the Surface (src) the rect (rSource) into postion (ptDest) of surface
		void Blit(const Surface & src,const Point& ptDest = Point(0,0),const Rect& rSource = Rect(0,0,-1,-1));
		// Draw the entire surface (sprite) at position ptDest with alpha-value (alpha)
		void DrawAlpha(const Surface & sprite,const Point& ptDest = Point(0,0),unsigned char alpha = 128);
	};
	
}
#endif // !defined(__TROLL_SURFACE_IMPL_H__)
