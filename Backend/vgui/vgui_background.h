#pragma once

#include <Windows.h>
#include "../platform/win32/Image.h"
#include "vgui_widget.h"
namespace native { class WidgetBase; }
namespace qmb { class Image; }
namespace vgui
{
    struct VBackground : vgui::Widget
    {
        /// <summary>
        /// The image we need to draw
        /// </summary>
        qmb::Image img;

        /// <summary>
        /// Draws this widget
        /// </summary>
        /// <param name="hdc">Hardware device to draw with</param>
        void draw(HDC hdc) override;

        /// <summary>
        /// Responds to and handles a vgui Event
        /// </summary>
        /// <param name="evt">An event to handle</param>
        /// <returns>Whether or not this widget should block propagate to sister widgets</returns>
        bool on_event(const Event& evt) override;

        /// <summary>
        /// Constructs a vgui Background widget
        /// </summary>
        /// <param name="owner">The native widget that is to own this Background</param>
        VBackground(native::WidgetBase& owner, const std::string& img_path);

    };
}
