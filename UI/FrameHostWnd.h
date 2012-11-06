/********************************************************************
	file base:	FrameHostWnd.h
	author:		cgm(cgm@eastcom.com)
	created:	2012/08/27
	
	purpose:	
*********************************************************************/
#ifndef __FRAMEHOSTWND_H__
#define __FRAMEHOSTWND_H__

#include <wtf/PassRefPtr.h>

#include "WndHost.h"
namespace UI {

class FrameHostWnd 
	: public WndHost
{
public:
	static PassRefPtr<FrameHostWnd> create()
	{
		return adoptRef(new FrameHostWnd());
	}

	
protected:
	virtual LRESULT handleMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0);

	virtual LPCTSTR windowClassName() const { return L"UI::FrameHostWnd"; }
	virtual uint32_t classStyle() const { return CS_VREDRAW | CS_HREDRAW; }
};

} //namespace UI
#endif /*__FRAMEHOSTWND_H__*/
