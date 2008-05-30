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

// SDLScreen.h: interface for the SDLScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__TROLL2D_SDL_SCREEN_H__)
#define __TROLL2D_SDL_SCREEN_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "troll/screen_impl.h"
#include "troll/surface.h"

namespace Troll
{

class SDLSurface;
class SDLScreen;

class SDLScreenHelper
{
	SDL_Surface * m_nativeSurface;
	Surface * m_screenSurface;
	static int m_screen_bpp;

public:
	static SDLScreen * SetupScreen(int w, int h, int bpp, bool fullscreen);

	Surface & GetSurface() const
	{
		return *m_screenSurface;
	}
	
	void FlipScreen();
	bool CreateScreenSurface(int w, int h,int bpp,bool fullscreen);

	inline static int GetScreenBPP() { return m_screen_bpp; }
	
	SDLScreenHelper();
	virtual ~SDLScreenHelper();
};

class SDLScreen : public ScreenImpl
{
	public:
		SDLScreen(int w, int h,int bpp,bool fullscreen);
		virtual ~SDLScreen();
		
	public:
		
		virtual Surface & GetSurface() const;
		virtual void Flip();
		
	private:
		
		SDLScreenHelper  m_screenHelper;
};
	
}// Troll

#endif // !defined(__TROLL2D_SDL_SCREEN_H__AFX_SDLSCREEN_H__9D690549_482F_4783_852A_E2EA601EF446__INCLUDED_)