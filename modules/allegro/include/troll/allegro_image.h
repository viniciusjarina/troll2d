#ifndef __TROLL_ALLEGRO_IMAGE_H__
#define __TROLL_ALLEGRO_IMAGE_H__

#include "troll/image_impl.h"

namespace Troll
{

class Surface;

class AllegroImageSurfaceHelper
{
	Surface * m_imageSurface;

public:
	AllegroImageSurfaceHelper();
	~AllegroImageSurfaceHelper();


	bool LoadImage(const char * sImageFile);


	const Surface & GetSurface() const
	{
		return *m_imageSurface;
	}

};

class AllegroImage : public ImageImpl
{
	AllegroImageSurfaceHelper m_imageHelper;
	
public:
	AllegroImage();
	virtual ~AllegroImage();

public:
	virtual bool LoadImage(const char * sImageFile);
	virtual const Surface & GetSurface() const;

};

}

#endif // __TROLL_ALLEGRO_IMAGE_H__