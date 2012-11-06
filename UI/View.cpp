#include "View.h"

#include "GraphicsContext.h"
#include "Color.h"
#include "IntRect.h"
#include "FontStyle.h"
#include "BitmapImage.h"
#include "SharedBuffer.h"

#include "Event.h"
#include "ViewTree.h"
#include "WndHost.h"

#include "Common.h"
#include "ImageManager.h"

#include "ViewAttributesHash.h"

namespace UI {


View::View()
	: m_hwndContainer(NULL)
	, m_viewTree(0)
	, m_parent(0)
	, m_backgroundImageRepeat(NoRepeat)
	, m_borderColor(Color::darkGray)
	, m_backgroundColor(Color::transparent)
	, m_fontSize(11)
	, m_fontFamily("Î¢ÈíÑÅºÚ")
	, m_fontStyle(FontItalicOff)
	, m_fontWeight(FontWeightNormal)
{
	m_style = LayoutParam::create();

	FontFamily family;
	family.setFamily("Î¢ÈíÑÅºÚ");
	m_fontDescription.setFamily(family);
	m_fontDescription.setSpecifiedSize(12);
	m_fontDescription.setComputedSize(12);
	
}

void View::draw( GraphicsContext *context , const IntRect& dirtyRect)
{
	ASSERT(layoutParam());
	if (!layoutParam())
		return;

	if (!dirtyRect.intersects(rect()))
		return;

	context->save();

	context->setShouldAntialias(false);

	//context->setFillColor(backgroundColor(), ColorSpaceSRGB);
	context->setCompositeOperation(CompositeCopy);

	// draw border
	IntRect borderRect(x() + 1, y() + 1, width() - 1, height() - 1);
	IntRect fill(x(), y(), width(), height());

	context->setStrokeColor(borderColor(), ColorSpaceSRGB);
	//context->setStrokeStyle(DashedStroke);

	if (layoutParam()->borderRadius() == 0) {
		context->strokeRect(borderRect, layoutParam()->borderSize());
	} else {
		Path path;
// 		path.addArc(borderRect.minXMinYCorner(), layoutParam()->borderRadius(), 270.0, 180.0, false);
// 		path.addArc(borderRect.maxXMinYCorner(), layoutParam()->borderRadius(), 270.0, 0.0, false);
// 		path.addArc(borderRect.maxXMaxYCorner(), layoutParam()->borderRadius(), 0.0, 90.0, false);
// 		path.addArc(borderRect.minXMaxYCorner(), layoutParam()->borderRadius(), 90.0, 180.0, false);
		path.addRoundedRect(borderRect, FloatSize(layoutParam()->borderRadius(), layoutParam()->borderRadius()));

		context->strokePath(path);
	}

	IntRect clipRect(contentRect());

	context->setFillColor(Color("white"), ColorSpaceSRGB);
	//context->fillRect(contentRect());
	context->clip(clipRect);

	drawBackground(context, dirtyRect);

	context->restore();
}

void View::moveXY( int x, int y )
{
	m_position.move(x, y);
}

void View::layout( const LayoutParam& lp )
{
}

void View::measure()
{
	m_position.setWidth(layoutParam()->width());
	m_position.setHeight(layoutParam()->height());
}

IntRect View::contentRect() const
{
	IntRect contentRect;
	contentRect.setX(m_position.x() + layoutParam()->paddingLeft() + layoutParam()->borderSize());
	contentRect.setY(m_position.y() + layoutParam()->paddingTop() + layoutParam()->borderSize());
	contentRect.setWidth(contentWidth());
	contentRect.setHeight(contentHeight());

	return contentRect;
}

bool View::onEvent( Event& event )
{
	if (event.isWindowEvent()) {
		switch(event.id()) {
		case UIEvent_MouseEnter:
			m_state.hover = true;
			invalidate();
			UI_LOG_VERBOSE("Hover");
			return true;

		case UIEvent_MouseLeave:
			m_state.hover = false;
			invalidate();
			UI_LOG_VERBOSE("Leave");
			return true;
		}
	}
	return false;
}

void View::invalidate()
{
	if (viewTree() && viewTree()->wndHost()) {
		viewTree()->wndHost()->invalidateRect(rect());
	}
}

void View::changedInRect( const Image*, const IntRect& )
{
	printf("aaa");
}

void View::animationAdvanced( const Image* image)
{
	invalidate();
}

static inline const ViewAttributeName* findViewAttribute(const String& name)
{
	char buffer[128]; // easily big enough for the longest color name
	unsigned length = name.length();
	if (length > sizeof(buffer) - 1)
		return 0;
	for (unsigned i = 0; i < length; ++i) {
		UChar c = name[i];
		if (!c || c > 0x7F)
			return 0;
		buffer[i] = toASCIILower(static_cast<char>(c));
	}
	buffer[length] = '\0';
	return findViewAttribute(buffer, length);
}


bool View::attribute( const String& name, const String& value )
{
	String nameTmp = name;
	const ViewAttributeName* attrName = findViewAttribute(nameTmp);
	if (!attrName)
		return false;
	return attributeWithHashName(*attrName, value);
}

bool View::attributeWithHashName(const ViewAttributeName& name, const String& value )
{
	switch (name.attrValue) {
	case Attr_Id:
		setId(value);
		break;
	case Attr_Padding:
		layoutParam()->setPadding(value.toInt());
		break;
	case Attr_PaddingLeft:
		layoutParam()->setPaddingLeft(value.toInt());
		break;
	case Attr_PaddingTop:
		layoutParam()->setPaddingTop(value.toInt());
		break;
	case Attr_PaddingRight:
		layoutParam()->setPaddingRight(value.toInt());
		break;
	case Attr_PaddingBottom:
		layoutParam()->setPaddingBottom(value.toInt());
		break;
	case Attr_Margin:
		layoutParam()->setMargin(value.toInt());
		break;
	case Attr_MarginTop:
		layoutParam()->setMarginTop(value.toInt());
		break;
	case Attr_MarginRight:
		layoutParam()->setMarginRight(value.toInt());
		break;
	case Attr_MarginBottom:
		layoutParam()->setMarginBottom(value.toInt());
		break;
	case Attr_MarginLeft:
		layoutParam()->setMarginLeft(value.toInt());
		break;
	case Attr_PositionX:
		layoutParam()->setX(value.toInt());
		break;
	case Attr_PositionY:
		layoutParam()->setY(value.toInt());
		break;
	case Attr_PositionWidth: 
		{
			if (value == "fill_parent")
				layoutParam()->setAttributeWidth(FillParent);
			else if (value == "wrap_content")
				layoutParam()->setAttributeWidth(WrapContent);
			else {
				layoutParam()->setWidth(value.toInt());
				layoutParam()->setAttributeWidth(Fixed);
			}
		}
		break;
	case Attr_PositionHeight:
		{
			if (value == "fill_parent")
				layoutParam()->setAttributeHeight(FillParent);
			else if (value == "wrap_content")
				layoutParam()->setAttributeHeight(WrapContent);
			else {
				layoutParam()->setHeight(value.toInt());
				layoutParam()->setAttributeHeight(Fixed);
			}
		}
		break;

	case Attr_VAlign:
		{
			VerticalAlign align;
			if (value == "center")
				align = AlignCenterV;
			else if (value == "bottom")
				align = AlignBottom;
			else if (value == "top")
				align = AlignTop;
			else
				break;

			layoutParam()->setVerticalAlign(align);
		}
		break;
	case Attr_HAlign:
		{
			HorizontalAlignment align;
			if (value == "center")
				align = AlignHCenter;
			else if (value == "right")
				align = AlignRight;
			else if (value == "left")
				align = AlignLeft;
			else
				break;

			layoutParam()->setHorizontalAlign(align);
		}
		break;
	case Attr_BorderColor:
		{
			Color color(value);
			if (color.isValid())
				setBorderColor(color);
		}
		break;
	case Attr_BorderWidth:
		layoutParam()->setBoldSize(value.toInt());
		break;

	case Attr_BorderRadius:
		layoutParam()->setBoldRadius(value.toInt());
		break;

	case Attr_BackgroundColor:
		{
			Color color(value);
			if (color.isValid())
				setBackgroundColor(color);
		}
		break;
	case Attr_BackgroundImage:
		{
			RefPtr<SharedBuffer> sharedBuffer  = ImageFileManager::get(value);
			RefPtr<BitmapImage> image = BitmapImage::create();
			image->setData(sharedBuffer, true);
			image->setImageObserver(this);

			m_backgroundImage = image.release();
		}
		break;
	case Attr_BackgroundRepeat:
		{
			if (value == "no-repeat") {
				m_backgroundImageRepeat = NoRepeat;
			} else if (value == "repeat") {
				m_backgroundImageRepeat = Repeat;
			} else if (value == "repeat-x") {
				m_backgroundImageRepeat |= RepeatX;
			} else if (value == "repeat-y") {
				m_backgroundImageRepeat |= RepeatY;
			}
		}
		break;
	case Attr_BackgroundPosition:
		ASSERT(0);
		break;
	case Attr_FontFamily:
		{
			FontFamily family;
			family.setFamily(value);
			m_fontDescription.setFamily(family);
		}
		break;
	case Attr_FontSize: 
		{
			int size = value.toInt();
			m_fontDescription.setSpecifiedSize(size);
			m_fontDescription.setComputedSize(size);
		}
		break;
	case Attr_FontWeight:
		{
			if (value == "normal") {
				m_fontDescription.setWeight(FontWeightNormal);
			} else if (value == "bold") {
				m_fontDescription.setWeight(FontWeightBold);
			} else {
				bool ok = true;
				int valueTemp = value.toInt(&ok);
				if (ok) {
					switch (valueTemp) {
					case 100: m_fontDescription.setWeight(FontWeight100); break;
					case 200: m_fontDescription.setWeight(FontWeight200); break;
					case 300: m_fontDescription.setWeight(FontWeight300); break;
					case 400: m_fontDescription.setWeight(FontWeight400); break;
					case 500: m_fontDescription.setWeight(FontWeight500); break;
					case 600: m_fontDescription.setWeight(FontWeight600); break;
					case 700: m_fontDescription.setWeight(FontWeight700); break;
					case 800: m_fontDescription.setWeight(FontWeight800); break;
					case 900: m_fontDescription.setWeight(FontWeight900); break;
					}
				}

			}
		}
		break;
	case Attr_FontStyle:
		{
			if (value == "normal") {
				m_fontDescription.setItalic(false);
			} else if (value == "italic" || value == "oblique") {
				m_fontDescription.setItalic(true);
			}
		}
	case Attr_TextAlign:
		{
			if (value == "left") {
				m_textAlign = LeftTextAlign;
			} else if (value == "right") {
				m_textAlign = RightTextAlign;
			} else if (value == "center") {
				m_textAlign = CenterTextAlign;
			}
		}
		break;
	case Attr_TextDecoration:
		{
			if (value == "none") {
				m_textDecoration = AlphabeticTextBaseline;
			} else if (value == "underline") {
				m_textDecoration = BottomTextBaseline;
			} else if (value == "overline") {
				m_textDecoration = TopTextBaseline;
			} else if (value == "line-through") {
				m_textDecoration = MiddleTextBaseline;
			}
		}
		break;
	case Attr_TextColor:
		{
			Color color(value);
			if (color.isValid())
				m_textColor = color;
		}
	}

	return true;
}

void View::drawBackground( GraphicsContext *context, const IntRect& rc )
{
	IntRect backgroundRect;
	backgroundRect.setX(x() + layoutParam()->borderLeft());
	backgroundRect.setY(y() + layoutParam()->borderTop());
	backgroundRect.setWidth(width() - layoutParam()->borderLeft() - layoutParam()->borderRight());
	backgroundRect.setHeight(height() - layoutParam()->borderTop() - layoutParam()->borderBottom());

 	if (m_backgroundColor.isValid() && m_backgroundColor.alpha()) {
		context->save();
 		context->setFillColor(m_backgroundColor, ColorSpaceLinearRGB);
		context->setAlpha(m_backgroundColor.alpha());
 		context->fillRect(backgroundRect);
		context->restore();
 	}

	if (!!m_backgroundImage) {
		context->setShouldAntialias(true);

		if (m_backgroundImageRepeat == NoRepeat)
			context->drawImage(m_backgroundImage.get(), ColorSpaceLinearRGB, contentRect());
		else {
			IntRect imageRect(IntPoint(0, 0), m_backgroundImage->size());
			context->drawTiledImage(m_backgroundImage.get(), ColorSpaceLinearRGB, contentRect(), imageRect, FloatSize(1, 1), Image::RepeatTile, Image::RepeatTile);
		}
	}

}





} //namespace UI