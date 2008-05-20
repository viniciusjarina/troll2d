#include "troll.h"

#include "troll/graphics_factory.h"
#include "troll/graphics_impl.h"

#include "troll/interface.h"


using namespace Troll;

GraphicsImpl * GraphicsFactory::CreateGraphics(Surface & surface)
{
	return Troll_AllocGraphics(surface.m_impl);
}