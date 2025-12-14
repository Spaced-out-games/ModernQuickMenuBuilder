#pragma once
#include <Windows.h>
#include "vgui_widget.h"
#include <vector>
#include <format>
#include <cassert>
#include "vgui_page.h"
#include "vgui_background.h"
#include "vgui_error.h"

namespace vgui
{


    struct Context {

        private:
            std::unique_ptr<Book> m_ActiveBook = nullptr;
            std::string m_ActivePageID = ""; // "" denotes null
            // needs to be drawn first.
            std::unique_ptr<vgui::VBackground> m_Background = nullptr;
            //Page* m_ActivePage = nullptr;

        public:
            vgui::VWindow* m_Window = nullptr;

        
            void draw(HDC hdc) {

                if (!GetActivePage()) return;

                if (m_Background) m_Background->draw(hdc);

                for (auto& [id, vWidget]: GetActivePage()->m_Widgets)
                {
                    vWidget.get()->draw(hdc); // OK, vWidget is a reference to unique_ptr
                }
            }

            bool LoadBackground(const std::string& pagename, const std::string& path) {

                if (!m_Background)
                {
                    m_Background = std::make_unique<vgui::VBackground>();
                }


                m_Background->img = Image::load_image(path);
                m_Background->stretch_to_fit(m_Window->handle());
                m_Window->invalidate();
                return true;
            }




            void SetBook(std::unique_ptr<Book>&& book)
            {
                m_ActiveBook = std::move(book);

                
            }

            Book* GetBook()
            {
                return m_ActiveBook.get();
            }

            



            void LoadPage(const std::string& id)
            {

                using enum vgui::Error;

                if(m_ActiveBook->find(id) == m_ActiveBook->end()) {
                    exit(std::format("[ERROR] Could not find page with name '{}'!", id), PAGE_NOT_FOUND_ERROR);
                    return;
                }


                m_ActivePageID = id;


                Page* page = GetActivePage();

                if (!page) return;

                auto& widgets = page->m_Widgets;

                // we also need to make sure all the widgets get a pointer to us. Pretty cheap. Might just want to bite the bullet and just use std::function anyways.
                for (auto& widget : widgets)
                {
                    if (widget.second) {
                        widget.second->m_Owner = this;
                    }
                }

            }

            Page* GetPage(const std::string& id)
            {
                if (!m_ActiveBook || m_ActiveBook->find(id) == m_ActiveBook->end()) return nullptr;
                return m_ActiveBook->at(id).get();
            }

            Page* GetActivePage()
            {
                return GetPage(m_ActivePageID);
            }


            // forward an event to us
            LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
            {

                // early exit
                if (!m_ActiveBook) return 0;

                if (!GetActivePage()) return 0;




                // forward the event to child widgets
                for (auto& [id, vWidget] : GetActivePage()->m_Widgets) // m_ActivePage->m_Widgets
                {
                    vWidget->on_event(hwnd, msg, wp, lp);
                }
                if (m_Background) m_Background->on_event(hwnd, msg, wp, lp);

                return 0;
            }
    };
}