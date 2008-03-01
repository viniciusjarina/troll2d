#ifndef __TROLL_KEY_INPUT_IMPL__
#define __TROLL_KEY_INPUT_IMPL__

namespace Troll
{
	class KeyInputImpl
	{
	public:
		virtual bool IsKeyUp(int key) = 0;
		virtual bool IsKeyDown(int key) = 0;
	};
}

#endif //__TROLL_KEY_INPUT_IMPL__