#ifndef __FONT_H__
#define __FONT_H__

#include <wtf/RefCounted.h>
#include <wtf/PassRefPtr.h>
#include <wtf/Noncopyable.h>
#include <wtf/FastMalloc.h>
#include <wtf/text/WTFString.h>

namespace UI {

class FontStyle
{

public:
/*	PassRefPtr<FontStyle> create() { return adoptRef(new FontStyle()); }*/
	
	FontStyle() : m_italic(0), m_bold(0), m_size(12), m_face("ÐÂËÎÌå") { }

	bool isItalic() const { return m_italic; }
	bool isBold() const { return m_bold; }
	double size() const { return m_size; }
	String face() const { return m_face; }
	
	void setItalic(bool italic) { m_italic = italic; }
	void setBold(bool bold) { m_bold = bold; }
	void setSize(double size) { m_size = size; }
	void setFace(const String& face) { m_face = face; }

	static FontStyle defaultFontStyle;

private:
	unsigned int m_italic: 1;
	unsigned int m_bold: 1;
	double m_size;
	String m_face;
};

}
#endif /*__FONT_H__*/

