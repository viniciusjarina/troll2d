#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace Troll
{

class Surface;
class ImageImpl;

class Image
{
	ImageImpl * m_impl;

public:
	Image();
	Image(const char * sImageFile);

	virtual ~Image();

public:
	bool LoadImage(const char * sImageFile);

	const Surface & GetSurface() const;
};

}

#endif // __IMAGE_H__