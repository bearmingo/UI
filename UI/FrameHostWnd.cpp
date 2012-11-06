#include "FrameHostWnd.h"

#include <Windows.h>

#include "View.h"

#include "GraphicsContext.h"
#include "Color.h"

namespace UI {


LRESULT FrameHostWnd::handleMessage( UINT msg, WPARAM wparam /*= 0*/, LPARAM lparam /*= 0*/ )
{

	return __super::handleMessage(msg, wparam, lparam);
}

}