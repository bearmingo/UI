#include "BitmapCache.h"

#include "ColorUtil.h"

namespace UI {

Color BitmapCache::InvalidateBackgroundColor = Color(0xff, 0xff, 0xff, 0xff);

bool BitmapCache::createBitmap( const IntSize& size, const Color& backgroundColor )
{
	HDC hDCDesktop = ::GetDC(NULL);
	HBITMAP hBmpCreate = ::CreateCompatibleBitmap(hDCDesktop, size.width(), size.height());

	m_hbitmap = hBmpCreate;

	if (backgroundColor != InvalidateBackgroundColor) {
		HDC hDCDraw = ::CreateCompatibleDC(hDCDesktop);
		HGDIOBJ hbmpOld = ::SelectObject(hDCDraw, hBmpCreate);
		RECT rcDraw = {0, 0, size.width(), size.height()};
		COLORREF clrOld = ::SetBkColor(hDCDraw, toColorRef(backgroundColor));

		ASSERT(clrOld != CLR_INVALID);
		if (clrOld != CLR_INVALID) {
			::ExtTextOut(hDCDraw, 0, 0, ETO_OPAQUE, &rcDraw, NULL, 0, NULL);
			::SetBkColor(hDCDraw, clrOld);
		}

		::SelectObject(hDCDraw, hbmpOld);
		::DeleteDC(hDCDraw);
	}

	::ReleaseDC(NULL, hDCDesktop);

	return hBmpCreate != NULL;
}

}