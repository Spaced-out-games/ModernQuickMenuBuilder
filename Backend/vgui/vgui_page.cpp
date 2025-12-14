#include "vgui_page.h"
#include "vgui_widget.h"

namespace vgui
{
    bool Page::add(const std::string& name, std::unique_ptr<Widget>&& widget)
    {
        if (m_Widgets.contains(name))
            return false;

        m_Widgets.emplace(name, std::move(widget));
        return true;
    }

    bool Page::remove(const std::string& name)
    {
        return m_Widgets.erase(name) > 0;
    }

    Widget* Page::get(const std::string& name)
    {
        auto it = m_Widgets.find(name);
        return it != m_Widgets.end() ? it->second.get() : nullptr;
    }

    const Widget* Page::get(const std::string& name) const
    {
        auto it = m_Widgets.find(name);
        return it != m_Widgets.end() ? it->second.get() : nullptr;
    }

    bool Page::has(const std::string& name) const
    {
        return m_Widgets.contains(name);
    }
}
