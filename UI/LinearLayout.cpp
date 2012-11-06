#include "LinearLayout.h"

#include <wtf/DataLog.h>

#include "Common.h"
namespace UI {



void LinearLayout::layoutVertical(const LayoutParam& lp)
{	
	//先计算WrapContent的子结点
	IntPoint location;
	location.setX(this->location().x() + layoutParam()->paddingLeft() + layoutParam()->borderSize());
	location.setY(this->location().y() + layoutParam()->paddingTop() + layoutParam()->borderSize());

	int contentMaxX = this->maxX() - layoutParam()->paddingRight() - layoutParam()->borderSize();
	int contentWidth = this->contentWidth();

	for (ViewVector::iterator it = m_children.begin(); it != m_children.end(); it++) {
		LayoutParam* childStyle = (*it)->layoutParam();
		if (!childStyle)
			continue;

		IntPoint tempLocation;
		switch (childStyle->horizontalAlgin()) {
		case AlignHCenter:
			tempLocation.setX(location.x() + childStyle->marginLeft() + (contentWidth - (*it)->widthWithMargin()) / 2);
			break;
		case AlignLeft:
			tempLocation.setX(location.x() + childStyle->marginLeft());
			break;
		case AlignRight:
			tempLocation.setX(contentMaxX - (*it)->width() - childStyle->marginRight());
			break;
		}

		tempLocation.setY(location.y() + childStyle->marginTop());

		(*it)->setLocation(tempLocation);
		(*it)->layout(lp);

		location.setY(location.y() + (*it)->heightWithMargin());

	}

}

void LinearLayout::layoutHorizontal(const LayoutParam& lp)
{
	IntPoint location;
	location.setX(this->location().x() + layoutParam()->paddingLeft() + layoutParam()->borderSize());
	location.setY(this->location().y() + layoutParam()->paddingTop() + layoutParam()->borderSize());

	int contentMaxY = this->maxY() - layoutParam()->paddingBottom() - layoutParam()->borderSize();
	int contentHeight = this->contentHeight();

	for(ViewVector::iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {
		LayoutParam *childStyle = (*it)->layoutParam();
		if (!childStyle)
			continue;

		IntPoint tempLocation;
		switch (childStyle->verticalAlign()) {
		case AlignTop:
			tempLocation.setY(location.y() + childStyle->marginTop());
			break;
		case AlignCenterV:
			tempLocation.setY(location.y() + childStyle->marginTop() + (contentHeight - (*it)->heightWithMargin()) / 2);
			break;
		case AlignBottom:
			tempLocation.setY(contentMaxY - (*it)->heightWithMargin() - childStyle->marginBottom());
			break;
		}

		tempLocation.setX(location.x() + childStyle->marginLeft());

		(*it)->setLocation(tempLocation);
		(*it)->layout(lp);
		
		location.setX(location.x() + (*it)->widthWithMargin());
	}
}

void LinearLayout::measureVertical()
{
	int maxContentWidth = 0;
	int maxContentHeight = 0;

	/*
	 * 首先检查子结点中长或宽属性为Wrap Content的节点，调用子节点的measure计算长宽，
	 * 记录宽度最大的节点的宽度(带margin)和所有子节点的高度(带margin)
	 */
	for (ViewVector::iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {
		LayoutParam* childLayoutParam = (*it)->layoutParam();
		if (!childLayoutParam)
			continue;

		if (childLayoutParam->attributeOfHeight() == FillParent) {
			UI_LOG_VERBOSE("LinearLayout 子节点高度为FillParent, 不支持此属性");
			//childStyle->setAttributeHeight(WrapContent);
		}

		if (childLayoutParam->attributeOfHeight() == Fixed)
			(*it)->setHeight(childLayoutParam->height());

		if (childLayoutParam->attributeOfWidth() == Fixed)
			(*it)->setWidth(childLayoutParam->width());
		//先检查子结点中高度属性为Wrap Content的节点

		if (childLayoutParam->attributeOfHeight() != WrapContent || childLayoutParam->attributeOfWidth() != FillParent)
			(*it)->measure();

		//记录宽度最大的节点的宽度(带margin), 除宽度为FillParent的子结点。
		int childWidthWithMargin = (*it)->widthWithMargin();
		if (childLayoutParam->attributeOfWidth() != FillParent && maxContentWidth < childWidthWithMargin)
			maxContentWidth = childWidthWithMargin;

		//所有子节点的高度(带margin)
		maxContentHeight += (*it)->heightWithMargin();
	}

	//if parent's height attribute is WrapContent, set parent's height
	if (attributeOfHeight() == WrapContent)
		setHeight(maxContentHeight + layoutParam()->paddingTop() + layoutParam()->paddingBottom() + layoutParam()->borderSize() * 2);

	//if parent's width attributes is WrapContent, set parent's width
	if (attributeOfWidth() == WrapContent)
		setWidth(maxContentWidth + layoutParam()->paddingLeft() + layoutParam()->paddingRight() + layoutParam()->borderSize() * 2);

	//recalculate child height and weight
	for (ViewVector::iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {
		LayoutParam* childLayoutParam = (*it)->layoutParam();
		if (!childLayoutParam)
			continue;

		//if attribute of child's width is FillParent, set child's width with width of parent's content
		if (childLayoutParam->attributeOfWidth() == FillParent && childLayoutParam->attributeOfHeight() == WrapContent) {
			(*it)->setWidthWithMargin(contentWidth());
			(*it)->measure();
		}

	}

}

void LinearLayout::measureHorizontal()
{
	int maxWidth = 0;
	int maxHeight = 0;

	for (ViewVector::iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {
		LayoutParam* childLayoutParam = (*it)->layoutParam();
		if (!childLayoutParam)
			continue;

		if (childLayoutParam->attributeOfWidth() == FillParent) {
			UI_LOG_VERBOSE("LinearLayout 子节点宽度为FillParent, 不支持此属性");
			//childStyle->setAttributeWidth(WrapContent);
		}
		
		//if attribute of child's height is Fixed, set child height width it's fixed width
		if (childLayoutParam->attributeOfHeight() == Fixed)
			(*it)->setHeight(childLayoutParam->height());

		if (childLayoutParam->attributeOfWidth() == Fixed)
			(*it)->setWidth(childLayoutParam->width());

		// calculate child's width and height if attributes of it's width or height are WrapContent
		if (childLayoutParam->attributeOfWidth() != WrapContent || childLayoutParam->attributeOfHeight() != FillParent)
			(*it)->measure();

		//get max height of children
		int childHeightWithMargin = (*it)->heightWithMargin();
		if (childLayoutParam->attributeOfHeight() != FillParent && maxHeight < childHeightWithMargin)
			maxHeight = childHeightWithMargin;

		maxWidth += (*it)->widthWithMargin();
	}

	if (layoutParam()->attributeOfWidth() == WrapContent)
		setWidth(maxWidth + layoutParam()->paddingLeft() + layoutParam()->paddingRight() + layoutParam()->borderSize() * 2);
	if (layoutParam()->attributeOfHeight() == WrapContent)
		setHeight(maxHeight + layoutParam()->paddingTop() + layoutParam()->paddingBottom() + layoutParam()->borderSize() * 2);

	for (ViewVector::iterator it = m_children.begin(), end = m_children.end(); it != end; it++) {
		LayoutParam* childLayoutParam = (*it)->layoutParam();
		if (!childLayoutParam)
			continue;

		if (childLayoutParam->attributeOfHeight() == FillParent && childLayoutParam->attributeOfWidth() == WrapContent)
			(*it)->setHeightWithMargin(contentHeight());
	}
}

void LinearLayout::layout( const LayoutParam& lp )
{
	if (m_orientation == Horizontal)
		layoutHorizontal(lp);
	else
		layoutVertical(lp);
}

void LinearLayout::measure()
{
	if (m_orientation == Horizontal)
		measureHorizontal();
	else
		measureVertical();
}

LinearLayout::LinearLayout( Container *parent )
{
	ASSERT(parent);
	parent->addChild(this);
}

bool LinearLayout::attribute( const String& name, const String& value )
{
	if (name == "orientation") {
		if (value == "vertical")
			m_orientation = Vertical;
		else if (value == "horizontal")
			m_orientation = Horizontal;
		return true;
	}

	return __super::attribute(name, value);
}


}