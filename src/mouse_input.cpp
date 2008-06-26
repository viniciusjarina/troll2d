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

#include "troll/basic_geo.h"

#include "troll/mouse_input.h"
#include "troll/mouse_input_impl.h"


#include "troll/mouse_input_factory.h"

using namespace Troll;

MouseInputImpl * MouseInput::m_singleton = 0; // static member initialization

MouseInput::MouseInput()
{
}

void MouseInput::Init()
{
	m_singleton = MouseInputFactory::CreateMouseInput();
}

void MouseInput::Cleanup()
{
	delete m_singleton;
}


void MouseInput::Update()
{
	m_singleton->Update();
}

void MouseInput::GetPosition( Point & pt )
{
	m_singleton->GetPosition(pt);
}

void MouseInput::SetPosition(const Point & pt )
{
	m_singleton->SetPosition(pt);
}

void MouseInput::GetRelativePosition( Point & ptDelta )
{
	m_singleton->GetRelativePosition(ptDelta);
}

bool MouseInput::IsButtonDown( int button )
{
	return m_singleton->IsButtonDown(button);
}

bool MouseInput::IsButtonUp( int button )
{
	return m_singleton->IsButtonUp(button);
}

bool MouseInput::IsButtonReleased( int button )
{
	return m_singleton->IsButtonReleased(button);
}

bool MouseInput::IsButtonPressed( int button )
{
	return m_singleton->IsButtonPressed(button);
}
