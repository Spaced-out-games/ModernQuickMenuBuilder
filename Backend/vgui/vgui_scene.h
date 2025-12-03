#pragma once
#include "vgui_background.h"
#include "vgui_widget.h"
#include <map>
#include <memory>

namespace vgui
{
	class Scene
	{		
			using id_type = uint32_t;


			friend class Context;
			
			id_type m_CurrentId = 0;
			std::map<id_type, std::unique_ptr<vgui::Widget>> m_Widgets;

		public:
			id_type insert(std::unique_ptr <vgui::Widget>&& widget)
			{
				assert(widget != nullptr);

				// Find next free ID
				while (m_Widgets.contains(m_CurrentId)) {
					m_CurrentId++;
				}

				id_type id = m_CurrentId;
				m_Widgets[id] = std::move(widget);

				return id;
			}



			void remove(id_type id)
			{
				if (m_Widgets.find(id) != m_Widgets.end())
				{
					m_Widgets.erase(id);
				}

			}

			vgui::Widget* get(id_type id)
			{
				if (m_Widgets.contains(id))
				{
					return m_Widgets[id].get();
				}
				return nullptr;
			}

	};
}