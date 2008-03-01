#ifndef __SDL_TROLL2D_KEYINPUT__
#define __SDL_TROLL2D_KEYINPUT__

#include "troll/key_input_impl.h"

namespace Troll
{
		
class SDLKeyInput : public KeyInputImpl
{
public:
	SDLKeyInput();
	
	bool IsKeyDown(int k);
	bool IsKeyUp(int k);
};
	
}

#endif//__SDL_TROLL2D_KEYINPUT__
