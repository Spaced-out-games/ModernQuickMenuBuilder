#pragma once
#include "vgui_background.h"
#include "vgui_widget.h"
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

namespace vgui
{
	class Page
	{		



			friend class Context;
			
			

			std::unordered_map<std::string, std::unique_ptr<vgui::Widget>> m_Widgets;


		public:
			/// <summary>
			/// Adds a widget
			/// </summary>
			/// <param name="name"></param>
			/// <param name="widget"></param>
			/// <returns>1 on success, 0 on failure</returns>
			bool add(const std::string& name, std::unique_ptr<vgui::Widget>&& widget)
			{
				// if it's already in the hash map, fail
				if (m_Widgets.find(name) != m_Widgets.end()) return 0;

				m_Widgets[name] = std::move(widget);
				return 1;

			}
			/// <summary>
			/// Adds a widget
			/// </summary>
			/// <param name="name"></param>
			/// <param name="widget"></param>
			/// <returns>1 on success, 0 on failure</returns>
			bool remove(const std::string& name)
			{
				if (m_Widgets.find(name) == m_Widgets.end()) return 0;

				m_Widgets.erase(name);
				return 1;




			}

			vgui::Widget* const get(const std::string& name)
			{
				if (m_Widgets.find(name) == m_Widgets.end()) return nullptr;
				return m_Widgets[name].get();
			}

			bool has(const std::string& name)
			{
				return (m_Widgets.find(name) != m_Widgets.end());
			}



	};

	using Book = std::unordered_map<std::string, std::unique_ptr<vgui::Page>>;





	/// When getting around to BSP implementation (if need be, do the following:
	/// BSP tree as a flat array/vector
	/// Maintain event lookups via two association maps:
	/// string->index; index->widget
	/// 
	/// 
	/// 
	/// left  = 2*i + 1
	/// right = 2 * i + 2
	struct BSPNode {
		std::unique_ptr<Widget> widget;
		float weight;
		alignas(4) bool axis;
	};
}