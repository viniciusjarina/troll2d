// Screen.h: interface for the Screen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCREEN_H__692E113B_B4A5_46A1_9BA9_DE8C97546727__INCLUDED_)
#define AFX_SCREEN_H__692E113B_B4A5_46A1_9BA9_DE8C97546727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace Troll
{

class Surface;

class Screen  
{
public:
	Screen();
	virtual ~Screen();

	virtual Surface * GetSurface() const = 0;
	virtual void Flip() = 0;
};

}// Troll

#endif // !defined(AFX_SCREEN_H__692E113B_B4A5_46A1_9BA9_DE8C97546727__INCLUDED_)
