#include "EditView.h"

#include "GraphicsContext.h"
#include "font.h"
#include "TextRun.h"
#include "Event.h"

namespace UI {

const double kCaretFlashEllipse = 0.5;


EditView::EditView()
	: m_caretVisible(false)
	, m_editing(true)
	, m_caretFlashTimer(0)
{

}



void EditView::draw( GraphicsContext * context, const IntRect& dirtyRect)
{
	__super::draw(context, dirtyRect);
	//if (m_text.length() != 0) {

		context->save();

		context->clip(rect());

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
	//}
	//m_caretPosition = IntPoint(x() + 10, y() + 20);
	drawCaret(context);
}

bool EditView::onEvent( Event& event )
{
	if (event.id() == UIEvent_ButtonDown) {
		m_caretPosition = toIntPoint(event.lparam());
	} else if (event.id() == UIEvent_Char) {
		String c;
		c.append((char)event.wparam());
		setText(c);
	}
	return View::onEvent(event);
}

bool EditView::attribute(const String& name, const String& value )
{
	return View::attribute(name, value);
}

void EditView::drawCaret( GraphicsContext *context )
{
    if (!m_caretFlashTimer) {
        m_caretFlashTimer = new Timer<EditView>(this, &EditView::advanceAnimation);
        m_caretFlashTimer->startRepeating(kCaretFlashEllipse);
    }

    if (m_editing) {
        if (m_caretVisible) {
            Font font(fontDescription(), 0, 0);
			font.update(0);
            int caretHeight = font.fontMetrics().height();

            context->drawLine(IntPoint(m_caretPosition.x(), m_caretPosition.y() - caretHeight), m_caretPosition);
        }
    }

}

void EditView::advanceAnimation(Timer<EditView> *)
{
    m_caretVisible = !m_caretVisible;
    invalidate();
}

void EditView::setText( const String& text )
{
	m_text.append(text);
	invalidate();
}


} //namespace UI
