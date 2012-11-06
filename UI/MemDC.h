#ifndef __MEMDC_H__
#define __MEMDC_H__

#include <Windows.h>

class MemDC
{
public:
	HDC m_originalDC;
	RECT m_paintRect;
	HBITMAP m_bmp;
	HBITMAP m_oldBmp;
	HDC m_hDC;

	MemDC(HDC hdc, const RECT& rcPaint)
	{
		m_paintRect = rcPaint;
		m_originalDC = hdc;
		m_hDC = ::CreateCompatibleDC(hdc);
		m_bmp = ::CreateCompatibleBitmap(m_originalDC, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top);
		m_oldBmp = (HBITMAP)::SelectObject(m_hDC, m_bmp);
		SetViewportOrgEx(m_hDC, -rcPaint.left, -rcPaint.top, NULL);
	}

	~MemDC()
	{
		::BitBlt(m_originalDC, m_paintRect.left, m_paintRect.top, 
			m_paintRect.right - m_paintRect.left,
			m_paintRect.bottom - m_paintRect.top,
			m_hDC, 
			m_paintRect.left, m_paintRect.top,
			SRCCOPY);
		SelectBitmap(m_hDC, m_oldBmp);
		DeleteObject(m_bmp);
		DeleteObject(m_hDC);
	}
};
#endif /*__MEMDC_H__*/

