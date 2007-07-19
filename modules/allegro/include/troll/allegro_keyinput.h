#ifndef __ALLEGRO_TROLL2D_KEYINPUT__
#define __ALLEGRO_TROLL2D_KEYINPUT__

#include "troll/key_input.h"

namespace Troll
{


class AllegroKeyInput : public KeyInput
{
public:
	AllegroKeyInput();
	
	bool IsKeyDown(int k);
	bool IsKeyUp(int k);
};

}

#endif//__ALLEGRO_TROLL2D_KEYINPUT__
