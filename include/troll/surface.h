// Surface.h: interface for the Surface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SURFACE_H__)
#define __TROLL2D_SURFACE_H__

namespace Troll
{


class Surface  
{
public:
	Surface();
	virtual ~Surface();

public:

	virtual int GetHeight() const = 0;
	virtual int GetWidth() const = 0;

};

}
#endif // !defined(__TROLL2D_SURFACE_H__)
