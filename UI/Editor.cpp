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
	return !!m_editingView;
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
		reinterpret_cast<EditView *>(m_editingView.get())->onCompositionString(text);
	}
}

void Editor::cancelComposition()
{

}

IntRect Editor::firstRectForCharacterInSelectedRange()
{
	if (canEdit()) {
		return reinterpret_cast<EditView *>(m_editingView.get())->firstRectForCharacterInSelectedRange();
	}

	return IntRect();
}

String Editor::getSelectedText()
{
	return String();
}

void Editor::setEditingView( PassRefPtr<View> view )
{
	if (view == m_editingView)
		return;

	if (m_editingView)
		reinterpret_cast<EditView *>(m_editingView.get())->endEdit();

	m_editingView = view;

	if (m_editingView)
		reinterpret_cast<EditView *>(m_editingView.get())->startEdit();
}

} //namespace UI