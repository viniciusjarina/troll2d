// Screen.h: interface for the Screen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL_SCREEN_IMPL_H__)
#define __TROLL_SCREEN_IMPL_H__


namespace Troll
{

class Surface;

class ScreenImpl  
{
public:
	ScreenImpl();
	virtual ~ScreenImpl();

	virtual Surface & GetSurface() const = 0;
	virtual void Flip() = 0;
};

}// Troll

#endif // !defined(__TROLL_SCREEN_IMPL_H__)
