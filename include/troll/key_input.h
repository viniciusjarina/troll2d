#ifndef __TROLL_KEY_INPUT__
#define __TROLL_KEY_INPUT__

namespace Troll
{
	class Key
	{
	public:
		enum EnumKey
		{
			SPACE,
			TAB,
			ENTER,
			LEFT_ALT,
			RIGHT_ALT,
			LEFT_SHIFT,
			RIGHT_SHIFT,
			LEFT_CONTROL,
			RIGHT_CONTROL,
			LEFT_META,
			RIGHT_META,
			INSERT,
			HOME,
			PAGE_UP,
			XDELETE,
			END,
			PAGE_DOWN,
			ESCAPE,
			CAPS_LOCK,
			BACKSPACE,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			PAUSE,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};
	};

	class KeyInputImpl;

	class KeyInput
	{
	private:
		KeyInput();

		static KeyInputImpl * m_singleton;

	public:
		static void Init();
		static void Cleanup();

		static bool IsKeyUp(int key);
		static bool IsKeyDown(int key);
	};
}

#endif //__TROLL_KEY_INPUT__