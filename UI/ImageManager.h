#ifndef ImageManager_h
#define ImageManager_h

#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>
#include <wtf/RefCounted.h>
#include <wtf/HashMap.h>
#include <wtf/RefPtrHashMap.h>
#include <wtf/text/WTFString.h>
#include <wtf/text/StringHash.h>

#include "Image.h"

namespace UI {

class ImageFileManager 
{
public:
	static bool loadImageResourceFile(const String& file);
	static PassRefPtr<SharedBuffer> get(const String& id);

	void addNode(const String& name, PassRefPtr<SharedBuffer> sharedBuffer);
private:
	static ImageFileManager* instance();
	ImageFileManager() { };

	typedef HashMap<String, RefPtr<SharedBuffer>> ImageFileHashMap;

	ImageFileHashMap m_map;
};

} // namespace UI

#endif /*ImageManager_h*/