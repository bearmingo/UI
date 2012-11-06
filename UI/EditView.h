#ifndef EditView_h__
#define EditView_h__

#include "Timer.h"
#include "View.h"


namespace UI {

class EditView : public View
{
	UI_VIEW_DECLARE_CLASS_NAME(TextView, "EditView")
public:
    virtual ~EditView() { }

    static PassRefPtr<EditView> create() { return adoptRef(new EditView()); }

    void setText(const String& text);

    //virtual void measure();

    virtual void draw(GraphicsContext * context, const IntRect&);
    virtual bool attribute(const String& name, const String& value);
    virtual bool onEvent(Event& event);
protected:
	void drawCaret(GraphicsContext *context);
    void advanceAnimation(Timer<EditView> *);

    EditView();
private:
    String m_text;
    Timer<EditView> *m_caretFlashTimer;
    bool m_caretVisible;
    bool m_editing;
    IntPoint m_caretPosition;
};

} // namespace UI

#endif /*EditView_h__*/
