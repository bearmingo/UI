#ifndef __BITMAPCACHE_H__
#define __BITMAPCACHE_H__

#include <wtf/PassRefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/Noncopyable.h>
#include <wtf/FastMalloc.h>

#include "Color.h"
#include "IntSize.h"

namespace UI {

class BitmapCache : public RefCounted<BitmapCache>
{
	WTF_MAKE_NONCOPYABLE(BitmapCache);
	WTF_MAKE_FAST_ALLOCATED;
public:
	PassRefPtr<BitmapCache> create() { return adoptRef(new BitmapCache()); }

	static Color InvalidateBackgroundColor;

	bool createBitmap(const IntSize& size, const Color& backgroundColor);

private:
	BitmapCache() {}
	HBITMAP m_hbitmap;
};

}
#endif /*__BITMAPCACHE_H__*/

