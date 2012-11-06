#ifndef ViewAttributesHash_h__
#define ViewAttributesHash_h__

namespace UI {

enum ViewAttributeValue {
    Attr_Padding,
    Attr_PaddingLeft,
    Attr_PaddingRight,
    Attr_PaddingTop,
    Attr_PaddingBottom,
    Attr_Margin,
    Attr_MarginLeft,
    Attr_MarginRight,
    Attr_MarginTop,
    Attr_MarginBottom,
    Attr_PositionWidth,
    Attr_PositionHeight,
    Attr_PositionX,
    Attr_PositionY,
    Attr_Position,
    Attr_BorderColor,
    Attr_BorderWidth,
	Attr_BorderRadius,
    Attr_VAlign,
    Attr_HAlign,
    Attr_BackgroundColor,
    Attr_BackgroundImage,
    Attr_BackgroundRepeat,
    Attr_BackgroundPosition,
    Attr_Id,
    Attr_FontSize,
    Attr_FontFamily,
    Attr_FontWeight,
    Attr_FontStyle,
    Attr_TextAlign,
    Attr_TextDecoration,
    Attr_TextColor,
};

struct ViewAttributeName {
	const char* name;
	ViewAttributeValue attrValue;
};

const ViewAttributeName* findViewAttribute(register const char *str, register unsigned int len);

} //namespace UI

#endif /*Viewattributeshash_h__*/
