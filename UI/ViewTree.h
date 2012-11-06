#ifndef __VIEWTREE_H__
#define __VIEWTREE_H__

#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/HashMap.h>
#include <wtf/RefPtrHashMap.h>
#include <wtf/text/WTFString.h>
#include <wtf/text/StringHash.h>
#include <wtf/FastMalloc.h>
#include <wtf/Noncopyable.h>

#include "View.h"

namespace UI {

class WndHost;

class ViewTree : public RefCounted<ViewTree>
{
	WTF_MAKE_FAST_ALLOCATED;
	WTF_MAKE_NONCOPYABLE(ViewTree);
public:

	static PassRefPtr<ViewTree> create() { return adoptRef(new ViewTree()); }

	View* root() { return m_root.get(); }
	void setRoot(PassRefPtr<View> root);

	bool addView(PassRefPtr<View> view);
	bool removeView(PassRefPtr<View> view);

	View* findViewById(String id) { m_views.find(id); }
	View* findViewByPoint(const IntPoint& point);
	View* findViewByTab(View *current);

	WndHost* wndHost() { ASSERT(m_host); return m_host; }

	bool needRelayout() const { return m_needLayout; }
	void setNeedRelayout(bool n) { m_needLayout = n; }

	void relayout();

protected:
	friend class WndHost;
	void setWndHost(WndHost *wndHost);

private:
	ViewTree() { }
	
	RefPtr<View> m_root;

	WndHost *m_host;
	
	HashMap<String, RefPtr<View>, StringHash> m_views;

	bool m_needUpdate;	//重绘
	bool m_needLayout;	//重新布局
};






} // namespace UI
#endif /*__VIEWTREE_H__*/

