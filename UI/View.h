/********************************************************************
	file base:	View.h
	author:		cgm(cgm@eastcom.com)
	created:	2012/08/27
	
	purpose:	
*********************************************************************/
#ifndef __VIEW_H__
#define __VIEW_H__

#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>
#include <wtf/text/CString.h>
#include <wtf/Vector.h>

#include <Windows.h>


#include "IntRect.h"
#include "IntPoint.h"
#include "IntSize.h"
#include "Image.h"
#include "GraphicsTypes.h"
#include "FontDescription.h"
#include "ImageObserver.h"

#include "ViewAttributesHash.h"
#include "LayoutParam.h"

namespace UI {

class GraphicsContext;

class ViewTree;
class Event;


#define UI_VIEW_DECLARE_CLASS_NAME(theClass, classname) \
public: \
	static const char* className() { return classname; } \
	virtual const char* objectClass() { return className(); } 

enum BackgroundImageRepeat {
	NoRepeat = 0x0,
	RepeatX  = 0x1,
	RepeatY	 = 0x2,
	Repeat	 = 0x3,
};


class View
	: public RefCounted<View>
	, ImageObserver
{
public:
	View();

	static const char* className() { return "View"; }
	virtual const char* objectClass() { return className(); }
	bool isClass(const String& cls) { return cls == className(); }
	bool isObject(const String& obj) { return obj == objectClass(); }

	String id() const { return m_id; }
	void setId(String id) 
	{
		ASSERT_WITH_MESSAGE(m_viewTree == NULL && !hasId(), "id can only set once and must set id befor add viewTree");
		//id can only set once
		//must set id before add viewTree
		if (m_viewTree != NULL && hasId())
			return;
		m_id = id; 
	}

	bool hasId() const { return m_id == ""; }

    int left() const { return m_position.x();}
    int right() const { return m_position.maxX(); }
    int top() const { return m_position.y(); }
    int bottom() const { return m_position.maxY(); }
	
	//border + padding + content
	int width() const { return m_position.width(); }
	int height() const { return m_position.height(); }

	int contentX() const { return m_position.x() + layoutParam()->paddingLeft() + layoutParam()->borderSize(); }
	int contentY() const { return m_position.y() + layoutParam()->paddingTop() + layoutParam()->borderSize(); }
	int contentWidth() const { return m_position.width() - layoutParam()->paddingLeft() - layoutParam()->paddingRight() - layoutParam()->borderSize() * 2; }
	int contentHeight() const { return m_position.height() - layoutParam()->paddingTop() - layoutParam()->paddingBottom() - layoutParam()->borderSize() * 2; }
	//extract padding and border;
	IntRect contentRect() const;

	void setLeft(int left) {  m_position.setX(left); }
	void setTop(int top) { m_position.setY(top); }
	void setWidth(int width) { m_position.setWidth(width); }
	void setHeight(int height) { m_position.setHeight(height); }

	void setLocation(const IntPoint& location) { m_position.setLocation(location); }
	void setSize(const IntSize& size) { m_position.setSize(size); }

	int x() const { return m_position.x(); }
	int y() const { return m_position.y(); }
	int maxX() const { return m_position.maxX(); }
	int maxY() const { return m_position.maxY(); }
	IntPoint location() const { return m_position.location(); }
	IntSize size() const { return m_position.size(); }

	//带边缘的长宽度（包含padding)
	int widthWithMargin() const { return m_position.width() + marginLeft() + marginRigth(); }
	int heightWithMargin() const { return m_position.height() + marginTop() + marginBottom(); }

	void setWidthWithMargin(int width) { setWidth(width - marginLeft() - marginRigth()); }
	void setHeightWithMargin(int height) { setHeight(height - marginTop() - marginBottom()); }

	void setSizeWithMargin(int width, int height) { setWidthWithMargin(width); setHeightWithMargin(height); }
	void setSizeWithMargin(const IntSize& size) { setSizeWithMargin(size.width(), size.height()); }

	void setXWithMargin(int x) { setLeft(x + marginLeft()); }
	void setYWithMargin(int y) { setTop(y + marginTop()); }
	void setXYWithMargin(int x, int y) { setXWithMargin(x); setYWithMargin(y); }

	IntRect rect() const { return m_position; }
	void setRect(const IntRect& rect) { m_position = rect; }
	void setRect(int x, int y, int width, int height) { setRect(IntRect(x, y, width, height)); }

	IntRect rectWithMargin() const { 
		return IntRect(
			m_position.x() - marginLeft(), 
			m_position.y() - marginTop(), 
			m_position.width() + marginLeft() + marginRigth(), 
			m_position.height() + marginTop() + marginBottom());
	}

    int paddingLeft() const { return layoutParam()->m_paddingLeft; }
    int paddingRight() const { return layoutParam()->m_paddingRight; }
    int paddingTop() const { return layoutParam()->m_paddingTop; }
    int paddingBottom() const { return layoutParam()->m_paddingBottom; }
    void setPaddingLeft(int left) { layoutParam()->m_paddingLeft = left; }
    void setPaddingTop(int top) { layoutParam()->m_paddingTop = top; }
    void setPaddingRight(int right) { layoutParam()->m_paddingRight = right; }
    void setPaddingBottom(int bottom) { layoutParam()->m_paddingBottom = bottom; }
    void setPadding(int padding) { setPaddingLeft(padding); setPaddingTop(padding); setPaddingRight(padding); setPaddingBottom(padding); }
    void setPadding(int l, int t, int r, int b) { setPaddingLeft(l); setPaddingTop(t); setPaddingRight(r); setPaddingBottom(b); }

    int marginLeft() const { return layoutParam()->m_marginLeft; }
    int marginTop() const { return layoutParam()->m_marginTop; }
    int marginRigth() const { return layoutParam()->m_marginRight; }
    int marginBottom() const { return layoutParam()->m_marginBottom; }
    void setMarginLeft(int left) { layoutParam()->m_marginLeft = left; }
    void setMarginTop(int top) { layoutParam()->m_marginTop = top; }
    void setMarginRight(int right) { layoutParam()->m_marginRight = right; }
    void setMarginBottom(int bottom) { layoutParam()->m_marginBottom = bottom; }
    void setMargin(int margin) { setMarginLeft(margin); setMarginTop(margin); setMarginRight(margin); setMarginBottom(margin); }
    void setMargin(int l, int t, int r, int b) { setMarginLeft(l); setMarginTop(t); setMarginRight(r); setMarginBottom(b); }

	
	AttributeLength attributeOfWidth() const { return layoutParam()->m_attributeOfWidth; }
	AttributeLength attributeOfHeight() const { return layoutParam()->m_attributeOfHeight; }
	
	void setAttributeWidth(AttributeLength attr) { layoutParam()->m_attributeOfWidth = attr; }
	void setAttributeHeight(AttributeLength attr) { layoutParam()->m_attributeOfHeight = attr; }
	

    HorizontalAlignment horizontalAlgin() const { return layoutParam()->m_horizontalAlign; }
    VerticalAlign verticalAlign() const { return layoutParam()->m_verticalAlign; }
    void setHorizontalAlign(HorizontalAlignment align) { layoutParam()->m_horizontalAlign = align; }
    void setVerticalAlign(VerticalAlign align) { layoutParam()->m_verticalAlign = align; }

	Color borderColor() const { return m_borderColor; }
	void setBorderColor(const Color& color) { m_borderColor = color; }

	Color backgroundColor() const { return m_backgroundColor; }
	void setBackgroundColor(const Color& color) { m_backgroundColor = color; }


	int measureHeight() const { m_measureSize.height(); }
	int measureWidth() const { m_measureSize.width(); }
	IntSize measureSize() const { m_measureSize; }
    
    HWND hwndContainer() const { return m_hwndContainer; }
    void setHWNDContainer(HWND hwnd) { m_hwndContainer = hwnd; }

	FontDescription& fontDescription() { return m_fontDescription; }

	//text style
	Color textColor() const { return m_textColor; }
	TextAlign textAlign() const { return m_textAlign; }
	TextBaseline textDecoration() { return m_textDecoration; }

	//virtual function
	virtual void draw(GraphicsContext *context, const IntRect& dirtyRect);

	virtual bool isContainer() { return false; }

	virtual void layout(const LayoutParam& lp);

	virtual void measure();

	virtual void moveXY(int x, int y);
	
	virtual void setViewTree(ViewTree *viewTree) { m_viewTree = viewTree; }
	ViewTree* viewTree() { return m_viewTree; }

	View* parent() { return m_parent; }
	void setParent(View* parent) { m_parent = parent; }

	LayoutParam* layoutParam() const { ASSERT(m_style.get()); return m_style.get(); }

	struct ViewState {
		ViewState() 
			: visible(1)
			, hover(0)
			, enable(1)
			, focued(0)
			, readonly(0)
			, captured(0)
			, transparent(0)
			, needRelayout(1)
			, floatview(0)
		{
		}

		uint32_t visible : 1;
		uint32_t hover: 1;
		uint32_t enable: 1;
		uint32_t focued: 1;
		uint32_t readonly: 1;
		uint32_t captured: 1;
		uint32_t transparent: 1;
		uint32_t dirty: 1;
		uint32_t needRelayout: 1;
		uint32_t floatview: 1;

	};

	bool isVisible() const { return m_state.visible; }
	bool isHover() const { return m_state.hover; }
	bool isFocused() const { return m_state.focued; }
	bool isEnable() const { return m_state.enable; }
	bool isReadonly() const { return m_state.readonly; }
	bool isCaptured() const { return m_state.captured; }
	bool isTransparent() const { return m_state.transparent; }
	bool isDirty() const { return m_state.dirty; }
	bool needRelayout() const { return m_state.needRelayout; }
	bool isFloat() const { return m_state.floatview; }

	/*消息接口，如果消息已处理，则返回true,*/
	virtual bool onEvent(Event& event);

	virtual View* getTopmostChildByPoint(const IntPoint& point) { return this; }

	void invalidate();

	//ImageOberver interface
	virtual void decodedSizeChanged(const Image*, int delta) {};
	virtual void didDraw(const Image*) { };

	virtual bool shouldPauseAnimation(const Image*) { return false; };
	virtual void animationAdvanced(const Image*);

	virtual void changedInRect(const Image*, const IntRect&);

	virtual bool attribute(const String& name, const String& value);
	virtual bool attributeWithHashName(const ViewAttributeName& name, const String& value);

protected:
	void drawBackground(GraphicsContext *context, const IntRect& rc);

private:

    IntRect m_position;

	IntSize m_measureSize;

    HWND m_hwndContainer;

	String m_id;
	ViewTree *m_viewTree;
	View *m_parent;

	ViewState m_state;

	RefPtr<LayoutParam> m_style;

	RefPtr<Image> m_backgroundImage;
	int m_backgroundImageRepeat;
	IntPoint m_backgroundPosition;

	String m_fontFamily;
	int m_fontSize;
	FontWeight m_fontWeight;
	FontItalic m_fontStyle;

	FontDescription m_fontDescription;

	TextAlign m_textAlign;
	TextBaseline m_textDecoration;
	Color m_textColor;

	Color m_backgroundColor;
	Color m_borderColor;
	
};

} // namespace UI

#endif /*__VIEW_H__*/