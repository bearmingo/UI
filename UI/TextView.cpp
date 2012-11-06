#include "TextView.h"

#include "GraphicsContext.h"
#include "Font.h"
#include "TextRun.h"

#include "DrawHelper.h"

namespace UI {

static Font dragLabelFont(int size, bool bold, FontRenderingMode renderingMode)
{
	NONCLIENTMETRICS metrics;
	metrics.cbSize = sizeof(metrics);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);

	FontDescription description;
	description.setWeight(bold ? FontWeightBold : FontWeightNormal);

	FontFamily family;
	family.setFamily(metrics.lfSmCaptionFont.lfFaceName);
	description.setFamily(family);
	description.setSpecifiedSize((float)size);
	description.setComputedSize((float)size);
	description.setRenderingMode(renderingMode);
	Font result = Font(description, 0, 0); 
	result.update(0);
	return result;
}

void TextView::measure()
{
	//DrawHelper drawHelper;

	if (attributeOfWidth() == WrapContent || attributeOfHeight() == WrapContent) {
// 		IntSize size;
// 		drawHelper.calcText(m_text, size, &m_font);
// 
// 		if (attributeOfWidth() == WrapContent) 
// 			setWidth(size.width() + paddingLeft() + paddingRight() + 2 * style()->borderSize() * 2);
// 		if (attributeOfHeight() == WrapContent)
// 			setHeight(size.height() + paddingTop() + paddingBottom() + 2 * style()->borderSize() * 2);


		//Font font = dragLabelFont(m_fontSize, true, NormalRenderingMode);
		//font.setWordSpacing(10);
		//font.setLetterSpacing(10);
		Font font(fontDescription(), 0, 0);
		font.update(0);

		TextRun textRun(m_text);

		if (attributeOfWidth() == WrapContent) {
			float width = font.width(textRun);
			setWidth(width + paddingLeft() + paddingRight() + layoutParam()->borderSize() * 2);
		}

		if (attributeOfHeight() == WrapContent)
			setHeight(font.fontMetrics().height() + paddingTop() + paddingBottom() + layoutParam()->borderSize() * 2);
	}

}

void TextView::draw( GraphicsContext *context, const IntRect& rc)
{
	__super::draw(context, rc);

	if (m_text.length() != 0) {

		context->save();

		context->clip(rect());

		//Font font = dragLabelFont(m_fontSize, true, NormalRenderingMode);
		Font font(fontDescription(), 0, 0);
		font.update(0);

		TextRun textRun(m_text);
		context->setFillColor(textColor(), ColorSpaceDeviceRGB);
		
		//calculate text
		IntSize textRect(font.width(textRun), font.fontMetrics().height());
		IntRect content(contentRect());


		context->drawText(font, textRun, LayoutPoint(contentX(), contentY() + font.fontMetrics().height()));
		//context->drawEmphasisMarks(font, textRun, "?", FloatPoint(contentX(), contentY() + font.fontMetrics().height()), 11);
		context->restore();
	}
}

bool TextView::attribute( const String& name, const String& value )
{
	if (name == "text") {
		m_text = value;
		return true;
	}

	return __super::attribute(name, value);
}



} //namespace UI