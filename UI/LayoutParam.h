#ifndef LayoutParam_h__
#define LayoutParam_h__

#include <wtf/FastMalloc.h>
#include <wtf/RefCounted.h>
#include <wtf/PassRefPtr.h>


#include "IntRect.h"
#include "Color.h"
#include "GraphicsTypes.h"

namespace UI {


enum VerticalAlign {
	AlignTop    = 0x0,
	AlignCenterV,
	AlignBottom,
};

enum {
	Invisible,
	Visible,
	Gone,
};

typedef enum {
	Fixed = 0,
	FillParent = 1,
	WrapContent = 2,
} AttributeLength;

class View;

class LayoutParam : public RefCounted<LayoutParam>
{
	WTF_MAKE_FAST_ALLOCATED;
public:

	static PassRefPtr<LayoutParam> create() { return adoptRef(new LayoutParam()); }
	//PassRefPtr<Style> create(const Style * style) { return adoptRef(new Style(*style)); }

	int x() const { return m_position.x(); }
	int y() const { return m_position.y(); }
	void setX(int x) { m_position.setX(x); }
	void setY(int y) { m_position.setY(y); }

	int width() const { return m_position.width(); }
	int height() const { return m_position.height(); }
	void setWidth(int w) { m_position.setWidth(w); }
	void setHeight(int h) { m_position.setHeight(h); }

	int marginLeft() const { return m_marginLeft; }
	int marginRight() const { return m_marginRight; }
	int marginTop() const { return m_marginTop; }
	int marginBottom() const { return m_marginBottom; }
	void setMarginLeft(int left) { m_marginLeft = left; }
	void setMarginTop(int top) { m_marginTop = top; }
	void setMarginRight(int right) { m_marginRight = right; }
	void setMarginBottom(int bottom) { m_marginBottom = bottom; }
	void setMargin(int margin) { setMarginLeft(margin); setMarginTop(margin); setMarginRight(margin); setMarginBottom(margin); }
	void setMargin(int l, int t, int r, int b) { setMarginLeft(l); setMarginTop(t); setMarginRight(r); setMarginBottom(b); }

	int borderLeft() const { return m_boldSize; }
	int borderRight() const { return m_boldSize; }
	int borderTop() const { return m_boldSize; }
	int borderBottom() const { return m_boldSize; }

	int paddingLeft() const { return m_paddingLeft; }
	int paddingRight() const { return m_paddingRight; }
	int paddingTop() const { return m_paddingTop; }
	int paddingBottom() const { return m_paddingBottom; }
	void setPaddingLeft(int left) { m_paddingLeft = left; }
	void setPaddingTop(int top) { m_paddingTop = top; }
	void setPaddingRight(int right) { m_paddingRight = right; }
	void setPaddingBottom(int bottom) { m_paddingBottom = bottom; }
	void setPadding(int padding) { setPaddingLeft(padding); setPaddingTop(padding); setPaddingRight(padding); setPaddingBottom(padding); }
	void setPadding(int l, int t, int r, int b) { setPaddingLeft(l); setPaddingTop(t); setPaddingRight(r); setPaddingBottom(b); }

	AttributeLength attributeOfWidth() const { return m_attributeOfWidth; }
	AttributeLength attributeOfHeight() const { return m_attributeOfHeight; }

	void setAttributeWidth(AttributeLength attr) { m_attributeOfWidth = attr; }
	void setAttributeHeight(AttributeLength attr) { m_attributeOfHeight = attr; }

	HorizontalAlignment horizontalAlgin() const { return m_horizontalAlign; }
	VerticalAlign verticalAlign() const { return m_verticalAlign; }
	void setHorizontalAlign(HorizontalAlignment align) { m_horizontalAlign = align; }
	void setVerticalAlign(VerticalAlign align) { m_verticalAlign = align; }

	void setBoldSize(int size) { m_boldSize = size; }
	int borderSize() const { return m_boldSize; }

	void setBoldRadius(int radius) { m_boldRadius = radius; }
	int borderRadius() const { return m_boldRadius; }



	friend class View;

	LayoutParam();

private:
	
	//border + padding + content
	IntRect m_position;

	AttributeLength m_attributeOfWidth;
	AttributeLength m_attributeOfHeight;
	
	//unused now
	int m_borderLeft;
	int m_borderRight;
	int m_borderTop;
	int m_borderBottom;

	int m_paddingLeft;
	int m_paddingTop;
	int m_paddingRight;
	int m_paddingBottom;

	int m_marginLeft;
	int m_marginTop;
	int m_marginRight;
	int m_marginBottom;

	/**/
	HorizontalAlignment m_horizontalAlign;
	VerticalAlign m_verticalAlign;

	
	int m_boldSize;
	int m_boldRadius;

	

};

}
#endif /*LayoutParam_h__*/

