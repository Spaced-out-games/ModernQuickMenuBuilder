#include "paint.h"
#ifdef  _DEBUG
	#include <format>
#endif

namespace paint
{

	LRESULT draw_image(HDC hdc, Image& img, int x, int y, int w, int h)
	{
		// instead of a null check, we just assert, since hdc is a pointer under the hood, so we can't really assume an HDC& is valid
		assert(hdc != nullptr);
		img.draw(hdc, x, y, w, h);
		return 0;
	}

	LRESULT render_background_image(WidgetBase& widget, HDC hdc, Image& img)
	{
		// instead of a null check, we just assert, since hdc is a pointer under the hood, and we can't really assume an HDC& is valid
		assert(hdc != nullptr);
		RECT rc = widget.bounds();
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		draw_image(hdc, img, 0, 0, width, height);
		return 0;
	}


	
}