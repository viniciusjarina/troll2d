/*
 *
 *  ______             ___    ___      
 * /\__  _\           /\_ \  /\_ \     
 * \/_/\ \/ _ __   ___\//\ \ \//\ \    
 *    \ \ \/\`'__\/ __`\\ \ \  \ \ \   
 *     \ \ \ \ \//\ \L\ \\_\ \_ \_\ \_ 
 *      \ \_\ \_\\ \____//\____\/\____\
 *       \/_/\/_/ \/___/ \/____/\/____/
 *
 * Copyright (c) 2008, JarinSoft
 * All rights reserved.
 *
 * Vinicius Jarina (viniciusjarina@gmail.com)
 *
 * Visit: http://troll2d.googlecode.com
 *
 * Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the JarinSoft nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JarinSoft ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL JARINSOFT BE LIABLE FOR ANY
 *   DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <SDL.h>

#include "troll/key_input.h"
#include "troll/sdl_keyinput.h"

using namespace Troll;
// Map correct keys for each plattform

#if defined(_WIN32_WCE) // In Windows CE misteriosly the Key Up is mapped to SDLK_KP7
	#define TROLL_SDL_UP_KEY    SDLK_KP7 
#else
	#define TROLL_SDL_UP_KEY    SDLK_UP
#endif

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
	// TODO: Implement better key mapping

	if(k == Key::ESCAPE)
		return keystate[SDLK_ESCAPE] != 0;
	else if(k == Key::ENTER)
		return keystate[SDLK_RETURN] != 0;
	else if(k == Key::LEFT)
		return keystate[SDLK_LEFT] != 0;
	else if(k == Key::RIGHT)
		return keystate[SDLK_RIGHT] != 0;
	else if(k == Key::UP)
		return keystate[TROLL_SDL_UP_KEY] != 0;
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