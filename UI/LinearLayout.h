#ifndef __LINEARLAYOUT_H__
#define __LINEARLAYOUT_H__

#include "Container.h"

namespace UI {

class LinearLayout : public Container
{
	UI_VIEW_DECLARE_CLASS_NAME(LinearLayout, "LinearLayout")
public:
	virtual ~LinearLayout() { }
	static PassRefPtr<LinearLayout> create() { return adoptRef(new LinearLayout()); }
	static PassRefPtr<LinearLayout> create(Container * parent)  { return adoptRef(new LinearLayout(parent)); }

	typedef enum {
		Horizontal,
		Vertical,
	} Orientation;

	Orientation orientation() const { return m_orientation; }
	void setOrientation(Orientation o) { m_orientation = o; }

	void layout(const LayoutParam& lp);

	virtual void measure();

	virtual bool attribute(const String& name, const String& value);
protected:
	LinearLayout() : m_orientation(Horizontal) { }
	LinearLayout(Container *parent);

	void layoutVertical(const LayoutParam&);
	void layoutHorizontal(const LayoutParam&);

	void measureVertical();
	void measureHorizontal();
private:
	Orientation m_orientation;
};

}
#endif /*__LINEARLAYOUT_H__*/
