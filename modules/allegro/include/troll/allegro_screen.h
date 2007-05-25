// AllegroScreen.h: interface for the AllegroScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALLEGROSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_)
#define AFX_ALLEGROSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen.h"

namespace Troll
{


class AllegroSurface;

class AllegroScreen : public Screen  
{
	friend class AllegroSystem;

private:
	AllegroScreen(int w,int h);
	virtual ~AllegroScreen();

public:

	virtual Surface * GetSurface() const;
	virtual void Flip();

private:

	AllegroSurface  * m_surface;
};

}// Troll

#endif // !defined(AFX_ALLEGROSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_)
