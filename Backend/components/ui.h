#pragma once
#include <cassert>
#include "../Windows/WidgetBase.h"
#include "../Windows/Image.h"


using namespace native;
using namespace qmb;



namespace ui
{
	LRESULT drag_drop_bg_img(WidgetBase& widget, Image& target, WPARAM wParam, LPARAM lParam);
}