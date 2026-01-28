#pragma once
#include <cassert>
#include "../platform/win32/WidgetBase.h"
#include "../platform/win32/Image.h"


using namespace native;
using namespace qmb;


namespace paint
{

	LRESULT draw_image(HDC hdc, Image& img, int x, int y, int w, int h);

	LRESULT render_background_image(WidgetBase& widget, HDC hdc, Image& img);


}