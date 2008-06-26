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

#ifndef __TROLL_KEY_INPUT__
#define __TROLL_KEY_INPUT__

namespace Troll
{
	class Key
	{
	public:
		enum EnumKey
		{
			BACKSPACE	= 1, // <-
			TAB			= 2, //		
			RETURN		= 3, // Enter
			PAUSE		= 4, 
			ESCAPE		= 5, 
			SPACE		= 6,
			EXCLAIM		= 7,// !
			QUOTEDBL	= 8, // "
			SHARP		= 9, // #
			DOLLAR		= 10,// $
			AMPERSAND	= 11,// &
			QUOTE		= 12,// '
			LEFTPAREN	= 13,// (
			RIGHTPAREN	= 14,// )
			ASTERISK	= 15,// *
			PLUS		= 16,// +
			COMMA		= 17,// ,
			MINUS		= 18,// -
			PERIOD		= 19,// .
			SLASH		= 20,// /
			ZERO		= 21,// 0
			ONE			= 22,// 1
			TWO			= 23,// 2
			THREE		= 24,// 3
			FOUR		= 25,// 4
			FIVE		= 26,// 5
			SIX			= 27,// 6
			SEVEN		= 28,// 7
			EIGHT		= 29,// 8
			NINE		= 30,// 9
			COLON		= 31,// :
			SEMICOLON	= 32,// ;
			LESS		= 33,// <
			EQUALS		= 34,// =
			GREATER		= 35,// >
			QUESTION	= 36,// ?
			AT			= 37,// @
			A			= 38,// A
			B			= 39,// B
			C			= 40,// C
			D			= 41,// D
			E			= 42,// E
			F			= 43,// F
			G			= 44,// G
			H			= 45,// H
			I			= 46,// I
			J			= 47,// J
			K			= 48,// K
			L			= 49,// L
			M			= 50,// M
			N			= 51,// N
			O			= 52,// O
			P			= 53,// P
			Q			= 54,// Q
			R			= 55,// R
			S			= 56,// S
			T			= 57,// T
			U			= 58,// U
			V			= 59,// V
			W			= 60,// W
			X			= 61,// X
			Y			= 62,// Y
			Z			= 63,// Y
			LEFTBRACKET = 64,// {
			BACKSLASH	= 65,// 
			RIGHTBRACKET= 66,// }
			CARET		= 67,// ^
			UNDERSCORE	= 68,// _
			BACKQUOTE	= 69,// `
			DELETE		= 70,
			NUMERIC_0	= 71,
			NUMERIC_1	= 72,
			NUMERIC_2	= 73,
			NUMERIC_3	= 74,
			NUMERIC_4	= 75,
			NUMERIC_5	= 76,
			NUMERIC_6	= 77,
			NUMERIC_7	= 78,
			NUMERIC_8	= 79,
			NUMERIC_9	= 80,
			NUMERIC_PERIOD	= 81,
			NUMERIC_DIVIDE	= 82,
			NUMERIC_MULTIPLY= 83,
			NUMERIC_MINUS	= 84,
			NUMERIC_PLUS	= 85,
			NUMERIC_ENTER	= 86,
			NUMERIC_EQUAL	= 87,
			UP			= 88,
			DOWN		= 89,
			RIGHT		= 90,
			LEFT		= 91,
			INSERT		= 92,
			HOME		= 93,
			END			= 94,
			PAGEUP		= 95,
			PAGEDOWN	= 96,
			F1			= 97,
			F2			= 98,
			F3			= 99,
			F4			= 100,
			F5			= 101,
			F6			= 102,
			F7			= 103,
			F8			= 104,
			F9			= 105,
			F10			= 106,
			F11			= 107,
			F12			= 108,
			NUMLOCK		= 109,
			CAPSLOCK	= 110,
			SCROLLOCK	= 111,
			RIGHT_SHIFT	= 112,
			LEFT_SHIFT	= 113,
			RIGHT_CTRL	= 114,
			LEFT_CTRL	= 115,
			RIGHT_ALT	= 116,
			LEFT_ALT	= 117,
			TOTAL_KEYS	= 118,
		};
	};


	class KeyInputImpl;

	class KeyInput
	{
	private:
		KeyInput();

		static KeyInputImpl * m_singleton;

	public:
		static void Init();
		static void Cleanup();

		static void Update();

		static bool IsKeyUp(int key);
		static bool IsKeyDown(int key);
		static bool IsKeyReleased(int key);
	};
}

#endif //__TROLL_KEY_INPUT__
