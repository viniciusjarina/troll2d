
#include <allegro.h>

#include "troll/key_input.h"
#include "troll/allegro_keyinput.h"

using namespace Troll;

bool AllegroKeyInput::IsKeyDown(int k)
{
	// TODO: a better system of input
	//  THe Ideia is can use a class like
	//  KeyInput::IsKeyDown(Key::ESC)
	//	and the static call internaly the virtual =)
	//	this is just a workaround to begin :P
	//
	if(keyboard_needs_poll())
		poll_keyboard();

	if(k == Key::ESCAPE)
		return key[KEY_ESC] != 0;
	if(k == Key::LEFT)
		return key[KEY_LEFT] != 0;
	if(k == Key::RIGHT)
		return key[KEY_RIGHT] != 0;
	if(k == Key::RIGHT)
		return key[KEY_RIGHT] != 0;
	if(k == Key::UP)
		return key[KEY_UP] != 0;
	if(k == Key::DOWN)
		return key[KEY_DOWN] != 0;
	return false;
}


bool AllegroKeyInput::IsKeyUp(int k)
{
	return true;
}

AllegroKeyInput::AllegroKeyInput()
{
	install_keyboard();	
}