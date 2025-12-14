#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace vgui
{
    class Context;
    struct Widget;

    class Page
    {
        friend class Context;

        std::unordered_map<std::string, std::unique_ptr<Widget>> m_Widgets;

    public:
        bool add(const std::string& name, std::unique_ptr<Widget>&& widget);
        bool remove(const std::string& name);

        Widget* get(const std::string& name);
        const Widget* get(const std::string& name) const;

        bool has(const std::string& name) const;
    };

    using Book = std::unordered_map<std::string, std::unique_ptr<Page>>;

    // Optional future BSP support
    struct BSPNode
    {
        std::unique_ptr<Widget> widget;
        float weight = 0.0f;
        alignas(4) bool axis = false;
    };
}
