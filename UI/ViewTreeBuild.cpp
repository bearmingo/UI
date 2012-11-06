#include "ViewTreeBuild.h"

#include <stdio.h>
#include <expat.h>


#include <wtf/OwnPtr.h>
#include <wtf/PassOwnPtr.h>
#include "ExpatOwnedPtr.h"
#include <wtf/text/CString.h>

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

#include "ViewFactory.h"
#include "Common.h"
#include "Container.h"

namespace UI {

class ViewXmlParser {
public:
    static void XMLCALL startElement(void *userData, const char *name, const char **attrs)
    {
        ViewXmlParser *This = reinterpret_cast<ViewXmlParser*>(userData);
        
		if (!This->m_viewTree){ 
			if (String("ViewTree") == name) {
				This->m_viewTree = ViewTree::create();
				return;
			}
		}

        RefPtr<View> view = ViewFactory::createView(name);
        if (!view) {
            UI_LOG_VERBOSE("invalidte node '%s'", name);
            XML_StopParser(This->m_parser.get(), XML_FALSE);
			return;
        }

		for (int i = 0; attrs[i]; i += 2) {
			view->attribute(String::fromUTF8(attrs[i]), String::fromUTF8(attrs[i + 1]));
		}

		if (This->m_parents.size() != 0) {
			View *parent = This->m_parents.last();
			if (parent->isContainer()) {
				reinterpret_cast<Container *>(parent)->addChild(view.get());
			} else {
				UI_LOG_VERBOSE("%s's parent is not container, can't add to it!!!", name);
				XML_StopParser(This->m_parser.get(), XML_FALSE);
				return;
			}
		} else {
			This->m_root = view;
		}

		This->m_parents.append(view.get());
    }
    
    static void XMLCALL endElement(void *userData, const char *name)
    {
        ViewXmlParser *This = reinterpret_cast<ViewXmlParser*>(userData);

		if (String("ViewTree") == name) {
			return;
		}

		This->m_parents.removeLast();
    }

	static void XMLCALL characterDataHandler(void *userData, const XML_Char *s, int len)
	{
		ViewXmlParser *This = reinterpret_cast<ViewXmlParser*>(userData);
		String data(s, len);
		UI_LOG_VERBOSE(data.ascii().data());

	}

	bool parser(SharedBuffer * data) 
	{
		m_parser = adoptPtr(XML_ParserCreate(NULL));
		if (!m_parser) {
			UI_LOG_VERBOSE("Couldn't allocate memory for parser\n");
			return false;
		}
		
		XML_SetUserData(m_parser.get(), this);
		XML_SetElementHandler(m_parser.get(), startElement, endElement);
		XML_SetCharacterDataHandler(m_parser.get(), characterDataHandler);

		const char *segment = 0;
		unsigned pos = 0;
		while (unsigned length = data->getSomeData(segment, pos)) {
			pos += length;

			if (XML_Parse(m_parser.get(), segment, length, pos == data->size()) == XML_STATUS_ERROR) {
				UI_LOG_VERBOSE("%s at line %" XML_FMT_INT_MOD "u\n",
					XML_ErrorString(XML_GetErrorCode(m_parser.get())),
					XML_GetCurrentLineNumber(m_parser.get()));
				return false;
			}
		}

		return true;
	}

	PassRefPtr<View> rootView() { return m_root.release(); }
	PassRefPtr<ViewTree> viewTree() 
	{
		if (!!m_viewTree) {
			if (!m_viewTree->root())
				m_viewTree->setRoot(m_root);
			return m_viewTree.release();
		}
		return 0;
	}

private:
    Vector<View *> m_parents;
    RefPtr<View> m_root;
    OwnPtr<XML_Parser> m_parser;
	RefPtr<ViewTree> m_viewTree;
};

PassRefPtr<ViewTree> ViewTreeBuild::buildViewTreeFromXmlFile(const String& xmlFile)
{
    RefPtr<SharedBuffer> sharedBuffer = SharedBuffer::createWithContentsOfFile(xmlFile);
    if (!sharedBuffer)
        return 0;
	ViewXmlParser viewXmlParser;

	viewXmlParser.parser(sharedBuffer.get());
    
    return viewXmlParser.viewTree();
}

}