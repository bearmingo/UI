#ifndef __DOUBLECOLOR_H__
#define __DOUBLECOLOR_H__

#include "Color.h"
namespace UI {

class DoubleColor
{
public:
	DoubleColor(const Color& color)
	{
		color.getRGBA(m_red, m_green, m_blue, m_alpha);
	}

	double red() const { return m_red; }
	double green() const { return m_green; }
	double blue() const { return m_blue; }
	double alpha() const { return m_alpha; }

private:
	double m_red;
	double m_green;
	double m_blue;
	double m_alpha;
};

}
#endif /*__DOUBLECOLOR_H__*/

