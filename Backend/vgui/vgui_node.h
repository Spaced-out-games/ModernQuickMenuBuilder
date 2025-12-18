#pragma once
#include "vgui_widget.h"
#include <memory>
#include <cstdint>
#include <limits>
#include <vector>

namespace vgui
{
    struct WidgetNode
    {
        using index_t = uint32_t;
        static constexpr index_t NULLWIDGET = -1;

        std::unique_ptr<vgui::Widget> m_Widget;
        index_t m_Prev = NULLWIDGET;
        index_t m_Next = NULLWIDGET;
        string_hash_t m_NameHash = 0;
        vgui::Widget* get() noexcept
        {
            return m_Widget.get();
        }
        WidgetNode() = default;
        WidgetNode(const std::string& name, index_t prev, index_t next, std::unique_ptr<vgui::Widget>&& widget): m_Prev(prev), m_Next(next), m_Widget(std::move(widget)), m_NameHash(hash(name)) {}
    };
}
