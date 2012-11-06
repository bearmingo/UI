#include "LayoutParam.h"

namespace UI {


LayoutParam::LayoutParam()
	: m_borderLeft(0), m_borderRight(0), m_borderTop(0), m_borderBottom(0)
	, m_paddingLeft(0), m_paddingRight(0), m_paddingTop(0), m_paddingBottom(0)
	, m_marginLeft(0), m_marginRight(0), m_marginTop(0), m_marginBottom(0)
	, m_attributeOfHeight(Fixed), m_attributeOfWidth(Fixed)
	, m_horizontalAlign(AlignLeft)
	, m_verticalAlign(AlignTop)
	, m_boldSize(1)
	, m_boldRadius(0)
{

}

}