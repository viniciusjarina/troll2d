#include <SDL.h>

#include "troll/surface.h"

#include "troll/sdl_surface.h"
#include "troll/sdl_image.h"


using namespace Troll;


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

/******************* SDLImage class *****************************/

SDLImage::SDLImage()
{
	
}

SDLImage::~SDLImage()
{
	
}

bool SDLImage::LoadImage( const char * sImageFile )
{
	return	m_imageHelper.LoadImage(sImageFile);
}

const Surface & SDLImage::GetSurface() const
{
	return m_imageHelper.GetSurface();	
}

/***************************************************************/

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
	SDL_Surface *image;
	
	// TODO: Use SDL_image to load more formats of image (png, jpeg..etc)
	imagebmp = SDL_LoadBMP(sImageFile);
	if(imagebmp == NULL)
		return false;
	
	/* Convert the image to the video format (maps colors) */
	image = SDL_DisplayFormat(imagebmp);
	
	SDL_FreeSurface(imagebmp);
	
	if (image == NULL)
		return false;
	
	SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,255,0,255));
	
	SDLImageSurfaceImpl * surfaceImpl = new SDLImageSurfaceImpl(image);
	m_imageSurface = new SDLImageSurface(surfaceImpl);
	return true;
}