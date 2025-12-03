#include "WidgetCallback.h"


namespace native
{
    event_pfn_t IWidgetCallbacks::on_file_drop() { return m_Callbacks.on_file_drop; }
    paint_pfn_t IWidgetCallbacks::on_paint() { return m_Callbacks.on_paint; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_enter() { return m_Callbacks.on_mouse_enter; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_exit() { return m_Callbacks.on_mouse_exit; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_move() { return m_Callbacks.on_mouse_move; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_down_L() { return m_Callbacks.on_mouse_down_L; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_up_L() { return m_Callbacks.on_mouse_up_L; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_down_R() { return m_Callbacks.on_mouse_down_R; }
    mouse_pfn_t IWidgetCallbacks::on_mouse_up_R() { return m_Callbacks.on_mouse_up_R; }

    event_pfn_t IWidgetCallbacks::on_resize() { return m_Callbacks.on_resize; }
    event_pfn_t IWidgetCallbacks::on_context_menu() { return m_Callbacks.on_context_menu; }
    event_pfn_t IWidgetCallbacks::on_focus() { return m_Callbacks.on_focus; }
    event_pfn_t IWidgetCallbacks::on_unfocus() { return m_Callbacks.on_unfocus; }
    event_pfn_t IWidgetCallbacks::on_key_down() { return m_Callbacks.on_key_down; }
    event_pfn_t IWidgetCallbacks::on_key_up() { return m_Callbacks.on_key_up; }
    event_pfn_t IWidgetCallbacks::on_char() { return m_Callbacks.on_char; }
    event_pfn_t IWidgetCallbacks::on_construct() { return m_Callbacks.on_construct; }
    event_pfn_t IWidgetCallbacks::on_destruct() { return m_Callbacks.on_destruct; }
    void IWidgetCallbacks::begin_paint_impl(HWND handle, PAINTSTRUCT& ps, HDC& hdc) { hdc = BeginPaint(handle, &ps); }
    void IWidgetCallbacks::end_paint_impl(HWND handle, PAINTSTRUCT& ps) { EndPaint(handle, &ps); }



    ///                                                 ///
    ///                     setters                     ///
    ///                                                 ///
    void IWidgetCallbacks::on_file_drop(event_pfn_t callback) { m_Callbacks.on_file_drop = callback; }
    void IWidgetCallbacks::on_paint(paint_pfn_t callback) { m_Callbacks.on_paint = callback; }
    void IWidgetCallbacks::on_mouse_enter(mouse_pfn_t callback) { m_Callbacks.on_mouse_enter = callback; }
    void IWidgetCallbacks::on_mouse_exit(mouse_pfn_t callback) { m_Callbacks.on_mouse_exit = callback; }
    void IWidgetCallbacks::on_mouse_move(mouse_pfn_t callback) { m_Callbacks.on_mouse_move = callback; }
    void IWidgetCallbacks::on_mouse_down_L(mouse_pfn_t callback) { m_Callbacks.on_mouse_down_L = callback; }
    void IWidgetCallbacks::on_mouse_up_L(mouse_pfn_t callback) { m_Callbacks.on_mouse_up_L = callback; }
    void IWidgetCallbacks::on_mouse_down_R(mouse_pfn_t callback) { m_Callbacks.on_mouse_down_R = callback; }
    void IWidgetCallbacks::on_mouse_up_R(mouse_pfn_t callback) { m_Callbacks.on_mouse_up_R = callback; }



    void IWidgetCallbacks::on_resize(event_pfn_t callback) { m_Callbacks.on_resize = callback; }
    void IWidgetCallbacks::on_context_menu(event_pfn_t callback) { m_Callbacks.on_context_menu = callback; }
    void IWidgetCallbacks::on_focus(event_pfn_t callback) { m_Callbacks.on_focus = callback; }
    void IWidgetCallbacks::on_unfocus(event_pfn_t callback) { m_Callbacks.on_unfocus = callback; }
    void IWidgetCallbacks::on_key_down(event_pfn_t callback) { m_Callbacks.on_key_down = callback; }
    void IWidgetCallbacks::on_key_up(event_pfn_t callback) { m_Callbacks.on_key_up = callback; }
    void IWidgetCallbacks::on_char(event_pfn_t callback) { m_Callbacks.on_char = callback; }
    void IWidgetCallbacks::on_construct(event_pfn_t callback) { m_Callbacks.on_construct = callback; }
    void IWidgetCallbacks::on_destruct(event_pfn_t callback) { m_Callbacks.on_destruct = callback; }
}