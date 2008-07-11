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

#include "troll/point.h"

#include "troll/allegro_mouseinput.h"

using Troll::Point;

using Troll::AllegroMouseInput;


#define ALLEGRO_BUTTON(b) (1<<(b))

AllegroMouseInput::AllegroMouseInput():
m_releaseds(0),
m_down(0),
m_presseds(0)
{
	install_mouse();
}

void AllegroMouseInput::Update()
{
	if(mouse_needs_poll())
		poll_mouse();

	m_releaseds = ((~mouse_b) &   m_down);
	m_presseds  = (( mouse_b) & (~m_down));
	m_down = mouse_b;
}

void AllegroMouseInput::GetPosition( Point & pt ) const
{
	pt.x = mouse_x;
	pt.y = mouse_y;
}

void AllegroMouseInput::SetPosition(const Point & pt)
{
	position_mouse(pt.x, pt.y);
}

void AllegroMouseInput::GetRelativePosition( Point & ptDelta ) const
{
	int delta_x;
	int delta_y;

	get_mouse_mickeys(&delta_x,&delta_y);

	ptDelta.x = delta_x;
	ptDelta.y = delta_y;
}

bool AllegroMouseInput::IsButtonDown( int button ) const
{
	return (mouse_b & ALLEGRO_BUTTON(button)) != 0;
}

bool AllegroMouseInput::IsButtonUp( int button ) const
{
	return !(mouse_b & ALLEGRO_BUTTON(button)) != 0;
}

bool AllegroMouseInput::IsButtonReleased( int button ) const
{
	return (m_releaseds & ALLEGRO_BUTTON(button)) != 0;
}

bool AllegroMouseInput::IsButtonPressed( int button ) const
{
	return (m_presseds & ALLEGRO_BUTTON(button)) != 0;
}
