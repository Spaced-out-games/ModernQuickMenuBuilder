#pragma once
#include <cassert>
#include "../native/WidgetBase.h"
#include "../native/Image.h"


using namespace native;
using namespace qmb;



namespace ui
{
	LRESULT drag_drop_bg_img(WidgetBase& widget, Image& target, WPARAM wParam, LPARAM lParam);
}