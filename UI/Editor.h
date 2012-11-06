#ifndef Editor_h__
#define Editor_h__

#include <wtf/RefPtr.h>
#include "View.h"

namespace UI {

class WndHost;

struct CompositionUnderline {
    CompositionUnderline() 
        : startOffset(0), endOffset(0), thick(false) { }
    CompositionUnderline(unsigned s, unsigned e, const Color& c, bool t) 
        : startOffset(s), endOffset(e), color(c), thick(t) { }
    unsigned startOffset;
    unsigned endOffset;
    Color color;
    bool thick;
};


class Editor {
public:
    Editor(WndHost *);
    ~Editor();

    bool canEdit() const;

    // international text input composition
    bool hasComposition() const { return m_editingView; }
    void setComposition(const String&, const Vector<CompositionUnderline>&, unsigned selectionStart, unsigned selectionEnd = 0);
    void confirmComposition();
    void confirmComposition(const String&);
    void cancelComposition();

    IntRect firstRectForCharacterInSelectedRange();
	String getSelectedText();

	void setEditingView(PassRefPtr<View> view) { m_editingView = view; }
private:
    WndHost * m_host;
    RefPtr<View> m_editingView;

};

} //namespace UI

#endif /*Editor_h__*/
