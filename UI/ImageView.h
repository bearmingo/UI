#ifndef ImageView_h__
#define ImageView_h__

#include "View.h"

class ImageView : View
{
public:
	virtual ~ImageView();
	static PassRefPtr<ImageView> create() { return adoptRef(new ImageView()); }

	void setImage(PassRefPtr<Image> image);
	Image* image() const { m_image.get(); }

	virtual void measure();
	virtual void draw(GraphicsContext *context, const IntRect&);

protected:
	ImageView() { }

private:
	RefPtr<Image> m_image;
};

#endif /*ImageView_h__*/