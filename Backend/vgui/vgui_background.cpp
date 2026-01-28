#include "vgui_background.h"

#include "../platform/win32/Image.h"
#include "../overrides/ui.h"
#include "vgui.h"
#include "vgui_window.h"

namespace vgui
{
    void VBackground::draw(HDC hdc)
    {
        if (vgui::g_Debug)
            Rectangle(hdc, 0, 0, w, h);

        img.draw(hdc, 0, 0, w, h);
    }

    void VBackground::stretch_to_fit(HWND hwnd)
    {
        RECT rc{};
        if (!GetClientRect(hwnd, &rc))
            return;

        w = rc.right - rc.left;
        h = rc.bottom - rc.top;

        InvalidateRect(hwnd, nullptr, TRUE);
    }
    /*
    LRESULT VBackground::on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        if (msg == WM_SIZE)
        {
            w = LOWORD(lp);
            h = HIWORD(lp);
            InvalidateRect(hwnd, nullptr, TRUE);
        }

        if (msg == WM_DROPFILES)
        {
            ui::drag_drop_bg_img(hwnd, img, wp, lp);
        }

        return 0;
    }*/

    bool VBackground::on_event(const Event& evt) {

        if (evt.type == EventType::LIFETIME_DTOR_EVENT) {
            std::cout << "VBackground got the dtor event";
        }

        if (evt.type == EventType::WINDOW_RESIZE_EVENT)
        {
            w = evt.window_resize_event.w;
            h = evt.window_resize_event.h;
            RECT rect = { 0, 0, w, h };
            InvalidateRect(nullptr, &rect, true);
        }
        return 0;
        
    }
    VBackground::VBackground(native::WidgetBase& widget) {
        x = widget.bounds().left;
        y = widget.bounds().top;
        w = widget.bounds().right - x;
        h = widget.bounds().bottom - y;


    }



}
