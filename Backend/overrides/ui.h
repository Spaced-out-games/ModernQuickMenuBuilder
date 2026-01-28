#pragma once
#include <cassert>
#include "../platform/win32/WidgetBase.h"
#include "../platform/win32/Image.h"


using namespace native;
using namespace qmb;



namespace ui
{
	LRESULT drag_drop_bg_img(HWND hwnd, Image& target, WPARAM wParam, LPARAM lParam);
}