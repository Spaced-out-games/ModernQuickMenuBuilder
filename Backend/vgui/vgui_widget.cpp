#include "vgui_widget.h"
#include "vgui.h"
#include "vgui_error.h"
#include <format>
#include "thirdparty/json/json.hpp"


using json = nlohmann::json;

namespace vgui
{
    Widget::Widget() = default;

    Widget::Widget(int x_, int y_, int w_, int h_)
        : x(x_), y(y_), w(w_), h(h_) {}

    Widget::Widget(json bounds)
    {
        using enum vgui::Error;

        if (!bounds.is_array())
        {
            vgui::exit(std::format("Bounds are not an array!"), JSON_PARSE_ERROR);
        }

        if (bounds.size() != 4)
        {
            vgui::exit(
                std::format("Bounds must contain exactly 4 elements (x, y, w, h)!"),
                JSON_PARSE_ERROR
            );
        }

        x = bounds[0].get<int>();
        y = bounds[1].get<int>();
        w = bounds[2].get<int>();
        h = bounds[3].get<int>();
    }

    void Widget::draw(HDC hdc)
    {
        if (!vgui::g_Debug)
            return;

        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
        HPEN oldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));

        Rectangle(hdc, x, y, x + w, y + h);

        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
    }

    LRESULT Widget::on_event(HWND hwnd, UINT msg, WPARAM, LPARAM)
    {
        if (msg == WM_SIZE)
        {
            InvalidateRect(hwnd, nullptr, TRUE);
        }
        return 0;
    }

    bool Widget::overlaps(int px, int py) const
    {
        return px >= x && px <= x + w &&
            py >= y && py <= y + h;
    }

    Widget::~Widget() = default;
}
