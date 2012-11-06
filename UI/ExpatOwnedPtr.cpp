#include "ExpatOwnedPtr.h"

#include <stdio.h>
#include <expat.h>

#if defined(__amigaos__) && defined(__USE_INLINE__)
#include <proto/expat.h>
#endif

#ifdef XML_LARGE_SIZE
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
#define XML_FMT_INT_MOD "I64"
#else
#define XML_FMT_INT_MOD "ll"
#endif
#else
#define XML_FMT_INT_MOD "l"
#endif

namespace WTF {

void deleteOwnedPtr(XML_Parser ptr)
{
	if (ptr)
		XML_ParserFree(ptr);
}

} // namespace WTF