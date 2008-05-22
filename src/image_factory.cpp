#include "troll/image_factory.h"
#include "troll/image_impl.h"

#include "troll/interface.h"

using namespace Troll;

ImageImpl * ImageFactory::CreateImage()
{
	return Troll_AllocImage();
}