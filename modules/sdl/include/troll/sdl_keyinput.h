#ifndef __SDL_TROLL2D_KEYINPUT__
#define __SDL_TROLL2D_KEYINPUT__

#include "troll/key_input.h"

namespace Troll
{
		
	class SDLKeyInput : public KeyInput
	{
	public:
		SDLKeyInput();
		
		bool IsKeyDown(int k);
		bool IsKeyUp(int k);
	};
	
}

#endif//__SDL_TROLL2D_KEYINPUT__
