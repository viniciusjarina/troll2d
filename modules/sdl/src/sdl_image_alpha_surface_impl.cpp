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

#include "sprig.h"

#include "troll/surface.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_image.h"

#include "troll/sdl_image_surface_impl.h"
#include "troll/sdl_image_alpha_surface_impl.h"

using Troll::Point;
using Troll::Rect;

using Troll::Surface;

using Troll::SurfaceImpl;

using Troll::SDLSurface;
using Troll::SDLImageSurfaceHelper;

using Troll::SDLImageAlphaSurfaceImpl;




void SDLImageAlphaSurfaceImpl::DrawStretch( SurfaceImpl & destination,const Rect& rcDest,const Rect& rSource /*= Rect(0,0,-1,-1)*/ ) const
{
	SDL_Rect rect1;
	SDL_Rect rect2;
	
	int width;
	int height;
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	if(rSource.width < 0)
		width = source->w;
	else
		width = rSource.width;
	
	if(rSource.height < 0)
		height = source->h;
	else
		height = rSource.height;
	
	rect1.x = rSource.x;
	rect1.y = rSource.y;
	rect1.h = height;
	rect1.w = width;
	
	rect2.x = rcDest.x;
	rect2.y = rcDest.y;
	rect2.h = rcDest.height;
	rect2.w = rcDest.width;
	
	float zoomx = ((float)rect2.w/(float)rect1.w);
	float zoomy = ((float)rect2.h/(float)rect1.h);
	
	// TODO: Found a better (faster) way to transform surfaces, considering colokey+alpha 
	SPG_TransformSurface(source,dest,0.0f,zoomx,zoomy,0,0,rect2.x,rect2.y,SPG_TBLEND|SPG_TAA);
}

void SDLImageAlphaSurfaceImpl::DrawAlpha( SurfaceImpl & destination,const Point& ptDest /*= Point(0,0)*/,unsigned char alpha /*= 128*/ ) const
{
	SDL_Rect rect1;
	SDL_Rect rect2;
	
	SDL_Surface * source = m_surface;
	SDL_Surface * dest = ((SDLSurface *)&destination)->m_surface;
	
	rect1.x = 0;
	rect1.y = 0;
	rect1.h = source->h;
	rect1.w = source->w;
	
	rect2.x = ptDest.x;
	rect2.y = ptDest.y;
	rect2.h = source->h;
	rect2.w = source->w;
	
	SDL_SetAlpha(source,SDL_SRCALPHA,alpha);
	SPG_Blit(source,&rect1,dest,&rect2);
}