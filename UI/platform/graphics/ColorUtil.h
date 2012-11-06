#ifndef __COLORUTIL_H__
#define __COLORUTIL_H__

#include <Windows.h>

#include "Color.h"

typedef DWORD COLORREF;

namespace UI {

inline COLORREF toColorRef(const Color& color)
{
	return RGB(color.red(), color.green(), color.blue());
}

}
#endif /*__COLORUTIL_H__*/

