#include "FractionalLayoutSize.h"

#include "FractionalLayoutPoint.h"

namespace UI {

IntSize pixelSnappedIntSize(const FractionalLayoutSize& s, const FractionalLayoutPoint& p)
{
    return IntSize(snapSizeToPixel(s.width(), p.x()), snapSizeToPixel(s.height(), p.y()));
}

} // namespace UI 
