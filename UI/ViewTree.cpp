#include "ViewTree.h"

#include "WndHost.h"

namespace UI{
bool ViewTree::addView( PassRefPtr<View> view )
{
	ASSERT(view.get());

	//set node's viewTree
	view->setViewTree(this);

	if (view->hasId())
		m_views.add(view->id(), view);

	return true;
}


bool ViewTree::removeView( PassRefPtr<View> view )
{
	view->setViewTree(NULL);

	if (view->hasId())
		m_views.remove(view->id());

	return true;
}

void ViewTree::setRoot( PassRefPtr<View> root )
{
	ASSERT(root.get());
	m_root = root;
	setNeedRelayout(true);

	m_root->setViewTree(this);
}

void ViewTree::setWndHost( WndHost *wndHost )
{
	m_host = wndHost;
	
	if (wndHost && root()) {
		root()->setSizeWithMargin(wndHost->clientSize());
	}
}

void ViewTree::relayout()
{
	if (m_root) {
		m_root->measure();

		m_root->setLocation(IntPoint(m_root->marginLeft(), m_root->marginRigth()));

		RefPtr<LayoutParam> lp = LayoutParam::create();
		m_root->layout(*lp.get());
		m_needLayout = false;
	}
}

}