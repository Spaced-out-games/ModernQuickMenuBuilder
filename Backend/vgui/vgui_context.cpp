#include "vgui_context.h"



namespace vgui
{
    bool LoadBackground(const std::string& pagename, const std::string& path)
    {

        if (!m_Background)
        {
            m_Background = std::make_unique<vgui::VBackground>();
        }


        m_Background->img = Image::load_image(path);
        m_Background->stretch_to_fit(nullptr);
        m_Window->invalidate();
        return true;
    }
}