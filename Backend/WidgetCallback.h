#pragma once


namespace Windows
{
    class WidgetBase;


    using paint_pfn_t = LRESULT(*)(WidgetBase*, WPARAM, LPARAM);
    using event_pfn_t = LRESULT(*)(WidgetBase*, WPARAM, LPARAM);
    using mouse_pfn_t = LRESULT(*)(WidgetBase*, WPARAM, LPARAM);

    struct WidgetCallbacks {
        paint_pfn_t on_paint = nullptr;

        mouse_pfn_t on_mouse_enter = nullptr;
        mouse_pfn_t on_mouse_move = nullptr;
        mouse_pfn_t on_mouse_exit = nullptr;
        mouse_pfn_t on_mouse_down_L = nullptr;
        mouse_pfn_t on_mouse_up_L = nullptr;
        mouse_pfn_t on_mouse_down_R = nullptr;
        mouse_pfn_t on_mouse_up_R = nullptr;

        event_pfn_t on_resize = nullptr;
        event_pfn_t on_context_menu = nullptr;
        event_pfn_t on_focus = nullptr;
        event_pfn_t on_unfocus = nullptr;
        event_pfn_t on_key_down = nullptr;
        event_pfn_t on_key_up = nullptr;
        event_pfn_t on_char = nullptr;
        event_pfn_t on_construct = nullptr;
        event_pfn_t on_destruct = nullptr;
        event_pfn_t on_file_drop = nullptr;
    };
}