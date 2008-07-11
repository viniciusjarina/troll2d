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

#include "troll/color.h"
#include "troll/system.h"
#include "troll/system_impl.h"
#include "troll/key_input.h"
#include "troll/mouse_input.h"

#include "troll/interface.h"

using Troll::ColorDepth;

using Troll::SystemImpl;
using Troll::System;

SystemImpl* System::m_singleton = 0;

System::System()
{
	
}

bool System::Init()
{
	m_singleton = Troll_AllocSystem();

	KeyInput::Init(); // Initialize KeyInput
	MouseInput::Init();

	return true;
}

void System::Cleanup()
{
	KeyInput::Cleanup();
	MouseInput::Cleanup();

	delete m_singleton;
}


bool System::SetupScreen( int nWidth /*= -1*/,int nHeight /*= -1*/,bool fFullScreen /*= false*/,ColorDepth depth /*= depthAuto*/ ,int fps /* = 30*/)
{
	return m_singleton->SetupScreen(nWidth,nHeight,fFullScreen,depth,fps);
}

void System::Sleep( int mili )
{
	m_singleton->Sleep(mili);
}

void System::SetScreenTitle( const char * szCaption )
{
	m_singleton->SetScreenTitle(szCaption);
}
