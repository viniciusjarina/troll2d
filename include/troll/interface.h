#ifndef __INTERFACE_H__
#define __INTERFACE_H__

namespace Troll
{
	class SystemImpl;
	class KeyInputImpl;
	class SurfaceImpl;
	class GraphicsImpl;
	class ImageImpl;
}

#ifdef __cplusplus
 extern "C"
 {
#endif

	 Troll::SystemImpl*		Troll_AllocSystem();
	 Troll::KeyInputImpl*	Troll_AllocKeyInput();
	 Troll::SurfaceImpl*	Troll_AllocSurface();
	 Troll::GraphicsImpl*	Troll_AllocGraphics(Troll::SurfaceImpl * surface_impl);
	 Troll::ImageImpl*		Troll_AllocImage();

#ifdef __cplusplus
 }; /* extern "C" */
#endif 


#endif /* __INTERFACE_H__*/