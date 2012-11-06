#ifndef ViewTreeBuild_h__
#define ViewTreeBuild_h__

#include <wtf/PassRefPtr.h>
#include <wtf/text/WTFString.h>

#include "ViewTree.h"
namespace UI {

class ViewTreeBuild
{
public:
    static PassRefPtr<ViewTree> buildViewTreeFromXmlFile(const String& xmlFile);
};

}

#endif /*Viewtreebuild_h__*/
