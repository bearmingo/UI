#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <wtf/Vector.h>
#include "View.h"

namespace UI {

class ContainerWalker;
class ContainervReverseWalker;

class Container : public View 
{
	friend ContainerWalker;
	friend ContainervReverseWalker;
public:
	virtual bool isContainer() { return true; }


	virtual void draw(GraphicsContext *context, const IntRect& rect);

	virtual void setViewTree(ViewTree *viewTree);
	
	bool addChild(PassRefPtr<View> child);
	bool removeChild(PassRefPtr<View> child);

	virtual View* getTopmostChildByPoint(const IntPoint& point);
protected:
	typedef Vector<RefPtr<View>> ViewVector; 
	ViewVector m_children;
};



class ContainerWalker
{
public:
	ContainerWalker(Container *c) : m_container(c), m_current(0) { }

	View* next() 
	{
		if (m_current >= 0 && m_current < m_container->m_children.size())
			return m_container->m_children[m_current ++].get();

		return 0;
	}
private:
	Container * m_container;
	int m_current;
};

class ContainervReverseWalker
{
public:
	ContainervReverseWalker(Container *c) : m_container(c), m_current(c->m_children.size()) { }

	View* next() 
	{
		if (m_current >= 0 && m_current < m_container->m_children.size())
			return m_container->m_children[--m_current].get();

		return 0;
	}
private:
	Container * m_container;
	int m_current;
};
}
#endif /*__CONTAINER_H__*/

