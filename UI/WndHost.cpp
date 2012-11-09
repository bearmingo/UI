#include "WndHost.h"

#include <wtf/Assertions.h>
#include <wtf/text/CString.h>
#include <wtf/text/WTFString.h>

#include <Windows.h>
#include <windowsx.h>

#include "GraphicsContext.h"
#include "HWndDC.h"
#include "BitmapInfo.h"
#include "RunLoop.h"

#include "Event.h"

#include "MemDC.h"

#include "Common.h"
namespace UI {

WndHost::WndHost() 
	: m_hwnd(NULL)
	, m_oldWndProc(::DefWindowProc)
	, m_subclassed(false)
	, m_needLayout(1)
	, m_trackingMouseLeave(FALSE)
	, m_editor(this)
{
}

HWND WndHost::createHost( HWND hwndParent, LPCTSTR lpszName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu /*= NULL*/ )
{
	return createHost(hwndParent, lpszName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu);
}

HWND WndHost::createHost( HWND hwndParent, LPCTSTR lpszName, DWORD dwStyle, DWORD dwExStyle, int x /*= CW_USEDEFAULT*/, int y /*= CW_USEDEFAULT*/, int cx /*= CW_USEDEFAULT*/, int cy /*= CW_USEDEFAULT*/, HMENU hMenu /*= NULL*/ )
{
	//ASSERT(superclassName() != NULL && !registerSuperclass());
	if (superclassName() != NULL && !registerSuperclass()) 
		return NULL;
	//ASSERT(superclassName() == NULL && !registerWindowClass());
	if (superclassName() == NULL && !registerWindowClass())
		return NULL;

	m_hwnd = ::CreateWindowEx(dwExStyle, windowClassName(), lpszName, dwStyle, x, y, cx, cy, hwndParent, hMenu, (HINSTANCE)GetModuleHandle(NULL), this);
	ASSERT(m_hwnd != NULL);
	return m_hwnd;
}

HWND WndHost::subclass( HWND hWnd )
{
	ASSERT(::IsWindow(hWnd));
	ASSERT(m_hwnd == NULL);
	m_oldWndProc = SubclassWindow(hWnd, static_cast<WNDPROC>(__wndProc));
	if (m_oldWndProc == NULL)
		return NULL;
	m_subclassed = true;
	m_hwnd = hWnd;
	return m_hwnd;
}

void WndHost::unsubclass()
{
	ASSERT(::IsWindow(m_hwnd));
	if (!::IsWindow(m_hwnd))
		return;
	if (!m_subclassed)
		return;

	SubclassWindow(m_hwnd, m_oldWndProc);
	m_subclassed = false;

}

void WndHost::showWindow( bool bShow /*= true*/, bool bTakeFocus /*= true*/ )
{
	ASSERT(::IsWindow(m_hwnd));
	if (!::IsWindow(m_hwnd))
		return;
	::ShowWindow(m_hwnd, bShow ? (bTakeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

uint32_t WndHost::showModal()
{
	ASSERT(::IsWindow(m_hwnd));
	uint32_t result = 0;
	HWND hWndParent = GetWindowOwner(m_hwnd);
	::ShowWindow(m_hwnd, SW_SHOWNORMAL);
	::EnableWindow(hWndParent, FALSE);

	MSG msg = {0};
	while (::IsWindow(m_hwnd) && ::GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == WM_CLOSE && msg.hwnd == m_hwnd) {
			result = msg.wParam;
			::EnableWindow(hWndParent, TRUE);
			::SetFocus(hWndParent);
		}
		
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			break;
	}

	::EnableWindow(hWndParent, TRUE);
	::SetFocus(hWndParent);
	if (msg.message == WM_QUIT)
		::PostQuitMessage(msg.wParam);
	return result;
}

void WndHost::close( uint32_t ret /*= IDOK*/ )
{
	ASSERT(::IsWindow(m_hwnd));
	if (!::IsWindow(m_hwnd))
		return;
	postMessage(WM_CLOSE, (WPARAM)ret, 0L);
}

void WndHost::centerWindow(HWND hWndCenter)
{
	ASSERT(::IsWindow(m_hwnd));

	//determine owner window to center against
	DWORD dwStyle = (DWORD)::GetWindowLong(m_hwnd, GWL_STYLE);
	if (hWndCenter == NULL) {
		if (dwStyle & WS_CHILD)
			hWndCenter = ::GetParent(m_hwnd);
		else
			hWndCenter = ::GetWindow(m_hwnd, GW_OWNER);
	}

	//get coordinates of the window relative its parent
	RECT rcDlg;
	::GetWindowRect(m_hwnd, &rcDlg);
	RECT rcArea;
	RECT rcCenter;
	HWND hWndParent;
	if (!(dwStyle & WS_CHILD)) {
		//don't center against invisible or minimized windows
		if (hWndCenter != NULL) {
			DWORD dwStyleCenter = ::GetWindowLong(hWndCenter, GWL_STYLE);
			if (!(dwStyleCenter & WS_VISIBLE) || (dwStyleCenter & WS_MINIMIZE))
				hWndCenter = NULL;
		}

		//center within screen coordinate
		::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcArea, NULL);
		if (hWndCenter == NULL)
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);
	} else {
		//center within parent client corrdinates
		hWndParent = ::GetParent(m_hwnd);
		ASSERT(::IsWindow(hWndParent));

		::GetClientRect(hWndParent, &rcArea);
		ASSERT(::IsWindow(hWndCenter));
		::GetClientRect(hWndCenter, &rcCenter);
		::MapWindowPoints(hWndCenter, hWndParent, (POINT *)&rcCenter, 2);
	}

	int dlgWidth = rcDlg.right - rcDlg.left;
	int dlgHeight = rcDlg.bottom - rcDlg.top;

	//find dialog's upper left based on rcCenter
	int xLeft = (rcCenter.left + rcCenter.right - dlgWidth) / 2;
	int yTop = (rcCenter.bottom + rcCenter.top - dlgHeight) / 2;

	//if the dialog is outside the screen, move ti inside
	if (xLeft < rcArea.left)
		xLeft = rcArea.left;
	else if (xLeft + dlgWidth > rcArea.right)
		xLeft = rcArea.right - dlgWidth;

	if (yTop < rcArea.top)
		yTop = rcArea.top;
	else if (yTop + dlgHeight > rcArea.bottom)
		yTop = rcArea.bottom - dlgHeight;

	//map screen coordinates to child coordinated
	::SetWindowPos(m_hwnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

}

void WndHost::setIcon( uint32_t res )
{
	HICON hIcon = (HICON)::LoadImage((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	ASSERT(hIcon);
	::SendMessage(m_hwnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
	hIcon  = (HICON)::LoadImage((HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	ASSERT(hIcon);
	::SendMessage(m_hwnd, WM_SETICON, (WPARAM)FALSE, (LPARAM)hIcon);
}

bool WndHost::registerWindowClass()
{
	WNDCLASS wc = {0};
	wc.style = classStyle();
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.lpfnWndProc = WndHost::__wndProc;
	wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = windowClassName();
	ATOM result = ::RegisterClass(&wc);

	ASSERT(result != NULL|| ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return result != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

bool WndHost::registerSuperclass()
{
	// Get the class information from an existing
	// Window so we can subclass it later on...
	WNDCLASSEX wc = {0};
	wc.cbSize = sizeof(WNDCLASSEX);
	if (::GetClassInfoEx(NULL, superclassName(), &wc)) {
		if (!::GetClassInfoEx((HINSTANCE)GetModuleHandle(NULL), superclassName(), &wc)) {
			ASSERT(!"Unable to locate window class");
			return NULL;
		}
	}

	m_oldWndProc = wc.lpfnWndProc;
	wc.lpfnWndProc = WndHost::__controlProc;
	wc.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wc.lpszClassName = windowClassName();

	ATOM result = ::RegisterClassEx(&wc);
	ASSERT(result != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS);
	return result != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

LRESULT CALLBACK WndHost::__wndProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	WndHost *pThis = NULL;
	if (msg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lparam);
		pThis = static_cast<WndHost *>(lpcs->lpCreateParams);
		pThis->m_hwnd = hwnd;
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LPARAM>(pThis));
	} else {
		pThis = reinterpret_cast<WndHost *>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (msg == WM_NCDESTROY && pThis != NULL) {
			LRESULT result = ::CallWindowProc(pThis->m_oldWndProc, hwnd, msg, wparam, lparam);
			::SetWindowLongPtr(pThis->m_hwnd, GWLP_USERDATA, 0L);
			if (pThis->m_subclassed)
				pThis->unsubclass();
			pThis->m_hwnd = NULL;
			pThis->OnFinalMessage(hwnd);
			return result;
		}
	}

	if (pThis != NULL) {
		return pThis->handleMessage(msg, wparam, lparam);
	} else {
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

LRESULT CALLBACK WndHost::__controlProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
	WndHost *pThis = NULL;
	if (msg == WM_NCCREATE) {
		LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>(lparam);
		pThis = static_cast<WndHost*>(lpcs->lpCreateParams);
		::SetProp(hwnd, L"WndX", (HANDLE)pThis);
		pThis->m_hwnd = hwnd;
	} else {
		pThis = reinterpret_cast<WndHost*>(::GetProp(hwnd, L"WndX"));
		if (msg == WM_NCDESTROY && pThis != NULL) {
			LRESULT result = ::CallWindowProc(pThis->m_oldWndProc, hwnd, msg, wparam, lparam);
			if (pThis->m_subclassed)
				pThis->unsubclass();
			::SetProp(hwnd, L"WndX", 0);
			pThis->m_hwnd = NULL;
			pThis->OnFinalMessage(hwnd);
			return result;
				
		}
	}

	if (pThis != NULL) {
		return pThis->handleMessage(msg, wparam, lparam);
	} else {
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

bool WndHost::sendMessage( UINT msg, WPARAM wparam /*= 0L*/, LPARAM lparam /*= 0L*/ )
{
	ASSERT(::IsWindow(m_hwnd));
	return !!::SendMessage(m_hwnd, msg, wparam, lparam);
}

bool WndHost::postMessage( UINT msg, WPARAM wparam, LPARAM lparam )
{
	ASSERT(::IsWindow(m_hwnd));
	return !!::PostMessage(m_hwnd, msg, wparam, lparam);
}

void WndHost::resizeClient( int cx /*= -1*/, int cy /*= -1*/ )
{
	ASSERT(::IsWindow(m_hwnd));
	RECT rc = { 0 };
	if( !::GetClientRect(m_hwnd, &rc) ) return;
	if( cx != -1 ) rc.right = cx;
	if( cy != -1 ) rc.bottom = cy;
	if( !::AdjustWindowRectEx(&rc, GetWindowStyle(m_hwnd), (!(GetWindowStyle(m_hwnd) & WS_CHILD) && (::GetMenu(m_hwnd) != NULL)), GetWindowExStyle(m_hwnd)) ) return;
	::SetWindowPos(m_hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
}

LRESULT WndHost::handleMessage( UINT msg, WPARAM wparam /*= 0*/, LPARAM lparam /*= 0*/ )
{
	bool handled = true;
	LRESULT lResult = 0;

	switch (msg) {
	case WM_SIZE:
		{
			int width = GET_X_LPARAM(lparam);
			int height = GET_Y_LPARAM(lparam);
			if (viewTree() && viewTree()->root()) {
				m_viewTree->root()->setWidthWithMargin(width);
				m_viewTree->root()->setHeightWithMargin(height);
				m_viewTree->relayout();
			}
		}
		break;
	case WM_PAINT:
		{
			paint();
			return S_OK;
		}
	case WM_MOUSEMOVE:
		trackingMouseLeave();
		if (viewTree() && viewTree()->root()) {

			IntPoint point(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));

			View *hoverItem = viewTree()->root()->getTopmostChildByPoint(point);

			if (hoverItem != m_lastHoverView.get()) {
				sendMouseLeaveMsgToLastHoverView();

				if (hoverItem) {
					Event event(UIEvent_MouseEnter, wparam);
					hoverItem->onEvent(event);
				}
				m_lastHoverView = hoverItem;
			} else if (hoverItem) {
				Event event(UIEvent_MouseMove, wparam, lparam);
				hoverItem->onEvent(event);
			}
		}
		break;

	case WM_MOUSELEAVE:
		sendMouseLeaveMsgToLastHoverView();
		m_trackingMouseLeave = FALSE;
		break;
	case WM_LBUTTONUP:
		onLButtonUp(wparam, toIntPoint(lparam));
		break;
	case WM_LBUTTONDOWN:
		onLButtonDown(wparam, toIntPoint(lparam));
		break;
	case WM_CHAR:
		onChar(wparam, lparam);
		break;
	case WM_KEYDOWN:
		onKeyDown(wparam, lparam);
		break;
	case WM_KEYUP:
		onKeyUp(wparam, lparam);
		break;
	case WM_CLOSE:
		RunLoop::main()->stop();
		break;
	case WM_IME_STARTCOMPOSITION:
		handled = onIMEStartComposition();
		break;
	case WM_IME_REQUEST:
		handled = onIMERequest(wparam, lparam);
		break;
	case WM_IME_COMPOSITION:
		handled = onIMEComposition(lparam);
		break;
	case WM_IME_ENDCOMPOSITION:
		handled = onIMEEndComposition();
		break;
	case WM_IME_SELECT:
		handled = onIMESelect(wparam, lparam);
		break;
	case WM_IME_SETCONTEXT:
		handled = onIMESetContext(wparam, lparam);
		break;

	case WM_NCCALCSIZE:
		lResult = onNcCalcSize(wparam, lparam);
		break;
	default:
		handled = false;
		break;

	}
	if (!handled)
		lResult = ::CallWindowProc(m_oldWndProc, m_hwnd, msg, wparam, lparam);

	return lResult;
}


void WndHost::sendMouseLeaveMsgToLastHoverView()
{
	if (!m_lastHoverView)
		return;
	Event event(UIEvent_MouseLeave, 0, 0);
	m_lastHoverView->onEvent(event);
	m_lastHoverView = 0;
}

void WndHost::OnFinalMessage( HWND hwnd )
{

}

IntSize WndHost::clientSize()
{
	RECT rc = {0};
	::GetClientRect(m_hwnd, &rc);

	return IntSize(rc.right - rc.left, rc.bottom - rc.top);
}

void WndHost::setTitle(const UChar *title)
{
	::SetWindowText(m_hwnd, title);
}

void WndHost::invalidateRect( const IntRect& rect)
{
	m_invalidateRegion.unite(Region(rect));

	if (::IsWindow(m_hwnd)) {
		RECT rc = rect;
		::InvalidateRect(m_hwnd, &rc, FALSE);
	}
}

void WndHost::paint()
{
	RECT rc = {0};
	GetClientRect(m_hwnd, &rc);

	SIZE size;
	size.cx = rc.right - rc.left;
	size.cy = rc.bottom - rc.top;

	IntSize windowClientSize(rc.right - rc.left, rc.bottom - rc.top);
	if (windowClientSize.isEmpty())
		return;

	PAINTSTRUCT ps = {0};
	BeginPaint(m_hwnd, &ps);
	HDC m_hdc = ps.hdc;

	if (viewTree() && viewTree()->root()) {
		OwnPtr<HDC> hdc = adoptPtr(::CreateCompatibleDC(HWndDC(m_hwnd)));
		
		
		bool needAllRedraw = false;

		if (windowClientSize != m_bitmapSize) {
			if (m_hbmp) {
				DeleteObject(m_hbmp.get());
				m_hbmp.clear();
			}
		}

		if (!m_hbmp.get()) {
			BitmapInfo bitmapInfo = BitmapInfo::createBottomUp(IntSize(size));

			void* pixels = 0;
			m_hbmp = adoptPtr(::CreateDIBSection(hdc.get(), &bitmapInfo, DIB_RGB_COLORS, &pixels, 0, 0));
			//ASSERT_WITH_MESSAGE(m_hbmp, "::CreateDIBSection failed with error %lu", ::GetLastError());
			needAllRedraw = true;
			m_bitmapSize = windowClientSize;

		}

		::SelectObject(hdc.get(), m_hbmp.get());

		if (viewTree()->needRelayout()) {
			viewTree()->relayout();
		}

 		IntRect damageRect(rc);
 
  		GraphicsContext context(hdc.get(), true);
  		context.save();
 
 		Vector<IntRect> rects = m_invalidateRegion.rects();

 		if (needAllRedraw) {
 			viewTree()->root()->draw(&context, damageRect);
 		} else {
 			for (Vector<IntRect>::iterator it = rects.begin(), end = rects.end(); it != end; it++) {
 				context.save();
 				context.clip(*it);
 				viewTree()->root()->draw(&context, *it);
 				context.restore();
 			}
 		}

 		m_invalidateRegion = Region();
 
 		context.restore();
 
 		BLENDFUNCTION bf;
 		bf.BlendOp = AC_SRC_OVER;
 		bf.BlendFlags = 0;
 		bf.SourceConstantAlpha = 255;
 		bf.AlphaFormat = AC_SRC_ALPHA;
 
 		POINT srcPoint;
 		srcPoint.x = 0;
 		srcPoint.y = 0;
 
 		POINT dstPoint;
 		dstPoint.x = rc.left;
 		dstPoint.y = rc.top;
 
 		//::UpdateLayeredWindow(m_hwnd, HWndDC(0), &dstPoint, &size, hdc, &srcPoint, 0, &bf, ULW_ALPHA);
 		HWndDC hWndDC;
 		HDC localDC = m_hdc ? m_hdc : hWndDC.setHWnd(m_hwnd);
 
 		::BitBlt(localDC, damageRect.x(), damageRect.y(), damageRect.width(), damageRect.height(), hdc.get(), damageRect.x(), damageRect.y(), SRCCOPY);
	}

	EndPaint(m_hwnd, &ps);
	//ReleaseDC(m_hwnd, m_hdc);

// 	::GetClientRect(m_hwnd, &rc);
// 	InvalidateRect(m_hwnd, &rc, TRUE);

	return;
}

void WndHost::trackingMouseLeave()
{
	if (m_trackingMouseLeave != FALSE)
		return;

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = m_hwnd;
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = 0;
	
	m_trackingMouseLeave = TrackMouseEvent(&tme);
}

void WndHost::onLButtonDown( unsigned long flags, const IntPoint& p)
{
	if (m_lastHoverView.get()) {

		setFocusView(m_lastHoverView.get());

		Event event(UIEvent_ButtonDown, flags, p);
		m_lastHoverView->onEvent(event);
		
		if (m_lastHoverView->isObject("EditView")) {
			editor()->setEditingView(m_lastHoverView);
		}
	}
}

void WndHost::onLButtonUp( unsigned long flags, const IntPoint& p)
{
	if (m_lastHoverView.get()) {
		Event event(UIEvent_ButtonUp, flags, p);
		m_lastHoverView->onEvent(event);
	}
}

void WndHost::onKeyDown( WPARAM wParam, LPARAM lParam )
{
	//消息发送给获得焦点的View
	if (m_focuedView.get()) {
		Event event(UIEvent_KeyDown, wParam, lParam);
		m_focuedView->onEvent(event);
	}
}

void WndHost::onKeyUp( WPARAM wParam, LPARAM lParam )
{
	//消息发送给获得焦点的View
	if (m_focuedView.get()) {
		Event event(UIEvent_KeyUp, wParam, lParam);
		m_focuedView->onEvent(event);
	}
}

void WndHost::onChar( WPARAM wParam, LPARAM lParam )
{
	//消息发送给获得焦点的View
	if (m_focuedView.get()) {
		Event event(UIEvent_Char, wParam, lParam);
		m_focuedView->onEvent(event);
	}
}

HIMC WndHost::getIMMContext()
{
	return ImmGetContext(m_hwnd);
}

void WndHost::prepareCandidateWindow( HIMC hInputContext )
{
	IntRect caret = m_editor.firstRectForCharacterInSelectedRange();
	CANDIDATEFORM form;
	form.dwIndex = 0;
	form.dwStyle = CFS_EXCLUDE;
	form.ptCurrentPos.x = caret.x();
	form.ptCurrentPos.y = caret.y();
	form.rcArea.top = caret.y();
	form.rcArea.bottom = caret.maxY();
	form.rcArea.left = caret.x();
	form.rcArea.right = caret.maxY();
	ImmSetCandidateWindow(hInputContext, & form);
}

void WndHost::resetIME()
{
	HIMC hInputContext = getIMMContext();
	if (!hInputContext)
		return;
	ImmNotifyIME(hInputContext, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
	ImmReleaseContext(m_hwnd, hInputContext);
}

void WndHost::setInputMethodState( bool enable )
{
	ImmAssociateContextEx(m_hwnd, 0, enable ? IACE_DEFAULT : 0);
}

void WndHost::compositionSelectionChanged( bool hasChanged )
{
	if (!hasChanged)
		resetIME();
}

bool WndHost::onIMEStartComposition()
{
	HIMC hInputContent = getIMMContext();
	if (hInputContent)
		return false;

	prepareCandidateWindow(hInputContent);
	ImmReleaseContext(m_hwnd, hInputContent);

	return true;
}

static bool getCompositionString(HIMC hInputContext, DWORD type, String& result)
{
	LONG compositionLength = ImmGetCompositionStringW(hInputContext, type, 0, 0);
	if (compositionLength <= 0)
		return false;

	Vector<UChar> compositionBuffer(compositionLength / 2);
	compositionLength = ImmGetCompositionStringW(hInputContext, type, compositionBuffer.data(), compositionLength);
	result = String::adopt(compositionBuffer);
	return true;
}

static void compositionToUnderlines(const Vector<DWORD>& clauses, const Vector<BYTE>& attributes, Vector<CompositionUnderline>& underlines)
{
	if (clauses.isEmpty()) {
		underlines.clear();
		return;
	}

	size_t numBoundaries = clauses.size() -1;
	underlines.resize(numBoundaries);
	for (unsigned i = 0; i < numBoundaries; i++) {
		underlines[i].startOffset = clauses[i];
		underlines[i].endOffset = clauses[i + 1];
		BYTE attribute = attributes[clauses[i]];
		underlines[i].thick = attribute == ATTR_TARGET_CONVERTED || attribute == ATTR_TARGET_NOTCONVERTED;
		underlines[i].color = Color::black;
	}
}

bool WndHost::onIMEComposition( LPARAM lparam )
{
	HIMC hInputContext = getIMMContext();
	if (!hInputContext)
		return true;

	prepareCandidateWindow(hInputContext);

	if (lparam & GCS_RESULTSTR || !lparam) {
		String compositionString;
		if (!getCompositionString(hInputContext, GCS_RESULTSTR, compositionString) && lparam)
			return true;
		
		editor()->confirmComposition(compositionString);
		return true;
	}

	String compositionString;
	if (!getCompositionString(hInputContext, GCS_COMPSTR, compositionString))
		return true;

	//Composition string attribute
	int numAttributes = ImmGetCompositionStringW(hInputContext, GCS_COMPATTR, 0, 0);
	Vector<BYTE> attributes(numAttributes);
	ImmGetCompositionStringW(hInputContext, GCS_COMPATTR, attributes.data(), numAttributes);

	int numBytes = ImmGetCompositionStringW(hInputContext, GCS_COMPCLAUSE, 0, 0);
	Vector<DWORD> clauses(numBytes / sizeof(DWORD));
	ImmGetCompositionStringW(hInputContext, GCS_COMPCLAUSE, clauses.data(), numBytes);

	Vector<CompositionUnderline> underlines;
	compositionToUnderlines(clauses, attributes, underlines);

	int cursorPosition = LOWORD(ImmGetCompositionStringW(hInputContext, GCS_CURSORPOS, 0, 0));

	editor()->setComposition(compositionString, underlines, cursorPosition);

	return true;
}

bool WndHost::onIMEEndComposition()
{
	if (editor()->hasComposition())
		editor()->confirmComposition(String());

	return false;
}

LRESULT WndHost::onIMERequestCharPosition( IMECHARPOSITION* charPos )
{
	IntRect caret = editor()->firstRectForCharacterInSelectedRange();

	charPos->pt.x = caret.x();
	charPos->pt.y = caret.y();
	::ClientToScreen(m_hwnd, &charPos->pt);
	charPos->cLineHeight = caret.height();
	::GetWindowRect(m_hwnd, &charPos->rcDocument);
	return true;
}

LRESULT WndHost::onIMERequestReconvertString( RECONVERTSTRING* reconvertString)
{
	String text = editor()->getSelectedText();
	unsigned totalSize = sizeof(RECONVERTSTRING) + text.length() * sizeof(UChar);

	if (!reconvertString)
		return totalSize;

	if (totalSize > reconvertString->dwSize)
		return 0;
	reconvertString->dwCompStrLen = text.length();
	reconvertString->dwStrLen = text.length();
	reconvertString->dwTargetStrLen = text.length();
	reconvertString->dwStrOffset = sizeof(RECONVERTSTRING);
	memcpy(reconvertString + 1, text.characters(), text.length() * sizeof(UChar));
	return totalSize;
}

LRESULT WndHost::onIMERequest( WPARAM request, LPARAM data)
{
	switch (request) {
	case IMR_RECONVERTSTRING:
		return onIMERequestReconvertString(reinterpret_cast<RECONVERTSTRING*>(data));

	case IMR_QUERYCHARPOSITION:
		return onIMERequestCharPosition(reinterpret_cast<IMECHARPOSITION*>(data));
	}
	return 0;
}

bool WndHost::onIMESelect( WPARAM, LPARAM )
{
	return false;
}	

bool WndHost::onIMESetContext( WPARAM, LPARAM )
{
	return false;
}

void WndHost::setFocusView(View *focusedView)
{
	if (focusedView == m_focuedView)
		return;

	if (m_focuedView) {
		Event event(UIEvent_KillFocus);
		m_focuedView->onEvent(event);
	}

	m_focuedView = focusedView;

	if (m_focuedView) {
		Event event(UIEvent_SetFocus);
		m_focuedView->onEvent(event);
	}
}

LRESULT WndHost::onNcCalcSize( WPARAM wParam, LPARAM lParam)
{
	BOOL bCalcValidRects = (BOOL)wParam;
	NCCALCSIZE_PARAMS* lpncsp = (NCCALCSIZE_PARAMS *)lParam;

	RECT windowRc;
	GetWindowRect(GetHWND(), &windowRc);
	//lpncsp->rgrc[0] = windowRc;
	lpncsp->rgrc[0].left = windowRc.left + 1;
	lpncsp->rgrc[0].top = windowRc.top;
	lpncsp->rgrc[0].bottom = windowRc.bottom;
	lpncsp->rgrc[0].right = windowRc.right - 1;

	LRESULT lResult = 0;//::CallWindowProc(m_oldWndProc, GetHWND(), WM_NCCALCSIZE, wParam, lParam);
	
	return lResult;
}


























} //namespace UI