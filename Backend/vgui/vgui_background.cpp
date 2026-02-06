#include "vgui_background.h"

#include "../platform/win32/Image.h"
#include "vgui.h"
#include "vgui_window.h"
#include "../woodchuck/woodchuck.h"

namespace vgui
{
    void VBackground::draw(HDC hdc)
    {
        if (vgui::g_Debug)
            Rectangle(hdc, 0, 0, w, h);

        img.draw(hdc, 0, 0, w, h);
    }



    bool VBackground::on_event(const Event& evt) {

        if (evt.type == EventType::LIFETIME_DTOR_EVENT) {

            woodchuck::info("VBackground got the dtor event");
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
    VBackground::VBackground(native::WidgetBase& owner, const std::string& img_path) 
    {
        qmb::load_image(img, img_path);

        x = owner.bounds().left;
        y = owner.bounds().top;
        w = owner.bounds().right - x;
        h = owner.bounds().bottom - y;

    }



}
