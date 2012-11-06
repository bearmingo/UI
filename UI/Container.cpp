#include "Container.h"

#include "GraphicsContext.h"

#include "ViewTree.h"


namespace UI {

void Container::draw( GraphicsContext *context , const IntRect& rc)
{
	if (!rc.intersects(rect()))
		return;

	__super::draw(context, rc);

  	context->save();
  	FloatRect clipRect = contentRect();
  	context->clip(clipRect);
 
  	ViewVector::iterator it = m_children.begin();
  	for (; it != m_children.end(); it++) {
  		if ((*it)->isVisible() && rect().intersects((*it)->rect()))
  			(*it)->draw(context, rc);
  	}

	context->restore();
}

bool Container::addChild(PassRefPtr<View> child)
{
	RefPtr<View> view = child;

	ASSERT(view.get());
	
	ASSERT_WITH_MESSAGE(!view->parent(), "child has add other parent");
	if (view->parent())
		return false;

	if (m_children.contains(view))
		return false;

	view->setParent(this);
	m_children.append(view);

	//if viewTree is not null, mean this node already add to viewTree;
	if (viewTree()) {
		viewTree()->addView(view);
	}


	return true;
}

bool Container::removeChild( PassRefPtr<View> child )
{
	ASSERT_WITH_MESSAGE(child->parent() == this, "node is this node's child, remove error!!!");
	if (child->parent() != this)
		return false;

	if (viewTree())
		viewTree()->removeView(child);

	m_children.remove(m_children.find(child));
	return true;
}

void Container::setViewTree( ViewTree *viewTree )
{
	__super::setViewTree(viewTree);

	//设置子节点的viewTree
	ViewVector::iterator it = m_children.begin();
	for (; it != m_children.end(); it++) {
		(*it)->setViewTree(viewTree);
	}
}

View* Container::getTopmostChildByPoint( const IntPoint& point )
{
	for (ViewVector::reverse_iterator it = m_children.rbegin(), end = m_children.rend(); it != end; it++) {
		if ((*it)->rect().contains(point)) {
			if ((*it)->isContainer()) {
				return (*it)->getTopmostChildByPoint(point);
			}

			return (*it).get();
		}
	}

	return this;
}


}