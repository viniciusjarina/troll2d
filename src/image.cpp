

#include "troll/image.h"
#include "troll/image_impl.h"

#include "troll/image_factory.h"

using namespace Troll;

Image::Image()
{
	m_impl = ImageFactory::CreateImage();
}

Image::Image( const char * sImageFile )
{
	m_impl = ImageFactory::CreateImage();

	m_impl->LoadImage(sImageFile);
}

Image::~Image()
{
	
}

const Surface & Image::GetSurface() const
{
	return m_impl->GetSurface();
}

bool Image::LoadImage( const char * sImageFile )
{
	return m_impl->LoadImage(sImageFile);
}

