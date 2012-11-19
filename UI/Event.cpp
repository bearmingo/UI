#include <config.h>
#include <Windows.h>
#include "Event.h"



namespace UI {

bool Event::isKeyboardShiftDown()
{
	return GetKeyState(VK_RSHIFT) < 0 || GetKeyState(VK_LSHIFT) < 0;
}

} //namespace UI
