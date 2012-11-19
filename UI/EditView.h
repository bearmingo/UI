#ifndef EditView_h__
#define EditView_h__

#include "Timer.h"
#include "View.h"


namespace UI {

class EditView : public View
{
	UI_VIEW_DECLARE_CLASS_NAME(TextView, "EditView")
public:
    virtual ~EditView();

    static PassRefPtr<EditView> create() { return adoptRef(new EditView()); }

    void setText(const String& text);

	//for get text from ime
	void onCompositionString(const String& text);
	void startEdit();
	void endEdit();
	IntRect firstRectForCharacterInSelectedRange();

    //virtual void measure();

    virtual void draw(GraphicsContext * context, const IntRect&);
    virtual bool attribute(const String& name, const String& value);
    virtual bool onEvent(Event& event);
protected:
	void drawCaret(GraphicsContext *context);
    void advanceAnimation(Timer<EditView> *);

	void onEventChar(UChar ch, unsigned int repeatCount, unsigned int flag);
	void onEventKeyDown(UChar ch, unsigned int repeatCount, unsigned int flag);
	void onLButtonDown(const IntPoint& point);


	void updateCaretPosition();

	void onLButtonUp(const IntPoint& point);
	void onMouseMove(unsigned int flag, IntPoint& point);

	int calcuateCaretRectFromPoint(const IntPoint& point, IntRect&);

    EditView();
private:
    String m_text;
    Timer<EditView> *m_caretFlashTimer;
    bool m_caretVisible;
    bool m_editing;
    IntRect m_caretRect;
	int m_caretPosAtString;

	bool m_lButtonDown;
	//IntRect m_selectedRange;
	int m_selectedFrom;
	int m_selectedTo;
};

} // namespace UI

#endif /*EditView_h__*/
