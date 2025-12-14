#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace vgui
{
    class VWindow;
    class VBackground;
    class Page;
    struct Widget;

    using Book = std::unordered_map<std::string, std::unique_ptr<Page>>;

    struct Context
    {
    private:
        std::unique_ptr<Book> m_ActiveBook = nullptr;
        std::string m_ActivePageID = ""; // "" denotes null
        std::unique_ptr<VBackground> m_Background = nullptr;

    public:
        VWindow* m_Window = nullptr;

        // rendering
        void draw(HDC hdc);

        // background
        bool LoadBackground(const std::string& pagename, const std::string& path);

        // book / pages
        void SetBook(std::unique_ptr<Book>&& book);
        Book* GetBook();

        void LoadPage(const std::string& id);
        Page* GetPage(const std::string& id);
        Page* GetActivePage();

        // events
        LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    };
}
