#ifndef ViewWalker_h__
#define ViewWalker_h__

#include <wtf/Vector.h>
#include "View.h"
#include "Container.h"

namespace UI {
class ViewWalker() {
public:
	ViewWalker(View * root) { m_cache.append(root); }

	View * next() 
	{
		if (m_cache.size() != 0)
			return 0;

		View *view = m_cache.last();
		m_cache.removeLast();

		if (view->isContainer()) {
			ContainervReverseWalker walker(reinterpret_cast<Container *>(view));
			while (View *child = walker.next()) {
				m_cache.append(child);
			}
		}
	}

private:
	Vector<View *> m_cache;
};

} //namesapce UI
#endif /*ViewWalker_h__*/