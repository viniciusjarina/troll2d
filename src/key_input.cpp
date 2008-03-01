
#include "troll/key_input.h"
#include "troll/key_input_impl.h"

#include "troll/interface.h"

using namespace Troll;


KeyInputImpl * KeyInput::m_singleton = 0; // static member initialization

KeyInput::KeyInput()
{
}

bool KeyInput::IsKeyDown(int key)
{
	return m_singleton->IsKeyDown(key);
}

bool KeyInput::IsKeyUp(int key)
{
	return m_singleton->IsKeyUp(key);
}

void KeyInput::Init()
{
	m_singleton = Troll_AllocKeyInput();
}

void KeyInput::Cleanup()
{
	delete m_singleton;
}