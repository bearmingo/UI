#ifndef Drawable_h__
#define Drawable_h__

#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>
#include "Image.h"


class Drawable 
{
public:
    void setImage(PassRefPtr<Image> image);
    Image* image() const { return m_image.get(); }
    virtual void draw(GraphiceContext *context, const IntRect& rc) = 0;

private:
    RefPtr<Image> m_image;
}

#endif /*Drawable_h__*/
