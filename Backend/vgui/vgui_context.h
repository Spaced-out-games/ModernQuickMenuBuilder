#pragma once
#include <Windows.h>
#include "vgui_widget.h"
#include <vector>
#include <cassert>
#include "vgui_scene.h"

namespace vgui
{


    struct Context {
        private:
            Scene* m_ActiveScene = nullptr;

        public:
        
            void draw(HDC hdc) {

                if (!m_ActiveScene) return;

                for (auto& [id, vWidget] : m_ActiveScene->m_Widgets)
                {
                    vWidget->draw(hdc); // OK, vWidget is a reference to unique_ptr
                }
            }

            void SetActiveScene(Scene& scene)
            {
                m_ActiveScene = &scene;
            }
            Scene* GetActiveScene()
            {
                return m_ActiveScene;
            }


            // forward an event to us
            LRESULT on_event(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
            {

                // early exit
                if (!m_ActiveScene) return 0;

                // forward the event to child widgets
                for (auto& [id, vWidget] : m_ActiveScene->m_Widgets)
                {
                    vWidget->on_event(hwnd, msg, wp, lp);
                }

                return 0;

                // let windows handle the event
                //return DefWindowProc(hwnd, msg, wp, lp);
            }
    };
}