#include "Editor.h"

#include "EditView.h"

namespace UI {

Editor::Editor( WndHost * host)
	:m_host(host)
{

}

Editor::~Editor()
{

}

bool Editor::canEdit() const
{
	return !m_editingView;
}

void Editor::setComposition( const String&, const Vector<CompositionUnderline>&, unsigned selectionStart, unsigned selectionEnd0)
{

}

void Editor::confirmComposition()
{

}

void Editor::confirmComposition( const String& text)
{
	if (m_editingView) {
		reinterpret_cast<EditView *>(m_editingView.get())->setText(text);
	}
}

void Editor::cancelComposition()
{

}

IntRect Editor::firstRectForCharacterInSelectedRange()
{
	if (canEdit()) {
		return IntRect(m_editingView->x() + 10, m_editingView->y() + 10, 10, 10);
	}

	return IntRect();
}

String Editor::getSelectedText()
{
	return String();
}

} //namespace UI