#include "../native/Image.h"
#include "vgui_context.h"
#include "vgui_page.h"
#include "vgui_widget.h"
#include "vgui_background.h"
#include "vgui_window.h"
#include "vgui_error.h"

#include <format>

namespace vgui
{
    void Context::draw(HDC hdc)
    {
        if (!GetActivePage())
            return;

        if (m_Background)
            m_Background->draw(hdc);

        for (auto& [id, vWidget] : GetActivePage()->m_Widgets)
        {
            vWidget->draw(hdc);
        }
    }

    bool Context::LoadBackground(const std::string& /*pagename*/, const std::string& path)
    {
        if (!m_Background)
        {
            m_Background = std::make_unique<VBackground>();
        }

        m_Background->img = qmb::Image::load_image(path);
        m_Background->stretch_to_fit(m_Window->handle());
        m_Window->invalidate();

        return true;
    }

    void Context::SetBook(std::unique_ptr<Book>&& book)
    {
        m_ActiveBook = std::move(book);
    }

    Book* Context::GetBook()
    {
        return m_ActiveBook.get();
    }

    void Context::LoadPage(const std::string& id)
    {
        using enum vgui::Error;

        if (!m_ActiveBook || m_ActiveBook->find(id) == m_ActiveBook->end())
        {
            exit(std::format("[ERROR] Could not find page with name '{}'!", id),
                PAGE_NOT_FOUND_ERROR);
            return;
        }

        m_ActivePageID = id;

        Page* page = GetActivePage();
        if (!page)
            return;

        // attach context to widgets
        for (auto& [name, widget] : page->m_Widgets)
        {
            if (widget)
                widget->m_Owner = this;
        }
    }

    Page* Context::GetPage(const std::string& id)
    {
        if (!m_ActiveBook)
            return nullptr;

        auto it = m_ActiveBook->find(id);
        return it != m_ActiveBook->end() ? it->second.get() : nullptr;
    }

    Page* Context::GetActivePage()
    {
        return GetPage(m_ActivePageID);
    }

    LRESULT Context::on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        if (!m_ActiveBook || !GetActivePage())
            return 0;

        for (auto& [id, vWidget] : GetActivePage()->m_Widgets)
        {
            vWidget->on_event(hwnd, msg, wp, lp);
        }

        if (m_Background)
            m_Background->on_event(hwnd, msg, wp, lp);

        return 0;
    }
}
