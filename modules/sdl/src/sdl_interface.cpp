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

#include "troll/interface.h"

#include "troll/sdl_system.h"
#include "troll/sdl_keyinput.h"
#include "troll/sdl_mouseinput.h"
#include "troll/sdl_surface.h"
#include "troll/sdl_graphics.h"
#include "troll/sdl_image.h"

using Troll::SystemImpl;
using Troll::KeyInputImpl;
using Troll::MouseInputImpl;
using Troll::SurfaceImpl;
using Troll::GraphicsImpl;
using Troll::ImageImpl;

using Troll::SDLSystem;
using Troll::SDLSurface;
using Troll::SDLKeyInput;
using Troll::SDLMouseInput;
using Troll::SDLGraphics;
using Troll::GraphicsImpl;
using Troll::SDLImage;

extern "C" SystemImpl * Troll_AllocSystem()
{
	return new SDLSystem;
}

extern "C" KeyInputImpl * Troll_AllocKeyInput()
{
	return new SDLKeyInput;
}

extern "C" MouseInputImpl * Troll_AllocMouseInput()
{
	return new SDLMouseInput;
}

extern "C" SurfaceImpl * Troll_AllocSurface()
{
	return new SDLSurface;
}

extern "C" GraphicsImpl * Troll_AllocGraphics(SurfaceImpl * surface_impl)
{
	SDLSurface * surface = (SDLSurface *)surface_impl;
	// TODO: use dynamic_cast<> ??
	// or create some method to get SDL_Surface from Surface object
	//		like:
	//			Surface s(100,100);
	//			NativeSurfaceAccessor access(s);
	//			BITMAP * buff = access.GetNativeSurface(); // return NULL in case of Surface is not a AllegroSurface
	//
	
	return new SDLGraphics(surface);
}

extern "C" ImageImpl * Troll_AllocImage()
{
	return new SDLImage;
}
