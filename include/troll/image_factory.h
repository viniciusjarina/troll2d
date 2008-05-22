#ifndef __TROLL_IMAGE_FACTORY_H__
#define __TROLL_IMAGE_FACTORY_H__

namespace Troll
{
	class ImageImpl;

	class ImageFactory
	{
	public:
		static ImageImpl * CreateImage();
	};

}

#endif // __TROLL_IMAGE_FACTORY_H__