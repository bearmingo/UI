#ifndef __TEXTVIEW_H__
#define __TEXTVIEW_H__

#include <wtf/text/WTFString.h>

#include "View.h"
#include "FontStyle.h"

namespace UI {

class TextView : public View
{
	UI_VIEW_DECLARE_CLASS_NAME(TextView, "TextView")
public:

	virtual ~TextView() { }
	static PassRefPtr<TextView> create() { return adoptRef(new TextView()); }

	void setText(const String& text) { m_text = text; }

	virtual void measure();

	virtual void draw(GraphicsContext *context, const IntRect&);
	virtual bool attribute(const String& name, const String& value);
protected:
	TextView() :m_align(StartTextAlign), m_fontSize(9), m_fontColor("gray"){ }
	
private:

	String m_text;
	
	FontStyle m_font;
	TextAlign m_align;
	Color m_fontColor;
	int m_fontSize;
};

} //namespace UI
#endif /*__TEXTVIEW_H__*/

