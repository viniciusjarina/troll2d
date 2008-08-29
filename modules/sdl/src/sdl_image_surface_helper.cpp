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

#include "SDL_image.h"

#include "troll/surface.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_image.h"

using Troll::Surface;

using Troll::SDLSurface;
using Troll::SDLImageSurfaceHelper;


class SDLImageSurfaceImpl : public SDLSurface
{
public:
	SDLImageSurfaceImpl(SDL_Surface * bmp):SDLSurface(bmp)
	{
	}
};

class SDLImageSurface : public Surface
{
public:
	SDLImageSurface(SDLImageSurfaceImpl * impl):Surface(impl)  
	{
	}
};


SDLImageSurfaceHelper::SDLImageSurfaceHelper():
m_imageSurface(NULL)
{
	
}

SDLImageSurfaceHelper::~SDLImageSurfaceHelper()
{
	if(m_imageSurface)
		delete m_imageSurface;
}

bool SDLImageSurfaceHelper::LoadImage( const char * sImageFile )
{
		/* Load a BMP image into a surface */
	SDL_Surface *imagebmp;
	SDL_Surface *image = NULL;

	bool hasAlpha = false;
	
	imagebmp = IMG_Load(sImageFile);

	if(imagebmp == NULL)
		return false;

	if (imagebmp->format->BitsPerPixel == 32)
	{
		for (int i = 0; i < imagebmp->w * imagebmp->h; ++i)
		{
			Uint8 r, g, b, a;
			SDL_GetRGBA(((Uint32*) imagebmp->pixels)[i],
				imagebmp->format,
				&r, &g, &b, &a);
			
			if (a != 255)
			{
				hasAlpha = true;
				break;
			}
		}
	}

	/* Convert the image to the video format (maps colors) */
	if (hasAlpha)
		image = SDL_DisplayFormatAlpha(imagebmp);
	else
		image = SDL_DisplayFormat(imagebmp);	
	
	if(image != NULL)
	{
		SDL_FreeSurface(imagebmp);
	}
	else
		image = imagebmp;
	
	SDL_SetColorKey(image,SDL_SRCCOLORKEY | SDL_RLEACCEL | SDL_HWACCEL,SDL_MapRGB(image->format,255,0,255));
	
	SDLImageSurfaceImpl * surfaceImpl = new SDLImageSurfaceImpl(image);
	m_imageSurface = new SDLImageSurface(surfaceImpl);
	return true;
}
