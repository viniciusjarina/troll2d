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

#include <allegro.h>

#include "troll/key_input.h"
#include "troll/allegro_keyinput.h"

using Troll::Key;
using Troll::AllegroKeyInput;


static char keys_down[KEY_MAX];
static char keys_released[KEY_MAX];
static char keys_pressed[KEY_MAX];

static int MapTroll2Allegro(Key k)
{
	if(k >= Troll::TOTAL_KEYS)
		return 0;

	static const unsigned char keys [Troll::TOTAL_KEYS] =
	{
		0,      // 
		KEY_BACKSPACE,// 	BACKSPACE	
		KEY_TAB,      // 	TAB			
		KEY_ENTER,    // 	RETURN		
		KEY_PAUSE,    // 	PAUSE		
		KEY_ESC,      // 	ESCAPE		
		KEY_SPACE,    // 	SPACE		
		0,			  // 	EXCLAIM		
		0,			  // 	QUOTEDBL	
		0,			  // 	SHARP		
		0,			  // 	DOLLAR		
		0,			  // 	AMPERSAND	
		KEY_QUOTE,	  // 	QUOTE		
		0,			  // 	LEFTPAREN	
		0,			  // 	RIGHTPAREN	
		KEY_ASTERISK, // 	ASTERISK	
		0,			  // 	PLUS		
		KEY_COMMA,    // 	COMMA		
		KEY_MINUS,    // 	MINUS
		KEY_STOP,     // 	PERIOD				
		KEY_SLASH,    // 	SLASH		
		KEY_0,		  // 	ZERO		
		KEY_1,        // 	ONE			
		KEY_2,        // 	TWO			
		KEY_3,        // 	THREE		
		KEY_4,        // 	FOUR		
		KEY_5,        // 	FIVE		
		KEY_6,        // 	SIX			
		KEY_7,        // 	SEVEN		
		KEY_8,        // 	EIGHT		
		KEY_9,        // 	NINE		
		KEY_COLON,    // 	COLON		
		KEY_SEMICOLON,// 	SEMICOLON	
		0,            // 	LESS		
		KEY_EQUALS,   // 	EQUALS		
		0,			  // 	GREATER		
		0,            // 	QUESTION	
		KEY_AT,       // 	AT			
		KEY_A,        // 	A			
		KEY_B,        // 	B			
		KEY_C,        // 	C			
		KEY_D,        // 	D			
		KEY_E,        // 	E			
		KEY_F,        // 	F			
		KEY_G,        // 	G			
		KEY_H,        // 	H			
		KEY_I,        // 	I			
		KEY_J,        // 	J			
		KEY_K,        // 	K			
		KEY_L,        // 	L			
		KEY_M,        // 	M			
		KEY_N,        // 	N			
		KEY_O,        // 	O			
		KEY_P,        // 	P			
		KEY_Q,        // 	Q			
		KEY_R,        // 	R			
		KEY_S,        // 	S			
		KEY_T,        // 	T			
		KEY_U,        // 	U			
		KEY_V,        // 	V			
		KEY_W,        // 	W			
		KEY_X,        // 	X			
		KEY_Y,        // 	Y
		KEY_Z,        // 	Z
		0,			  // 	LEFTBRACKET
		KEY_BACKSLASH,// 	BACKSLASH 
		0,			  //	RIGHTBRACKET	 
		KEY_CIRCUMFLEX,// 	CARET
		0,			  // 	UNDERSCORE		
		KEY_BACKQUOTE,// 	BACKQUOTE
		KEY_DEL,      // 	DELETE	
		KEY_0_PAD,    //    NUMERIC_0
		KEY_1_PAD,    // 	NUMERIC_1		
		KEY_2_PAD,    // 	NUMERIC_2	
		KEY_3_PAD,    // 	NUMERIC_3	
		KEY_4_PAD,    // 	NUMERIC_4	
		KEY_5_PAD,    // 	NUMERIC_5	
		KEY_6_PAD,    // 	NUMERIC_6	
		KEY_7_PAD,    // 	NUMERIC_7	
		KEY_8_PAD,    // 	NUMERIC_8		
		KEY_9_PAD,    // 	NUMERIC_9		
		KEY_DEL_PAD,  // 	NUMERIC_PERI
		KEY_SLASH_PAD,// 	NUMERIC_DIVI
		KEY_ASTERISK, // 	NUMERIC_MULT
		KEY_MINUS_PAD,// 	NUMERIC_MINU
		KEY_PLUS_PAD, // 	NUMERIC_PLUS
		KEY_ENTER_PAD,// 	NUMERIC_ENTE
		0,			  // 	NUMERIC_EQUA
		KEY_UP,       // 	UP		
		KEY_DOWN,     // 	DOWN	
		KEY_RIGHT,    // 	RIGHT		
		KEY_LEFT,     // 	LEFT		
		KEY_INSERT,   // 	INSERT		
		KEY_HOME,     // 	HOME		
		KEY_END,      // 	END			
		KEY_PGUP,     // 	PAGEUP		
		KEY_PGDN,     // 	PAGEDOWN	
		KEY_F1,       // 	F1			
		KEY_F2,       // 	F2			
		KEY_F3,       // 	F3			
		KEY_F4,       // 	F4			
		KEY_F5,       // 	F5			
		KEY_F6,       // 	F6			
		KEY_F7,       // 	F7			
		KEY_F8,       // 	F8			
		KEY_F9,       // 	F9			
		KEY_F10,      // 	F10			
		KEY_F11,      // 	F11				
		KEY_F12,      // 	F12				
		KEY_NUMLOCK,  // 	NUMLOCK		
		KEY_CAPSLOCK, // 	CAPSLOCK	
		KEY_SCRLOCK,  // 	SCROLLOCK	
		KEY_RSHIFT,   // 	RIGHT_SHIFT	
		KEY_LSHIFT,   // 	LEFT_SHIFT	
		KEY_RCONTROL, // 	RIGHT_CTRL	
		KEY_LCONTROL, // 	LEFT_CTRL	
		KEY_ALT,      // 	RIGHT_ALT
		KEY_ALTGR,    // 	LEFT_ALT
	};	

	return keys[ k ];
}

AllegroKeyInput::AllegroKeyInput()
{
	install_keyboard();	
}

void AllegroKeyInput::Update()
{
	if(keyboard_needs_poll())
		poll_keyboard();

	char * p_down  = keys_down;
	char * p_released = keys_released;
	char * p_pressed  = keys_pressed;
	const volatile char * p_keys = key;

	int i = KEY_MAX;

	while(--i)
	{
		*p_released = (!(*p_keys)) && ( (*p_down)); // key is not down and was down previous
		*p_pressed  = ( (*p_keys)) && (!(*p_down)); // key is down and wasn't down previous
		*p_down     = *p_keys; // save current state of key
		
		p_down++;
		p_released++;
		p_pressed++;
		p_keys++;
	}
}

bool AllegroKeyInput::IsKeyDown(Key k) const
{
	int allegro_key;
	allegro_key = MapTroll2Allegro(k);
	if(!allegro_key)
		return false;

	return key[allegro_key] != 0;
}


bool AllegroKeyInput::IsKeyUp(Key k) const
{
	int allegro_key;
	allegro_key = MapTroll2Allegro(k);
	if(!allegro_key)
		return false;
	
	return key[allegro_key] == 0;
}

bool AllegroKeyInput::IsKeyReleased(Key key) const
{
	int allegro_key;
	allegro_key = MapTroll2Allegro(key);
	if(!allegro_key)
		return false;

	return keys_released[allegro_key] != 0;
}

bool AllegroKeyInput::IsKeyPressed(Key key) const
{
	int allegro_key;
	allegro_key = MapTroll2Allegro(key);
	if(!allegro_key)
		return false;
	
	return keys_pressed[allegro_key] != 0;
}

