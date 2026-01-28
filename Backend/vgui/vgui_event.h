#pragma once
#include "../platform/win32/Application.h"
#include "../platform/win32/Window.h"

namespace vgui
{

    struct Event;

    // defined in vgui_event_*_impl.cpp
    void Event_dtor_impl(Event& evt);

    // note: there is no analogue for 'WM_NCHITTEST'
    enum class EventType : uint32_t {
        LIFETIME_NULL_EVENT,
        LIFETIME_CTOR_EVENT,
        LIFETIME_DTOR_EVENT,
        LIFETIME_TICK_EVENT,
        LIFETIME_EXIT_QUERY_EVENT,
        CLIPBOARD_UPDATE_EVENT,
        KEYBOARD_PRESS_EVENT,
        KEYBOARD_RELEASE_EVENT,
        KEYBOARD_HOLD_EVENT,

        MOUSE_MOVE_EVENT,
        MOUSE_CLICK_EVENT,
        MOUSE_HOLD_EVENT,
        MOUSE_RELEASE_EVENT,
        
        
        MOUSE_HOVER_EVENT,
        MOUSE_LEAVE_EVENT,

        MOUSEWHEEL_EVENT,

        WINDOW_RESIZE_EVENT, // WM_SIZE
        WINDOW_RESIZING_EVENT, // WM_SIZING
        WINDOW_BEGIN_MOVE_RESIZE_EVENT, // WM_ENTERSIZEMOVE
        WINDOW_END_MOVE_RESIZE_EVENT, // WM_EXITSIZEMOVE
        WINDOW_MOVE_EVENT,
        WINDOW_MOVING_EVENT,
        WINDOW_PAINT_EVENT,
        WINDOW_GAINFOCUS_EVENT,
        WINDOW_LOSEFOCUS_EVENT,
        WINDOW_ERASE_BG_EVENT, // WM_ERASEBKGND
        WINDOW_STATE_CHANGING_EVENT, // WM_WINDOWPOSCHANGING


        FILE_UPDATE_EVENT,
        FILE_REMOVE_EVENT,
        FILE_CREATE_EVENT,

        WIDGET_CREATE_EVENT,
        WIDGET_DESTROY_EVENT,

        LAYER_CREATE_EVENT,
        LAYER_DESTROY_EVENT,
        

    };

    enum Keycode : unsigned int {
        KEY_UNKNOWN = 0,

        // Letters
        KEY_A = 1,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,

        // Numbers (top row)
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,

        // Function keys
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,

        // Arrow keys
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,

        // Common controls
        KEY_SPACE,
        KEY_ENTER,
        KEY_ESCAPE,
        KEY_TAB,
        KEY_BACKSPACE,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_ALT,
        KEY_CAPSLOCK,

        // Numpad
        KEY_NUM0,
        KEY_NUM1,
        KEY_NUM2,
        KEY_NUM3,
        KEY_NUM4,
        KEY_NUM5,
        KEY_NUM6,
        KEY_NUM7,
        KEY_NUM8,
        KEY_NUM9,
        KEY_NUMLOCK,
        KEY_NUM_ENTER,
        KEY_NUM_DIVIDE,
        KEY_NUM_MULTIPLY,
        KEY_NUM_SUBTRACT,
        KEY_NUM_ADD,
        KEY_NUM_DECIMAL,

        // Other common keys
        KEY_INSERT,
        KEY_DELETE,
        KEY_HOME,
        KEY_END,
        KEY_PAGEUP,
        KEY_PAGEDOWN,
        KEY_PRINTSCREEN,
        KEY_PAUSE,
        KEY_MENU,  // Alt/Menu key
    };

    enum KeyFlag : unsigned int {
        KEYFLAG_NONE = 0,
        KEYFLAG_EXTENDED = 1 << 0,
        KEYFLAG_WAS_DOWN = 1 << 1,
        KEYFLAG_RELEASED = 1 << 2,
    };


    struct Event {
        native::Application* app = nullptr;
        EventType type = EventType::LIFETIME_NULL_EVENT;
        uint32_t timestamp = 0;
        union
        {
            // for testing
            struct { HWND hwnd; UINT msg; WPARAM wp; LPARAM lp; } win32_event;

            struct { float deltaTime; } tick_event;

            // Clipboard
            struct { const char* text; } clipboard_update_event;

            // Keyboard
            struct { Keycode keycode; KeyFlag flags; } keyboard_event;

            // Mouse
            struct { int x; int y; int button; } mouse_event;
            struct { int x; int y; int direction; } mousewheel_event;

            // Window
            struct { int w; int h; } window_resize_event;
            struct { int x; int y; } window_move_event;
            struct { void* device; void* draw_instructions;  } window_paint_event;

            // File system
            struct { const char* path; } file_create_event;
            struct { const char* path; } file_remove_event;
            struct { const char* path; } file_update_event;

            // Widgets
            struct { void* widget; } widget_create_event;
            struct { void* widget; } widget_destroy_event;

            // Layers
            struct { void* layer; } layer_create_event;
            struct { void* layer; } layer_destroy_event;
        };
        // platform-specified destructor
        void free() {
            Event_dtor_impl(*this);
        }
        Event() = default;
        Event(const Event& other) = delete;
        ~Event() { free(); }


    };

    


    void makeTickEvent(Event& evt);

} // namespace vgui
