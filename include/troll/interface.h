#ifndef __INTERFACE_H__
#define __INTERFACE_H__

namespace Troll
{
	class SystemImpl;
	class KeyInputImpl;
	class SurfaceImpl;
}

#ifdef __cplusplus
 extern "C"
 {
#endif

	 Troll::SystemImpl*		Troll_AllocSystem();
	 Troll::KeyInputImpl*	Troll_AllocKeyInput();
	 Troll::SurfaceImpl*	Troll_AllocSurface();


#ifdef __cplusplus
 }; /* extern "C" */
#endif 


#endif /* __INTERFACE_H__*/