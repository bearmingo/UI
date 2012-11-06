#ifndef ImageDrawable_h__
#define ImageDrawable_h__

#include <wtf/PassRefPtr.h>
#include <wtf/RefPtr.h>
#include "Image.h"

#include "Drawable.h"

class ImageDrawable : public Drawable {
public:
    void setImage(PassRefPtr<Image> image);
    Image* image() const { return m_image.get(); }
    
    void setSubImageRect(

    virtual void draw(GraphiceContext *context, const IntRect& rc);

protected:
    ImageDrawable();
private:
    RefPtr<Image> m_image;
    bool m_repeat;
    IntRect m_subImageRect;

};

#endif /*Imagedrawable_h__*/
