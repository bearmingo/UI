#include "ImageManager.h"
#include <stdio.h>
#include <expat.h>


#include <wtf/OwnPtr.h>
#include <wtf/PassOwnPtr.h>
#include "ExpatOwnedPtr.h"

#include "SharedBuffer.h"
#include "BitmapImage.h"

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

#include "Common.h"


namespace UI {

void UI::ImageFileManager::addNode(const String& name, PassRefPtr<SharedBuffer> sharedBuffer )
{
	instance()->m_map.add(name, sharedBuffer);
}

static void XMLCALL startElement(void *userData, const char * name, const char **attrs)
{
	
	if (String(name) == "image") {
		String id;
		RefPtr<SharedBuffer> sharedBuffer;
		for (int i = 0; attrs[i]; i+= 2) {
			String nameString = attrs[i]; 

			if (nameString == "file") {
				sharedBuffer = SharedBuffer::createWithContentsOfFile(attrs[i + 1]);
				if (!sharedBuffer)
					break;

// 				image = BitmapImage::create();
// 				image->setData(sharedBuffer, true);
			} else if (nameString == "id") {
				id = attrs[i + 1];
			}
		}
		if (!id.isEmpty() && !!sharedBuffer) {
			static_cast<ImageFileManager *>(userData)->addNode(id, sharedBuffer.release());
		}
				
	}
}

static void XMLCALL endElement(void *userData, const char *name)
{

}

bool UI::ImageFileManager::loadImageResourceFile( const String& file )
{
	RefPtr<SharedBuffer> sharedBuffer = SharedBuffer::createWithContentsOfFile(file);
	if (!sharedBuffer)
		return false;

	OwnPtr<XML_Parser> parser = adoptPtr(XML_ParserCreate(NULL));

	if (!parser) {
		UI_LOG_VERBOSE("Couldn't allocate memory for parser\n");
		return false;
	}

	XML_SetUserData(parser.get(), ImageFileManager::instance());
	XML_SetElementHandler(parser.get(), startElement, endElement);

	const char* segment;
	unsigned pos = 0;
	while (unsigned length = sharedBuffer->getSomeData(segment, pos)) {
		pos += length;

		if (XML_Parse(parser.get(), segment, length, pos == sharedBuffer->size()) == XML_STATUS_ERROR) {
			UI_LOG_VERBOSE("%s at line %" XML_FMT_INT_MOD "u\n",
				XML_ErrorString(XML_GetErrorCode(parser.get())),
				XML_GetCurrentLineNumber(parser.get()));
			return false;
		}
	}

	return true;

}


ImageFileManager* ImageFileManager::instance()
{
	static ImageFileManager *sInstance = 0;
	if (!sInstance) {
		sInstance = new ImageFileManager;
		if (!sInstance)
			CRASH();
	}

	return sInstance;
}

PassRefPtr<SharedBuffer> ImageFileManager::get( const String& id )
{
	return instance()->m_map.get(id);
}


}