#ifndef FractionalLayoutSize_h__
#define FractionalLayoutSize_h__

#include "FloatSize.h"
#include "FractionalLayoutUnit.h"
#include "IntSize.h"


namespace UI {

class FractionalLayoutPoint;

class FractionalLayoutSize 
{
public:
    FractionalLayoutSize() : m_width(0), m_height(0) { }
    FractionalLayoutSize(const IntSize& size) : m_width(size.width()), m_height(size.height()) { }
    FractionalLayoutSize(FractionalLayoutUnit width, FractionalLayoutUnit height) : m_width(width), m_height(height) { }

    explicit FractionalLayoutSize(const FloatSize& size): m_width(size.width()), m_height(size.height()) { }

    FractionalLayoutUnit width() const { return m_width; }
    FractionalLayoutUnit height() const { return m_height; }

    void setWidth(FractionalLayoutUnit width) { m_width = width; }
    void setHeight(FractionalLayoutUnit height) { m_height = height; }

    bool isEmpty() const { return m_width <= 0 || m_height <= 0; }
    bool isZero() const { return !m_width || !m_height; }
    
    float aspectRadio() const { return static_cast<float>(m_width) / static_cast<float>(m_height); }

    void expand(FractionalLayoutUnit width, FractionalLayoutUnit height)
    {
        m_width = width;
        m_height = height;
    }

    void scale(float scale)
    {
        m_width = static_cast<int>(static_cast<float>(m_width) * scale);
        m_height = static_cast<int>(static_cast<float>(m_height) * scale);
    }
    
    FractionalLayoutSize expandedTo(const FractionalLayoutSize& other) const
    {
        return FractionalLayoutSize(m_width > other.m_width ? m_width : other.m_width,
            m_height > other.m_height ? m_height : other.m_height);
    }

    FractionalLayoutSize shrunkTo(const FractionalLayoutSize& other) const
    {
        return FractionalLayoutSize(m_width < other.m_width ? m_width : other.m_width,
            m_height < other.m_height ? m_height : other.m_height);
    }

    void clampNegativeToZero()
    {
        *this = expandedTo(FractionalLayoutSize());
    }

    FractionalLayoutSize transposedSize() const
    {
        return FractionalLayoutSize(m_height, m_width);
    }

private:
    FractionalLayoutUnit m_width, m_height;
};


inline FractionalLayoutSize& operator+=(FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    a.setWidth(a.width() + b.width());
    a.setHeight(a.height() + b.height());
    return a;
}

inline FractionalLayoutSize& operator-=(FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    a.setWidth(a.width() - b.width());
    a.setHeight(a.height() - b.height());
    return a;
}

inline FractionalLayoutSize operator+(const FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    return FractionalLayoutSize(a.width() + b.width(), a.height() + b.height());
}

inline FractionalLayoutSize operator-(const FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    return FractionalLayoutSize(a.width() - b.width(), a.height() - b.height());
}

inline FractionalLayoutSize operator-(const FractionalLayoutSize& size)
{
    return FractionalLayoutSize(-size.width(), -size.height());
}

inline bool operator==(const FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    return a.width() == b.width() && a.height() == b.height();
}

inline bool operator!=(const FractionalLayoutSize& a, const FractionalLayoutSize& b)
{
    return a.width() != b.width() || a.height() != b.height();
}

inline IntSize flooredIntSize(const FractionalLayoutSize& s)
{
    return IntSize(s.width().toInt(), s.height().toInt());
}

inline IntSize roundedIntSize(const FractionalLayoutSize& s)
{
    return IntSize(s.width().round(), s.height().round());
}

IntSize pixelSnappedIntSize(const FractionalLayoutSize&, const FractionalLayoutPoint&);


} // namespace UI

#endif //FractionalLayoutSize_h__