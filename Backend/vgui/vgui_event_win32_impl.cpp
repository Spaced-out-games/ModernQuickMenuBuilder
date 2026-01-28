#include "vgui_event_win32_impl.h"


namespace vgui
{


    KeyFlag vgui_keyflag_win32_impl(LPARAM lp)
    {
        KeyFlag flags = KEYFLAG_NONE;

        // Bit 24 = Extended key (right-hand Ctrl/Alt, arrow keys, etc.)
        if ((lp >> 24) & 1)
            flags = static_cast<KeyFlag>(flags | KEYFLAG_EXTENDED);

        // Bit 30 = Previous key state (1 = was down)
        if ((lp >> 30) & 1)
            flags = static_cast<KeyFlag>(flags | KEYFLAG_WAS_DOWN);

        // Bit 31 = Transition state (1 = key being released, only on WM_KEYUP)
        if ((lp >> 31) & 1)
            flags = static_cast<KeyFlag>(flags | KEYFLAG_RELEASED);

        return flags;
    }

    void vgui_handle_mouse_events(Event& evt, UINT msg, LPARAM lp, WPARAM wp) {

        evt.mouse_event.button = 0;

        if (msg == WM_MOUSEWHEEL || msg == WM_MOUSEHWHEEL) {
            evt.type = EventType::MOUSEWHEEL_EVENT;
            evt.mousewheel_event.direction = GET_WHEEL_DELTA_WPARAM(wp);
            evt.mousewheel_event.x = GET_X_LPARAM(lp);
            evt.mousewheel_event.y = GET_Y_LPARAM(lp);
            return;

        }
        else {
            evt.mouse_event.x = GET_X_LPARAM(lp);
            evt.mouse_event.y = GET_Y_LPARAM(lp);
        }

        // mouse movement handled separately. Use what the else case provided and return
        if (msg == WM_MOUSEMOVE) {
            evt.type = EventType::MOUSE_MOVE_EVENT;
            return;
        }


        // extract type
        switch (msg) {
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
            evt.type = EventType::MOUSE_RELEASE_EVENT;
            break;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
            evt.type = EventType::MOUSE_CLICK_EVENT;
            break;

        default:
            evt.type = EventType::LIFETIME_NULL_EVENT;
            return;
            break;
        }

        switch (msg) {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            evt.mouse_event.button = 0;
            break;

        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            evt.mouse_event.button = 1;
            break;

        case WM_MBUTTONUP:
        case WM_MBUTTONDOWN:
            evt.mouse_event.button = 2;
            break;

        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
            evt.mouse_event.button = (int)HIWORD(wp);
            break;


        default:
            evt.type = EventType::LIFETIME_NULL_EVENT;

        }

        return; // for now


    }


    // keymap
    Keycode vgui_keycode_win32_impl(WPARAM wp, LPARAM lp) {
        using namespace vgui;

        bool extended = (lp >> 24) & 1;

        switch (wp) {
            // Letters
        case 'A': return KEY_A;
        case 'B': return KEY_B;
        case 'C': return KEY_C;
        case 'D': return KEY_D;
        case 'E': return KEY_E;
        case 'F': return KEY_F;
        case 'G': return KEY_G;
        case 'H': return KEY_H;
        case 'I': return KEY_I;
        case 'J': return KEY_J;
        case 'K': return KEY_K;
        case 'L': return KEY_L;
        case 'M': return KEY_M;
        case 'N': return KEY_N;
        case 'O': return KEY_O;
        case 'P': return KEY_P;
        case 'Q': return KEY_Q;
        case 'R': return KEY_R;
        case 'S': return KEY_S;
        case 'T': return KEY_T;
        case 'U': return KEY_U;
        case 'V': return KEY_V;
        case 'W': return KEY_W;
        case 'X': return KEY_X;
        case 'Y': return KEY_Y;
        case 'Z': return KEY_Z;

            // Numbers (top row)
        case '0': return KEY_0;
        case '1': return KEY_1;
        case '2': return KEY_2;
        case '3': return KEY_3;
        case '4': return KEY_4;
        case '5': return KEY_5;
        case '6': return KEY_6;
        case '7': return KEY_7;
        case '8': return KEY_8;
        case '9': return KEY_9;

            // Function keys
        case VK_F1:  return KEY_F1;
        case VK_F2:  return KEY_F2;
        case VK_F3:  return KEY_F3;
        case VK_F4:  return KEY_F4;
        case VK_F5:  return KEY_F5;
        case VK_F6:  return KEY_F6;
        case VK_F7:  return KEY_F7;
        case VK_F8:  return KEY_F8;
        case VK_F9:  return KEY_F9;
        case VK_F10: return KEY_F10;
        case VK_F11: return KEY_F11;
        case VK_F12: return KEY_F12;

            // Arrows
        case VK_LEFT:  return KEY_LEFT;
        case VK_RIGHT: return KEY_RIGHT;
        case VK_UP:    return KEY_UP;
        case VK_DOWN:  return KEY_DOWN;

            // Common controls
        case VK_SPACE:      return KEY_SPACE;
        case VK_ESCAPE:     return KEY_ESCAPE;
        case VK_TAB:        return KEY_TAB;
        case VK_BACK:       return KEY_BACKSPACE;
        case VK_SHIFT:      return KEY_SHIFT;
        case VK_CONTROL:    return KEY_CTRL;
        case VK_MENU:       return KEY_ALT;
        case VK_CAPITAL:    return KEY_CAPSLOCK;
        case VK_PAUSE:      return KEY_PAUSE;
        case VK_SNAPSHOT:   return KEY_PRINTSCREEN;
        case VK_INSERT:     return KEY_INSERT;
        case VK_DELETE:     return KEY_DELETE;
        case VK_HOME:       return KEY_HOME;
        case VK_END:        return KEY_END;
        case VK_PRIOR:      return KEY_PAGEUP;
        case VK_NEXT:       return KEY_PAGEDOWN;
        case VK_APPS:       return KEY_MENU;

            // Numpad
        case VK_NUMPAD0: return KEY_NUM0;
        case VK_NUMPAD1: return KEY_NUM1;
        case VK_NUMPAD2: return KEY_NUM2;
        case VK_NUMPAD3: return KEY_NUM3;
        case VK_NUMPAD4: return KEY_NUM4;
        case VK_NUMPAD5: return KEY_NUM5;
        case VK_NUMPAD6: return KEY_NUM6;
        case VK_NUMPAD7: return KEY_NUM7;
        case VK_NUMPAD8: return KEY_NUM8;
        case VK_NUMPAD9: return KEY_NUM9;
        case VK_NUMLOCK: return KEY_NUMLOCK;
        case VK_DIVIDE:  return KEY_NUM_DIVIDE;
        case VK_MULTIPLY:return KEY_NUM_MULTIPLY;
        case VK_SUBTRACT:return KEY_NUM_SUBTRACT;
        case VK_ADD:     return KEY_NUM_ADD;
        case VK_DECIMAL: return KEY_NUM_DECIMAL;
        case VK_RETURN:
            if (extended) return KEY_ENTER;
            return KEY_NUM_ENTER;
            break;

        default:
            return KEY_UNKNOWN;
        }
    }

    /*
    
    
                case WM_ERASEBKGND:
                return 1;
            case WM_NCHITTEST:
            case WM_ENTERSIZEMOVE:
            case WM_EXITSIZEMOVE:
            case WM_SIZING:
            case WM_WINDOWPOSCHANGING:
            case WM_SIZE:
    
    */



    // can't be converted from anything but a native win32 event!
    bool vgui_event_win32_impl(native::Application* app, vgui::Event& evt, UINT msg, WPARAM wp, LPARAM lp) {

        if (!app) {
            __debugbreak();
            std::cout << "Invalid Application*!";
            throw std::runtime_error("Invalid Application*!");
        }
        if (!app->m_Window) {
            __debugbreak();
            std::cout << "Invalid Window*!";
            throw std::runtime_error("Invalid Window*!");
        }

        // these are provided every time. Consider window* in app!
        evt.app = app;


        // handle mice events (declutters this function)
        if ((msg >= WM_MOUSEMOVE && msg <= WM_MOUSEHWHEEL) || msg == WM_XBUTTONDBLCLK) {
            vgui_handle_mouse_events(evt, msg, lp, wp);
            return 0;
        }
        //TODO: add event bodies & population logic
        switch (msg)
        {
        case WM_WINDOWPOSCHANGING:
            evt.type = EventType::WINDOW_STATE_CHANGING_EVENT;
            break;
        case WM_ENTERSIZEMOVE:
            evt.type = EventType::WINDOW_BEGIN_MOVE_RESIZE_EVENT;
            break;
        case WM_EXITSIZEMOVE:
            evt.type = EventType::WINDOW_END_MOVE_RESIZE_EVENT;
            break;
        case WM_ERASEBKGND:
            evt.type = EventType::WINDOW_ERASE_BG_EVENT;
            break;
        case WM_CREATE:
            evt.type = EventType::LIFETIME_CTOR_EVENT;
            break;

        case WM_QUIT:
            evt.type = EventType::LIFETIME_DTOR_EVENT;
            break;

        case WM_CLOSE:
            evt.type = EventType::LIFETIME_EXIT_QUERY_EVENT;
            break;

            // we skip tick events here since that's custom

            // and we skip clipboard stuff for now, since I'm lazy.
        case WM_KEYUP:
            evt.type = EventType::KEYBOARD_RELEASE_EVENT;
            evt.keyboard_event.keycode = vgui_keycode_win32_impl(wp, lp);
            evt.keyboard_event.flags = vgui_keyflag_win32_impl(lp);
            break;

        case WM_KEYDOWN:
            evt.type = EventType::KEYBOARD_PRESS_EVENT;
            evt.keyboard_event.keycode = vgui_keycode_win32_impl(wp, lp);
            evt.keyboard_event.flags = vgui_keyflag_win32_impl(lp);
            break;

        case WM_MOUSEHOVER:
            evt.type = EventType::MOUSE_HOVER_EVENT;
            break;
        case WM_MOUSELEAVE:
            evt.type = EventType::MOUSE_LEAVE_EVENT;
            break;
        case WM_SIZE:
            evt.type = EventType::WINDOW_RESIZE_EVENT;
            evt.window_resize_event.w = LOWORD(lp);
            evt.window_resize_event.h = HIWORD(lp);
            break;
        case WM_SIZING:
            evt.type = EventType::WINDOW_RESIZING_EVENT;
            break;
        case WM_MOVE:
            evt.type = EventType::WINDOW_MOVE_EVENT;
            evt.window_move_event.x = LOWORD(lp);
            evt.window_move_event.y = HIWORD(lp);
            break;
        case WM_MOVING:
            evt.type = EventType::WINDOW_MOVING_EVENT;
            evt.window_move_event.x = LOWORD(lp);
            evt.window_move_event.y = HIWORD(lp);
            break;
        case WM_PAINT:
            evt.type = EventType::WINDOW_PAINT_EVENT;
            evt.window_paint_event.draw_instructions = (void*) new PAINTSTRUCT();
            evt.window_paint_event.device = BeginPaint(app->m_Window->handle(), (PAINTSTRUCT*)evt.window_paint_event.draw_instructions);
            break;
            break;
        case WM_SETFOCUS:
            evt.type = EventType::WINDOW_GAINFOCUS_EVENT;
            break;
        case WM_KILLFOCUS:
            evt.type = EventType::WINDOW_LOSEFOCUS_EVENT;
            break;


        default:
            break;
        }
        return 0;
    }

    bool vgui_event_win32_impl(native::Application* app, vgui::Event& evt, const MSG& msg) {
        return vgui_event_win32_impl(app, evt, msg.message, msg.wParam, msg.wParam);
    }

    void Event_dtor_impl(Event& evt)
    {
        if (!evt.app) {
            std::cout << "Invalid Application*!";
            throw std::runtime_error("Invalid Application*!");
        }

        if (!evt.app->m_Window) {
            std::cout << "Invalid Window*!";
            throw std::runtime_error("Invalid Window*!");
        }

        if (evt.type == EventType::WINDOW_PAINT_EVENT && evt.window_paint_event.draw_instructions != nullptr) {
            PAINTSTRUCT* ps = (PAINTSTRUCT*)evt.window_paint_event.draw_instructions;
            evt.window_paint_event.draw_instructions = nullptr;
            EndPaint(evt.app->m_Window->handle(), ps);
            delete ps;
        }
    }
    bool PollEvent(native::Application* app, vgui::Event& evt, bool dispatch_native)
    {
        MSG msg;
        if (!PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) return false;

        if (dispatch_native)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }


        vgui_event_win32_impl(app, evt, msg);
        return true;
    }





}