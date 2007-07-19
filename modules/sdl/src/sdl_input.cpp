
#include <SDL.h>

#include "troll/key_input.h"
#include "troll/sdl_keyinput.h"

using namespace Troll;

bool SDLKeyInput::IsKeyDown(int k)
{
	// TODO: a better system of input
	//  THe Ideia is can use a class like
	//  KeyInput::IsKeyDown(Key::ESC)
	//	and the static call internaly the virtual =)
	//	this is just a workaround to begin :P
	//
	SDL_PumpEvents();
	Uint8 *keystate = SDL_GetKeyState(NULL);
	// TODO: Implementar para qualquer caso ( e usar SDL_PeepEvents )
	if(k == Key::ESCAPE)
		return keystate[SDLK_ESCAPE] != 0;
	if(k == Key::LEFT)
		return keystate[SDLK_LEFT] != 0;
	if(k == Key::RIGHT)
		return keystate[SDLK_RIGHT] != 0;
	if(k == Key::RIGHT)
		return keystate[SDLK_RIGHT] != 0;
	if(k == Key::UP)
		return keystate[SDLK_UP] != 0;
	if(k == Key::DOWN)
		return keystate[SDLK_DOWN] != 0;

	
	return false;
}


bool SDLKeyInput::IsKeyUp(int k)
{

	return true;
}

SDLKeyInput::SDLKeyInput()
{
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
}