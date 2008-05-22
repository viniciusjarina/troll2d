#ifndef __TROLL_SDL_IMAGE_H__
#define __TROLL_SDL_IMAGE_H__

#include "troll/image_impl.h"

namespace Troll
{

class Surface;
class SDLImageSurfaceHelper
{
	Surface * m_imageSurface;

public:
	SDLImageSurfaceHelper();
	~SDLImageSurfaceHelper();


	bool LoadImage(const char * sImageFile);

	const Surface & GetSurface() const
	{
		return *m_imageSurface;
	}
};

class SDLImage : public ImageImpl
{
	SDLImageSurfaceHelper m_imageHelper;
	
public:
	SDLImage();
	virtual ~SDLImage();

public:
	virtual bool LoadImage(const char * sImageFile);
	virtual const Surface & GetSurface() const;
};

}

#endif // __TROLL_ALLEGRO_IMAGE_H__