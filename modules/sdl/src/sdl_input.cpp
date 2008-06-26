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

static Uint8 keys_pressed[SDLK_LAST];
static Uint8 keys_relesed[SDLK_LAST];

static int MapTroll2SDL(int k)
{
	if(k >= Key::TOTAL_KEYS)
		return 0;

	static const unsigned char keys [Key::TOTAL_KEYS] =
	{
		0,      // 
		SDLK_BACKSPACE,// 	BACKSPACE	
		SDLK_TAB,      // 	TAB			
		SDLK_RETURN,   // 	RETURN		
		SDLK_PAUSE,    // 	PAUSE		
		SDLK_ESCAPE,   // 	ESCAPE		
		SDLK_SPACE,    // 	SPACE		
		SDLK_EXCLAIM,  // 	EXCLAIM		
		SDLK_QUOTEDBL, // 	QUOTEDBL	
		SDLK_HASH,	   // 	SHARP		
		SDLK_DOLLAR,   // 	DOLLAR		
		SDLK_AMPERSAND,// 	AMPERSAND	
		SDLK_QUOTE,	   // 	QUOTE		
		SDLK_LEFTPAREN,// 	LEFTPAREN	
		SDLK_RIGHTPAREN,// 	RIGHTPAREN	
		SDLK_ASTERISK, // 	ASTERISK	
		SDLK_PLUS,     // 	PLUS		
		SDLK_COMMA,    // 	COMMA		
		SDLK_MINUS,    // 	MINUS
		SDLK_PERIOD,   // 	PERIOD				
		SDLK_SLASH,    // 	SLASH		
		SDLK_0,		   // 	ZERO		
		SDLK_1,        // 	ONE			
		SDLK_2,        // 	TWO			
		SDLK_3,        // 	THREE		
		SDLK_4,        // 	FOUR		
		SDLK_5,        // 	FIVE		
		SDLK_6,        // 	SIX			
		SDLK_7,        // 	SEVEN		
		SDLK_8,        // 	EIGHT		
		SDLK_9,        // 	NINE		
		SDLK_COLON,    // 	COLON		
		SDLK_SEMICOLON,// 	SEMICOLON	
		SDLK_LESS,     // 	LESS		
		SDLK_EQUALS,   // 	EQUALS		
		SDLK_GREATER,  // 	GREATER		
		SDLK_QUESTION, // 	QUESTION	
		SDLK_AT,       // 	AT			
		SDLK_a,        // 	A			
		SDLK_b,        // 	B			
		SDLK_c,        // 	C			
		SDLK_d,        // 	D			
		SDLK_e,        // 	E			
		SDLK_f,        // 	F			
		SDLK_g,        // 	G			
		SDLK_h,        // 	H			
		SDLK_i,        // 	I			
		SDLK_j,        // 	J			
		SDLK_k,        // 	K			
		SDLK_l,        // 	L			
		SDLK_m,        // 	M			
		SDLK_n,        // 	N			
		SDLK_o,        // 	O			
		SDLK_p,        // 	P			
		SDLK_q,        // 	Q			
		SDLK_r,        // 	R			
		SDLK_s,        // 	S			
		SDLK_t,        // 	T			
		SDLK_u,        // 	U			
		SDLK_v,        // 	V			
		SDLK_w,        // 	W			
		SDLK_x,        // 	X			
		SDLK_y,        // 	Y
		SDLK_z,        // 	Z
		SDLK_LEFTBRACKET,// LEFTBRACKET
		SDLK_BACKSLASH,// 	BACKSLASH 
		SDLK_RIGHTBRACKET,//RIGHTBRACKET	 
		SDLK_CARET,     // 	CARET
		SDLK_UNDERSCORE,// 	UNDERSCORE		
		SDLK_BACKQUOTE, // 	BACKQUOTE
		SDLK_DELETE,    // 	DELETE	
		SDLK_KP0,    //     NUMERIC_0
		SDLK_KP1,    // 	NUMERIC_1		
		SDLK_KP2,    // 	NUMERIC_2	
		SDLK_KP3,    // 	NUMERIC_3	
		SDLK_KP4,    // 	NUMERIC_4	
		SDLK_KP5,    // 	NUMERIC_5	
		SDLK_KP6,    // 	NUMERIC_6	
		SDLK_KP7,    // 	NUMERIC_7	
		SDLK_KP8,    // 	NUMERIC_8		
		SDLK_KP9,    // 	NUMERIC_9		
		SDLK_KP_PERIOD,// 	NUMERIC_PERI
		SDLK_KP_DIVIDE,// 	NUMERIC_DIVI
		SDLK_KP_MULTIPLY,//	NUMERIC_MULT
		SDLK_KP_MINUS,// 	NUMERIC_MINU
		SDLK_KP_PLUS, // 	NUMERIC_PLUS
		SDLK_KP_ENTER,// 	NUMERIC_ENTE
		SDLK_KP_EQUALS,// 	NUMERIC_EQUA
		TROLL_SDL_UP_KEY,//	UP		
		SDLK_DOWN,     // 	DOWN	
		SDLK_RIGHT,    // 	RIGHT		
		SDLK_LEFT,     // 	LEFT		
		SDLK_INSERT,   // 	INSERT		
		SDLK_HOME,     // 	HOME		
		SDLK_END,      // 	END			
		SDLK_PAGEUP,   // 	PAGEUP		
		SDLK_PAGEDOWN, // 	PAGEDOWN	
		SDLK_F1,       // 	F1			
		SDLK_F2,       // 	F2			
		SDLK_F3,       // 	F3			
		SDLK_F4,       // 	F4			
		SDLK_F5,       // 	F5			
		SDLK_F6,       // 	F6			
		SDLK_F7,       // 	F7			
		SDLK_F8,       // 	F8			
		SDLK_F9,       // 	F9			
		SDLK_F10,      // 	F10			
		SDLK_F11,      // 	F11				
		SDLK_F12,      // 	F12				
		SDLK_NUMLOCK,  // 	NUMLOCK		
		SDLK_CAPSLOCK, // 	CAPSLOCK	
		SDLK_SCROLLOCK,// 	SCROLLOCK	
		SDLK_RSHIFT,   // 	RIGHT_SHIFT	
		SDLK_LSHIFT,   // 	LEFT_SHIFT	
		SDLK_RCTRL, //	RIGHT_CTRL	
		SDLK_LCTRL, // 	LEFT_CTRL	
		SDLK_RALT,  // 	RIGHT_ALT
		SDLK_LALT,  // 	LEFT_ALT
	};	

	return keys[ k ];
}

SDLKeyInput::SDLKeyInput()
{
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL);
}

void SDLKeyInput::Update()
{
	SDL_PumpEvents();

	Uint8 * p_pressed  = keys_pressed;
	Uint8 * p_released = keys_relesed;
	const Uint8 * p_keys = SDL_GetKeyState(NULL);
	
	int i = SDLK_LAST;
	
	while(--i)
	{
		*p_released = (!*p_keys) && (*p_pressed);
		*p_pressed = *p_keys;
		
		p_pressed++;
		p_released++;
		p_keys++;
	}
}

bool SDLKeyInput::IsKeyDown(int k) const
{
	int sdl_key;
	sdl_key = MapTroll2SDL(k);
	if(!sdl_key)
		return false;

	Uint8 *keystate = SDL_GetKeyState(NULL);	
	
	return keystate[sdl_key] != 0;
}


bool SDLKeyInput::IsKeyUp(int k) const
{
	int sdl_key;
	sdl_key = MapTroll2SDL(k);
	if(!sdl_key)
		return false;
	
	Uint8 *keystate = SDL_GetKeyState(NULL);	
	
	return keystate[sdl_key] == 0;
}

bool SDLKeyInput::IsKeyReleased(int key) const
{
	int sdl_key;
	sdl_key = MapTroll2SDL(key);
	if(!sdl_key)
		return false;
	
	return keys_relesed[sdl_key] != 0;
}

