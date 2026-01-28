#include "QMBApplication.h"
#include "../vgui/vgui_event.h"

namespace qmb {
	void QMBApplication::fire(const vgui::Event& evt) {
		assert(m_Window != nullptr);
		if(m_Window) m_Window->m_LayerStack.on_event(evt);
	}
	void QMBApplication::exit(const std::string& msg) {
		assert(this != nullptr);
		vgui::Event evt;
		evt.app = this;
		evt.type = vgui::EventType::LIFETIME_DTOR_EVENT;
		// notify the layers to the destructor being called
		fire(evt);
		status = 1;
	}

	void QMBApplication::link_window(vgui::VWindow& window)
	{
		m_Window = &window;
	}



}