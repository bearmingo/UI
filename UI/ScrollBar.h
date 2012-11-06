#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

namespace UI {

class ScrollBar 
{
public:
	enum ScrollBarType { SB_Horizontal, SB_Vertical };
private:
	ScrollBarType m_scrollbarType;
	int m_offset;
	int m_scrollbarWidth;

};
}
#endif /*__SCROLLBAR_H__*/

