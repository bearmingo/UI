/********************************************************************
	file base:	ViewFactory.h
	author:		cgm(cgm@eastcom.com)
	created:	2012/08/27
	
	purpose:	
*********************************************************************/

#ifndef __VIEWFACTORY_H__
#define __VIEWFACTORY_H__

#include <wtf/PassRefPtr.h>
#include <wtf/text/WTFString.h>
#include "View.h"

namespace UI {

class ViewFactory
{
public:
	static PassRefPtr<View> createView(const char * viewName);
	static PassRefPtr<View> createView(String viewName);
};


}
#endif /*__VIEWFACTORY_H__*/
