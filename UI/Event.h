#ifndef __EVENT_H__
#define __EVENT_H__

#include <wtf/text/WTFString.h>

#include "IntPoint.h"


//typedef unsigned int WPARAM;
//typedef unsigned int LPARAM;

namespace UI {

typedef enum {
	UIEvent__First = 0,
	UIEvent__KeyBegin,
	UIEvent_KeyDown,
	UIEvent_KeyUp,
	UIEvent_Char,
	UIEvent_SysKey,
	UIEvent__KeyEnd,
	UIEvent__MouseBegin,
	UIEvent_MouseMove,
	UIEvent_MouseLeave,
	UIEvent_MouseEnter,
	UIEvent_ButtonDown,
	UIEvent_ButtonUp,
	UIEvent_RButtonDown,
	UIEvent_RButtonUp,
	UIEvent_DBLClick,
	UIEvent_ContextMenu,
	UIEvnet_ScollWheel,
	UIEvent_MouseEnd,
	UIEvent_KillFocus,
	UIEvent_SetFocus,
	UIEvent_WindowSize,
	UIEvent_Timer,
	UIEvent_Notify,
	UIEvent_Command,
	UIEvent__Last,
} EventID;


class View;

inline LPARAM toLPARAM(const IntPoint& p)
{
	return (LPARAM)(((unsigned int)(p.x()) & 0xffff) | ((unsigned int)(p.y()) & 0xffff) << 16);
}

inline IntPoint toIntPoint(LPARAM lparam)
{
	return IntPoint(((unsigned int)lparam & 0xffff), (((unsigned int) lparam) >> 16) & 0xffff);
}

class Event
{
public:
	Event(EventID id, WPARAM wparam = 0, LPARAM lparam = 0, View *sender = 0) 
		: m_id(id)
		, m_wparam(wparam)
		, m_lparam(wparam)
		, m_sender(m_sender)
		, m_isWindowEvent(true)
	{
	}

	Event(EventID id, unsigned int flags, const IntPoint& p, View * sender = 0)
		: m_id(id)
		, m_wparam(flags)
		, m_lparam(toLPARAM(p))
		, m_sender(sender)
		, m_isWindowEvent(true)
	{

	}


	WPARAM wparam() { return m_wparam; }
	LPARAM lparam() { return m_lparam; }
	View * sender() { return m_sender; }

	EventID id() const { return m_id; }
	const String& eventName() const { return m_name; }

	bool isWindowEvent() const { return m_isWindowEvent; }
	void setWindowEvent(bool b) { m_isWindowEvent = b; }

private:


	EventID m_id;
	String m_name;
	WPARAM m_wparam;
	LPARAM m_lparam;
	View* m_sender;
	char m_key;
	short m_keyState;
	long m_timestamp;

	bool m_isWindowEvent;
};


}

#endif /*__EVENT_H__*/

