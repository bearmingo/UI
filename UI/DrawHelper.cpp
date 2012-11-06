#include "DrawHelper.h"

#include <math.h>

#include <wtf/Assertions.h>
#include <wtf/text/CString.h>

#include <Windows.h>
#include <WindowsX.h>

#include <cairo-win32.h>

#include "IntPoint.h"
#include "IntRect.h"
#include "IntSize.h"

#include "Color.h"
#include "ColorUtil.h"
#include "DoubleColor.h"
#include "FontStyle.h"

namespace UI{


void DrawHelper::drawLine( const IntRect& rc, int size, const Color& color )
{
	ASSERT(::GetObjectType(m_hdc) == OBJ_DC || ::GetObjectType(m_hdc) == OBJ_MEMDC);
	
	POINT tmp;
	
	HPEN hPen = ::CreatePen(PS_SOLID, size, color.rgb());
	HPEN hOldPen = (HPEN)::SelectObject(m_hdc, hPen);
	
	::MoveToEx(m_hdc, rc.x(), rc.y(), &tmp);
	::LineTo(m_hdc, rc.maxX(), rc.maxY());
	
	::SelectObject(m_hdc, hOldPen);
	::DeleteObject(hPen);
}

#if 0
void DrawHelper::drawRect( const IntRect& rc, int borderSize, const Color& color )
{
	ASSERT(::GetObjectType(m_hdc) == OBJ_DC || ::GetObjectType(m_hdc) == OBJ_MEMDC);

	HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, borderSize, RGB(color.red(), color.green(), color.blue()));
	HPEN hOldPen = (HPEN)::SelectObject(m_hdc, hPen);
	::SelectObject(m_hdc, GetStockBrush(HOLLOW_BRUSH));

	::Rectangle(m_hdc, rc.x(), rc.y(), rc.maxX(), rc.maxY());

	::SelectObject(m_hdc, hOldPen);
	::DeleteObject(hPen);
}
#endif

#define M_PI       3.14159265358979323846

void DrawHelper::drawRect( const IntRect& rc, int borderSize, const Color& color )
{
	cairo_t *cr = m_cairo;
	double x = rc.x();
	double y = rc.y();
	double width = rc.width();
	double height = rc.height();

	double aspect = 1.0;
	double corner_radius = height / 10.0;

	double radius = corner_radius / aspect;
	double degrees = M_PI / 180.0;

//  	cairo_new_sub_path (cr);
//  	cairo_arc (cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
//  	cairo_arc (cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
//  	cairo_arc (cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
//  	cairo_arc (cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
//  	cairo_close_path (cr);

	

	//cairo_set_source_rgb (cr, 1, 1, 1);
	//cairo_fill_preserve(cr);
	double r, g, b, a;
	color.getRGBA(r, g, b, a);
	cairo_set_source_rgba (cr, r, g, b, a);
	cairo_set_line_width (cr, borderSize);
	cairo_rectangle(cr, x, y, width, height);
	cairo_stroke (m_cairo);
	//

}

void DrawHelper::drawRect( const IntRect& rc, int borderSize, const Color& color, const Color& fillColor )
{
	DoubleColor colord(color);
	DoubleColor fillColord(fillColor);

	cairo_rectangle(m_cairo, rc.x(), rc.y(), rc.width(), rc.height());
	
	cairo_set_source_rgba(m_cairo, fillColord.red(), fillColord.green(), fillColord.blue(), fillColord.alpha());
	cairo_fill_preserve(m_cairo);
	
	cairo_set_source_rgba(m_cairo, colord.red(), colord.green(), colord.blue(), fillColord.alpha());
	cairo_stroke(m_cairo);
}

void DrawHelper::drawRoundRect( const IntRect& rc, int radius, int borderSize, const Color& color )
{
// 	ASSERT(::GetObjectType(m_hdc) == OBJ_DC || ::GetObjectType(m_hdc) == OBJ_MEMDC);
// 
// 	HPEN hPen = ::CreatePen(PS_SOLID | PS_INSIDEFRAME, borderSize, color.rgb());
// 	HPEN hOldPen = (HPEN)::SelectObject(m_hdc, hPen);
// 	::SelectObject(m_hdc, GetStockBrush(HOLLOW_BRUSH));
// 
// 	::RoundRect(m_hdc, rc.x(), rc.y(), rc.maxX(), rc.maxY(), width, height);
// 
// 	::SelectObject(m_hdc, hOldPen);
// 	::DeleteObject(hPen);

	double degrees = M_PI / 180.0;

	cairo_new_path(m_cairo);
	cairo_arc(m_cairo, rc.x() + radius + 0.5, rc.y() + radius + 0.5, radius, 180.0 * degrees , 270.0 * degrees);
	cairo_arc(m_cairo, rc.maxX() - radius + 0.5, rc.y() + radius + 0.5, radius, 270 * degrees, 0);
	cairo_arc(m_cairo, rc.maxX() - radius + 0.5, rc.maxY() - radius + 0.5, radius, 0, 90 * degrees);
	cairo_arc(m_cairo, rc.x() + radius + 0.5, rc.maxY() - radius + 0.5, radius, 90 * degrees, 180 * degrees);
	cairo_close_path(m_cairo);

	double r, g, b, a;
	color.getRGBA(r, g, b, a);
	cairo_set_source_rgba(m_cairo, r, g, b, a);
	cairo_set_line_width(m_cairo, borderSize);
	cairo_stroke(m_cairo);
}

void DrawHelper::drawRoundRect( const IntRect& rc, int radius, int borderSize, const Color& color, const Color& fillColor )
{
	double degrees = M_PI / 180.0;

	cairo_new_path(m_cairo);
	cairo_arc(m_cairo, rc.x() + radius + 0.5, rc.y() + radius + 0.5, radius, 180.0 * degrees , 270.0 * degrees);
	cairo_arc(m_cairo, rc.maxX() - radius + 0.5, rc.y() + radius + 0.5, radius, 270 * degrees, 0);
	cairo_arc(m_cairo, rc.maxX() - radius + 0.5, rc.maxY() - radius + 0.5, radius, 0, 90 * degrees);
	cairo_arc(m_cairo, rc.x() + radius + 0.5, rc.maxY() - radius + 0.5, radius, 90 * degrees, 180 * degrees);
	cairo_close_path(m_cairo);

	DoubleColor colord(color);
	DoubleColor fillColord(fillColor);

	cairo_set_source_rgba(m_cairo, fillColord.red(), fillColord.green(), fillColord.blue(), fillColord.alpha());
	cairo_fill_preserve(m_cairo);
	cairo_set_line_width(m_cairo, 1);
	cairo_set_source_rgba(m_cairo, colord.red(), colord.green(), colord.blue(), colord.alpha());
	cairo_stroke(m_cairo);
}

void DrawHelper::fillRect( const IntRect& rc, const Color& color )
{
// 	ASSERT(::GetObjectType(m_hdc) == OBJ_DC || ::GetObjectType(m_hdc) == OBJ_MEMDC);
// 	
// 	HBRUSH hBrush = ::CreateSolidBrush(toColorRef(color));
// 	
// 	RECT rect = rc;
// 
// 	::FillRect(m_hdc, &rect, hBrush);
// 
// 	::DeleteObject(hBrush);

	double r, g, b, a;
	color.getRGBA(r, g, b, a);
	cairo_set_source_rgba(m_cairo, r, g, b, a);
	cairo_rectangle (m_cairo, rc.x(), rc.y(), rc.width(), rc.height());
	cairo_fill(m_cairo);
}

DrawHelper::DrawHelper( HDC hdc )
{
	m_hdc = hdc;

	cairo_surface_t* surface = cairo_win32_surface_create(m_hdc);
	m_cairo = cairo_create(surface);
	cairo_surface_destroy(surface);
}

DrawHelper::DrawHelper()
{
	HDC hdc = GetDC(NULL);

	cairo_surface_t* surface = cairo_win32_surface_create(hdc);
	m_cairo = cairo_create(surface);
	cairo_surface_destroy(surface);
	
	ReleaseDC(NULL, hdc);
}

DrawHelper::~DrawHelper()
{
	cairo_destroy(m_cairo);
}

void DrawHelper::drawText( const IntRect& rc, const String& str, TextAlign align, FontStyle *font)
{
	ASSERT(font);
	if (!font)
		return;

	cairo_text_extents_t extents;
	double x, y;
	CString text = str.utf8();
	CString face = font->face().utf8();
	cairo_font_slant_t slant = font->isItalic() ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL;
	cairo_font_weight_t weight = font->isBold() ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL;

	cairo_select_font_face(m_cairo, face.data(), slant, weight);

	cairo_set_font_size(m_cairo, font->size());
	cairo_text_extents(m_cairo, text.data(), &extents);

	if (align & DT_HCenter) {
		x = (rc.width() - extents.width) / 2 + rc.x();
	} else if (align & DT_Right) {
		x = rc.width() - extents.width + rc.x();
	} else {
		x = rc.x();
	}

	if (align & DT_VCenter) {
		y = (rc.height() - extents.height) / 2 + rc.y();
	} else if (align & DT_Bottom) {
		y = (rc.height() - extents.height) + rc.y();
	} else {
		y = rc.y();
	}

	y += extents.height;

	cairo_move_to(m_cairo, x, y);
	cairo_show_text(m_cairo, text.data());
 
}

void DrawHelper::calcText( const String& str, IntSize& size, FontStyle *font)
{
	ASSERT(font);
	if (!font)
		return;

	cairo_text_extents_t extents;
	double x, y;
	CString text = str.utf8();
	CString face = font->face().utf8();
	cairo_font_slant_t slant = font->isItalic() ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL;
	cairo_font_weight_t weight = font->isBold() ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL;

	cairo_select_font_face(m_cairo, face.data(), 
		slant, weight);

	cairo_set_font_size(m_cairo, font->size());
	cairo_text_extents(m_cairo, text.data(), &extents);
	
	size.setWidth(extents.width);
	size.setHeight(extents.height);
}

}