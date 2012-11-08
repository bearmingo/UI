#include "EditView.h"


#include "GraphicsContext.h"
#include "font.h"
#include "TextRun.h"
#include "WidthIterator.h"
#include "Event.h"


namespace UI {

const double kCaretFlashEllipse = 0.5;
const double kProcessCharInterval = 0.01;


EditView::EditView()
	: m_caretVisible(false)
	, m_editing(false)
	, m_caretFlashTimer(0)
	, m_caretPosAtString(0)
{

}



void EditView::draw( GraphicsContext * context, const IntRect& dirtyRect)
{
	__super::draw(context, dirtyRect);

	context->save();

	context->clip(rect());

	Font font(fontDescription(), 0, 0);
	font.update(0);

	TextRun textRun(m_text);
	context->setFillColor(textColor(), ColorSpaceDeviceRGB);

	//calculate text
	IntSize textRect(font.width(textRun), font.fontMetrics().height());
	IntRect content(contentRect());

	context->drawText(font, textRun, FloatPoint(contentX(), contentY() + font.fontMetrics().ascent()));
	//context->drawEmphasisMarks(font, textRun, "?", FloatPoint(contentX(), contentY() + font.fontMetrics().height()), 11);

	if (m_editing) {
		if (m_caretVisible) {
			int caretHeight = font.fontMetrics().height(IdeographicBaseline);

			context->drawLine(m_caretRect.minXMinYCorner(), m_caretRect.maxXMaxYCorner());
		}
	}

	context->restore();
}

bool EditView::onEvent( Event& event )
{
	switch (event.id()) {
	case UIEvent_ButtonDown:
		onLButtonDown(toIntPoint(event.lparam()));
		break;
	case UIEvent_Char:
		onEventChar((UChar)event.wparam(), (unsigned int)event.lparam() & 0xFFFF, 
			(unsigned)((event.lparam() & 0xFFFF0000) >> 16));
		break;
	case UIEvent_KeyDown:
		onEventKeyDown((UChar)event.wparam(), (unsigned int)event.lparam() & 0xFFFF, 
			(unsigned)((event.lparam() & 0xFFFF0000) >> 16));
		break;
	default:
		break;
	}
	return View::onEvent(event);
	
}

bool EditView::attribute(const String& name, const String& value )
{
	return View::attribute(name, value);
}

void EditView::drawCaret( GraphicsContext *context )
{
// 	ASSERT(m_editing);
// 
//     if (!m_caretFlashTimer) {
//         m_caretFlashTimer = new Timer<EditView>(this, &EditView::advanceAnimation);
//         m_caretFlashTimer->startRepeating(kCaretFlashEllipse);
//     }


    


}

void EditView::advanceAnimation(Timer<EditView> *timer)
{
	if (timer == m_caretFlashTimer) {
		m_caretVisible = !m_caretVisible;
		invalidate();
	}
}

void EditView::setText( const String& text )
{
	m_text = text;
	//TODO reset caret
	invalidate();
}

void EditView::onCompositionString( const String& text )
{
	m_text.insert(text, m_caretPosAtString);
	m_caretPosAtString += text.length();
	updateCaretPosition();
	invalidate();
}

void EditView::onEventChar(UChar ch, unsigned int repeatCount, unsigned int flag)
{

	if (ch == VK_BACK) {
		if (m_caretPosAtString == 0)
			return;
		else {
			m_text.remove(m_caretPosAtString - 1);
			m_caretPosAtString -= 1;
		}
	} else if (ch >= L' ' && ch <= L'~'){
		String temp;
		temp.append(ch);

		m_text.insert(temp, m_caretPosAtString);
		m_caretPosAtString += 1;
	}
	updateCaretPosition();

	invalidate();

}

EditView::~EditView()
{
	if (m_caretFlashTimer != 0) {
		delete m_caretFlashTimer;
	}
}

void EditView::onLButtonDown( const IntPoint& point )
{
	Font font(fontDescription(), 0, 0);
	font.update(0);

	if (m_text.length() == 0) {
		m_caretRect = IntRect(contentX(), contentY(), 0, font.fontMetrics().height());
		return;
	}
	
	TextRun textRun(m_text);

	GlyphBuffer glyphBuffer;

	WidthIterator it(&font, textRun, 0, false, false);
	it.advance(0);
	it.advance(textRun.length(), &glyphBuffer);

	float nextX = contentX();
	float lastX;

	for (int i = 0; i < glyphBuffer.size(); i++) {
		lastX = nextX;
		nextX += glyphBuffer.advanceAt(i);
		
		if (point.x() < nextX) {
			m_caretRect = IntRect(lastX, contentY(), 0, font.fontMetrics().height());
			m_caretPosAtString = i;
			return;
		}
	}

	m_caretRect = IntRect(lastX, contentY(), 0, font.fontMetrics().height());
	m_caretPosAtString = m_text.length();
}

void EditView::updateCaretPosition()
{
	Font font(fontDescription(), 0, 0);
	font.update(0);

	TextRun textRun(m_text);
	GlyphBuffer glyphBuffer;
	WidthIterator it(&font, textRun, 0, false, false);
	it.advance(0);
	it.advance(textRun.length(), &glyphBuffer);

	int xpos;
	if (m_caretPosAtString == 0)
		xpos = contentX();
	else {
		xpos = contentX();
		for (int i = 0; i < m_caretPosAtString; i++) {
			xpos += glyphBuffer.advanceAt(i);
		}
	}

	m_caretRect = IntRect(xpos, contentY(), 0, font.fontMetrics().height());

}

void EditView::onEventKeyDown( UChar ch, unsigned int repeatCount, unsigned int flag )
{
	if (ch == VK_LEFT) {
		if (m_caretPosAtString == 0)
			return;
		m_caretPosAtString -= 1;

		updateCaretPosition();
		invalidate();
	} if (ch == VK_RIGHT) {
		if (m_caretPosAtString == m_text.length())
			return;
		m_caretPosAtString += 1;

		updateCaretPosition();
		invalidate();
	}
}

void EditView::startEdit()
{
	m_editing = true;

	if (!m_caretFlashTimer) {
		m_caretFlashTimer = new Timer<EditView>(this, &EditView::advanceAnimation);
		m_caretFlashTimer->startRepeating(kCaretFlashEllipse);
	}
}

void EditView::endEdit()
{
	m_editing = false;

	if (m_caretFlashTimer) {
		delete m_caretFlashTimer;
		m_caretFlashTimer = 0;
	}
}

IntRect EditView::firstRectForCharacterInSelectedRange()
{
	return m_caretRect;
}





} //namespace UI
