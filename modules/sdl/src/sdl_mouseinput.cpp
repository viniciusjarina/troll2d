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

#include "troll/point.h"

#include "troll/sdl_mouseinput.h"

using Troll::Point;
using Troll::SDLMouseInput;


SDLMouseInput::SDLMouseInput():
m_down(0),
m_releaseds(0),
m_presseds(0)
{
}

void SDLMouseInput::Update()
{
	SDL_PumpEvents();

	Uint8 state = SDL_GetMouseState(NULL,NULL);
	m_releaseds = ((~state  ) &   m_down);
	m_presseds  = (( state  ) & (~m_down));
	m_down = state;
}

Point SDLMouseInput::GetPosition() const
{
	Point pt;

	int x,y;

	SDL_GetMouseState(&x,&y);

	pt.x = x;
	pt.y = y;

	return pt;
}

void SDLMouseInput::SetPosition(const Point & pt)
{
	SDL_WarpMouse(pt.x, pt.y);
}

Point SDLMouseInput::GetRelativePosition() const
{
	Point ptDelta;

	int xDelta,yDelta;

	SDL_GetRelativeMouseState(&xDelta,&yDelta);

	ptDelta.x = xDelta;
	ptDelta.y = yDelta;

	return ptDelta;
}


bool SDLMouseInput::IsButtonDown( int button ) const
{
	Uint8 state;
	state = SDL_GetMouseState(NULL,NULL);
	return ((state)&SDL_BUTTON(button + 1)) != 0;
}

bool SDLMouseInput::IsButtonUp( int button ) const
{
	Uint8 state;
	state = SDL_GetMouseState(NULL,NULL);
	return ((state)&SDL_BUTTON(button + 1)) == 0;
}

bool SDLMouseInput::IsButtonReleased( int button ) const
{
	return ((m_releaseds)&SDL_BUTTON(button + 1)) != 0;
}

bool SDLMouseInput::IsButtonPressed( int button ) const
{
	return ((m_presseds)&SDL_BUTTON(button + 1)) != 0;
}
