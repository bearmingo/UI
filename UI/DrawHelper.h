#ifndef __GRAPHICE_H__
#define __GRAPHICE_H__

#include <wtf/Assertions.h>
#include <wtf/text/WTFString.h>

#include "GraphicsTypes.h"

//#if USER_CAIOR
typedef struct _cairo cairo_t;
//#endif

#if PLATFORM(WIN)
typedef struct HDC__ * HDC;
#endif

namespace UI {

class Color;
class IntPoint;
class IntSize;
class IntRect;


#define	DT_Left		 0x0
#define	DT_Right	 0x1
#define	DT_HCenter	 0x2
#define	DT_Top		 0x0
#define	DT_Bottom	 0x4
#define	DT_VCenter	 0x8

class FontStyle;

class DrawHelper
{
public:
	DrawHelper();
	~DrawHelper();

	void drawRect(const IntRect& rc, int borderSize, const Color& color);
	void drawRect(const IntRect& rc, int borderSize, const Color& color, const Color& fillColor);

	void drawRoundRect(const IntRect& rc, int radius, int borderSize, const Color& color);
	void drawRoundRect(const IntRect& rc, int radius, int borderSize, const Color& color, const Color& fillColor);
	void drawLine(const IntRect& rc, int size, const Color& color);

	void fillRect(const IntRect& rc, const Color& color);

	void drawText(const IntRect& rc, const String& str, TextAlign align, FontStyle *);

	void calcText(const String& str, IntSize& size, FontStyle *);

	/*DrawHelper(HDC hdc) : m_hdc(hdc) { }*/
	DrawHelper(HDC hdc);
	
private:
	HDC m_hdc;
	cairo_t *m_cairo;
};

} //namespace UI
#endif /*__GRAPHICE_H__*/

