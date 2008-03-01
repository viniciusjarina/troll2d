#ifndef __TROLL_SCREEN_H__
#define __TROLL_SCREEN_H__

namespace Troll
{

class ScreenImpl;
class Surface;

class Screen
{
private:
	Screen();

	static ScreenImpl * m_singleton;

public:
	static void SetSingleton(ScreenImpl * impl)
	{// TODO: Remove this method
		m_singleton = impl;
	}
	/* REVIEW: What is better, static functions or a GetSingleton() function??
	 Personally I prefer static
	e.g

    Surface & s = Screen::GetSurface(); // very clean

	Surface & s = Screen::getSingleton().GetSurface(); // to much dots :P 	

    */
	static Surface & GetSurface();

	static void Flip();
};

}

#endif