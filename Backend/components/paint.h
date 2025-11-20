#pragma once
#include <cassert>
#include "../WidgetBase.h"
#include "../Image.h"

using namespace Windows;

namespace paint
{

	LRESULT draw_image(HDC hdc, Image& img, int x, int y, int w, int h);

	LRESULT render_background_image(WidgetBase& widget, HDC hdc, Image& img);


}