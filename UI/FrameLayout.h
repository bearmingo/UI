#ifndef FrameLayout_h__
#define FrameLayout_h__

#include "Container.h"

class FrameLayout : public Container
{
	UI_VIEW_DECLARE_CLASS_NAME(LinearLayout, "FrameLayout");
public:
	virtual ~FrameLayout() { }
	static PassRefPtr<FrameLayout> create() { return adoptRef(new FrameLayout()); }
	static PassRefPtr<FrameLayout> create(Container *parent) { return adoptRef(new FrameLayout()); }

	virtual void layout(const LayoutParam& lp);
	virtual void measure();

	virtual bool attribute(const String& name, const String& value);

protected:
	virtual bool attributeWithHashName(const ViewAttributeName& name, const String& value);
};


#endif /*FrameLayout_h__*/