#pragma once
#include <Windows.h>

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


    class IWidgetCallbacks
    {
        WidgetCallbacks m_Callbacks = {};
        //public:

        // Gets the event hook
        event_pfn_t on_file_drop();

        // Gets the event hook
        paint_pfn_t on_paint();

        // Gets the event hook
        mouse_pfn_t on_mouse_enter();

        // Gets the event hook
        mouse_pfn_t on_mouse_exit();

        // Gets the event hook
        mouse_pfn_t on_mouse_move();

        // Gets the event hook
        mouse_pfn_t on_mouse_down_L();

        // Gets the event hook
        mouse_pfn_t on_mouse_up_L();

        // Gets the event hook
        mouse_pfn_t on_mouse_down_R();

        // Gets the event hook
        mouse_pfn_t on_mouse_up_R();


        // Gets the event hook
        event_pfn_t on_resize();

        // Gets the event hook
        event_pfn_t on_context_menu();

        // Gets the event hook
        event_pfn_t on_focus();

        // Gets the event hook
        event_pfn_t on_unfocus();

        // Gets the event hook
        event_pfn_t on_key_down();

        // Gets the event hook
        event_pfn_t on_key_up();

        // Gets the event hook
        event_pfn_t on_char();

        // Gets the event hook
        event_pfn_t on_construct();

        // Gets the event hook
        event_pfn_t on_destruct();

        // Begins painting
        void begin_paint(HWND handle, PAINTSTRUCT&, HDC&);

        // Stops painting
        void        end_paint(HWND handle, PAINTSTRUCT&);




        ///                                                 ///
        ///                     setters                     ///
        ///                                                 ///

        // Sets the event hook
        void on_paint(paint_pfn_t);

        // Sets the event hook
        void on_mouse_enter(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_exit(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_move(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_down_L(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_up_L(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_down_R(mouse_pfn_t);

        // Sets the event hook
        void on_mouse_up_R(mouse_pfn_t);

        // Sets the event hook
        void on_file_drop(event_pfn_t);

        // Sets the event hook
        void on_resize(event_pfn_t);

        // Sets the event hook
        void on_context_menu(event_pfn_t);

        // Sets the event hook
        void on_focus(event_pfn_t);

        // Sets the event hook
        void on_unfocus(event_pfn_t);

        // Sets the event hook
        void on_key_down(event_pfn_t);

        // Sets the event hook
        void on_key_up(event_pfn_t);

        // Sets the event hook
        void on_char(event_pfn_t);

        // Sets the event hook
        void on_construct(event_pfn_t);

        // Sets the event hook
        void on_destruct(event_pfn_t);
    };
}