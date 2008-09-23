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

#include <math.h>

#include <allegro.h>

#include "aastr2/aastr.h"
#include "aastr2/round.h"

#include "troll/surface.h"

#include "troll/allegro_surface.h"
#include "troll/allegro_image.h"

#include "troll/surface.h"

#include "troll/allegro_image_surface_impl.h"
#include "troll/allegro_image_alpha_surface_impl.h"

using Troll::Point;
using Troll::Rect;

using Troll::Surface;
using Troll::SurfaceImpl;

using Troll::AllegroSurface;
using Troll::AllegroImageSurfaceHelper;

using Troll::AllegroImageSurfaceImpl;
using Troll::AllegroImageAlphaSurfaceImpl;


static int allegro_bitmap_has_alpha(BITMAP *bmp)
{
	int x, y, c;
	
	if (bitmap_color_depth(bmp) != 32)
		return FALSE;
	
	for (y = 0; y < bmp->h; y++) {
		for (x = 0; x < bmp->w; x++) {
			c = getpixel(bmp, x, y);
			if (geta32(c))
				return TRUE;
		}
	}
	return FALSE;
}

class AllegroImageSurface : public Surface
{
public:
	AllegroImageSurface(AllegroImageSurfaceImpl * impl):
	Surface(impl)  
	{
	}
};

// AllegroImageSurfaceHelper:
// This class provide help to associate Image object with Surface object

AllegroImageSurfaceHelper::AllegroImageSurfaceHelper():
m_imageSurface(NULL)
{
}

AllegroImageSurfaceHelper::~AllegroImageSurfaceHelper()
{
	if(m_imageSurface)
		delete m_imageSurface;
}

bool AllegroImageSurfaceHelper::LoadImage( const char * sImageFile )
{
	PALETTE palette;
	BITMAP * bmp_image = load_bitmap(sImageFile, palette);
	
	if (!bmp_image)
		return false;

	AllegroImageSurfaceImpl * surfaceImpl;

	if(allegro_bitmap_has_alpha(bmp_image))
		surfaceImpl = new AllegroImageAlphaSurfaceImpl(bmp_image);
	else
		surfaceImpl = new AllegroImageSurfaceImpl(bmp_image);

	m_imageSurface = new AllegroImageSurface(surfaceImpl);
	return true;
}	

