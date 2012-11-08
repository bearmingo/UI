/********************************************************************
	file base:	WndHost.h
	author:		cgm(cgm@eastcom.com)
	created:	2012/08/24
	
	purpose:	
*********************************************************************/
#ifndef __WNDHOST_H__
#define __WNDHOST_H__

#include <stdint.h>
#include <wtf/Noncopyable.h>
#include <wtf/FastAllocBase.h>
#include <wtf/RefCounted.h>
#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>

#include "Region.h"

#include "ViewTree.h"
#include "Editor.h"

#if PLATFORM(WIN)
typedef HWND__ * HWND;
typedef HIMC__ * HIMC;
#endif

namespace UI {


class WndHost :  public RefCounted<WndHost>
{
	WTF_MAKE_NONCOPYABLE(WndHost);
	WTF_MAKE_FAST_ALLOCATED;
public:

	virtual ~WndHost() {}

	HWND GetHWND() const { return m_hwnd; }
	operator HWND() const { return m_hwnd; }

	bool registerWindowClass();
	bool registerSuperclass();

	void setViewTree(PassRefPtr<ViewTree> viewTree) 
	{
		if (m_viewTree.get())
			m_viewTree->setWndHost(NULL);

		m_viewTree = viewTree;
		m_viewTree->setWndHost(this);

	}

	ViewTree* viewTree() { return m_viewTree.get(); }

	HWND createHost(HWND hwndParent, LPCTSTR lpszName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	HWND createHost(HWND hwndParent, LPCTSTR lpszName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
	
	void WndHost::setTitle(const UChar *title);

	HWND subclass(HWND hWnd);
	void unsubclass();
	void showWindow(bool bShow = true, bool bTakeFocus = true);
	uint32_t showModal();
	void close(uint32_t ret = IDOK);
	void centerWindow(HWND hWndCenter = NULL);
	void setIcon(uint32_t res);

	bool sendMessage(UINT msg, WPARAM wparam = 0L, LPARAM lparam = 0L);
	bool postMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	void resizeClient(int cx = -1, int cy = -1);

	bool clientToScreen(POINT& point);

	IntSize clientSize();

	void invalidateRect(const IntRect&);

	//IME
	HIMC getIMMContext();
	void prepareCandidateWindow(HIMC hInputContext);
	void resetIME();
	void setInputMethodState(bool enable);
	void compositionSelectionChanged(bool hasChanged);
	bool onIMEStartComposition();
	bool onIMEComposition(LPARAM lparam);
	bool onIMEEndComposition();
	LRESULT onIMERequestCharPosition(IMECHARPOSITION* charPos);
	LRESULT onIMERequestReconvertString(RECONVERTSTRING*);
	LRESULT onIMERequest(WPARAM, LPARAM);
	bool onIMESelect(WPARAM, LPARAM);
	bool onIMESetContext(WPARAM, LPARAM);

protected:
	WndHost();
	virtual LPCTSTR windowClassName() const = 0;
	virtual LPCTSTR superclassName() const { return NULL; }
	virtual uint32_t classStyle() const { return 0; }

	virtual LRESULT handleMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0);
	virtual void OnFinalMessage(HWND hwnd);

	static LRESULT CALLBACK __wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK __controlProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam); 

	void sendMouseLeaveMsgToLastHoverView();

	void paint();

	void onLButtonDown(unsigned long flags, const IntPoint&);
	void onLButtonUp(unsigned long flags, const IntPoint&);
	void onChar(WPARAM wParam, LPARAM lParam);
	void onKeyDown(WPARAM wParam, LPARAM lParam);
	void onKeyUp(WPARAM wParam, LPARAM lParam);

	Editor* editor() const { return &m_editor; }

	void setFocusView(View *focusedView);

protected:
	void trackingMouseLeave();


protected:
	HWND m_hwnd;
	WNDPROC m_oldWndProc;
	bool m_subclassed;

	RefPtr<ViewTree> m_viewTree;

	unsigned int m_needLayout: 1;

	RefPtr<View> m_lastHoverView;
	RefPtr<View> m_focuedView;

	Region m_invalidateRegion;	//需要重新绘图的区域


	OwnPtr<HBITMAP> m_hbmp;		//绘图的缓冲区
	bool m_invalidBitmap;		//绘图的缓冲区无效，需要重新创建
	IntSize m_bitmapSize;
	HDC m_hdc;
	mutable Editor m_editor;

	BOOL m_trackingMouseLeave;
};

} //namespace UI
#endif /*__WNDHOST_H__*/
