#include "ViewFactory.h"

#include <wtf/text/WTFString.h>

#include "View.h"
#include "Container.h"
#include "LinearLayout.h"
#include "TextView.h"
#include "EditView.h"

namespace UI {

PassRefPtr<View> ViewFactory::createView( const char * viewName )
{
	return createView(String(viewName));
}

PassRefPtr<View> ViewFactory::createView( String viewName )
{
	if (viewName == "View") {
		return adoptRef(new View());
	} else if (viewName == "Container") {
		return adoptRef(new Container());
	} else if (viewName == "LinearLayout") {
		return LinearLayout::create();
	} else if (viewName == "TextView") {
		return TextView::create();
	} else if (viewName == EditView::className()) {
		return EditView::create();
	}
	//return adoptRef(0);
	return 0;
}

}