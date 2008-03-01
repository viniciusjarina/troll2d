

#include "troll/screen.h"
#include "troll/screen_impl.h"

using namespace Troll;


ScreenImpl * Screen::m_singleton = 0; // static member initialization

Screen::Screen()
{

}

Surface & Screen::GetSurface()
{
	return m_singleton->GetSurface();
}

void Screen::Flip()
{
	m_singleton->Flip();
}
