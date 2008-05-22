#ifndef __TROLL_IMAGE_IMPL_H__
#define __TROLL_IMAGE_IMPL_H__

namespace Troll
{


class Surface;

class ImageImpl
{
public:
	ImageImpl();
	virtual ~ImageImpl();

public:
	virtual bool LoadImage(const char * sImageFile) = 0;
	virtual const Surface & GetSurface() const = 0;

};

}

#endif //__TROLL_IMAGE_IMPL_H__
