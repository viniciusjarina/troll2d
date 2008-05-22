#include <allegro.h>

#include "troll/surface.h"

#include "troll/allegro_surface.h"
#include "troll/allegro_image.h"


using namespace Troll;

class AllegroImageSurfaceImpl : public AllegroSurface
{
public:
	AllegroImageSurfaceImpl(BITMAP * bmp):
	AllegroSurface(bmp)
	{
	}
};

class AllegroImageSurface : public Surface
{
public:
	AllegroImageSurface(AllegroImageSurfaceImpl * impl):
	Surface(impl)  
	{
	}
};


/********** AllegroImage class **************/

AllegroImage::AllegroImage()
{
	
}

AllegroImage::~AllegroImage()
{
	
}

bool AllegroImage::LoadImage( const char * sImageFile )
{
	return m_imageHelper.LoadImage(sImageFile);
}

const Surface & AllegroImage::GetSurface() const
{
	return m_imageHelper.GetSurface();	
}

/*******************************************************************************/
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
	
	AllegroImageSurfaceImpl * surfaceImpl = new AllegroImageSurfaceImpl(bmp_image);
	m_imageSurface = new AllegroImageSurface(surfaceImpl);
	return true;
}	

