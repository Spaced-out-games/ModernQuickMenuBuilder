#pragma once
#include "vgui.h"
#include "vgui_node.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>





namespace vgui
{

	/// PLAN:
	/// Reuse the same layered architecture used in the game engine, with a flat linked-list structure
	/// Layers, when inserted into a layer stack, are sorted by Z, and widgets, when inserted into a layer
	/// stack, are assigned the appropriate layer (or a new one is created). Needs to be doubly-linked
	/// for O(1) deletions. An auxillary hash map of name->index is also populated for the sake of
	/// API integration. It might also be better to make the widget lookup table at the layerstack
	/// scope as opposed to the layer scope, so (a), it's O(1), and (b) reduces ambiguity. 
	/// This'll mean making it map to (layer index, widget index) as opposed to (widget index)

	
	struct Layer
	{




		//using index_t = WidgetNode::index_t;
		//constexpr index_t NULLWIDGET = WidgetNode::NULLWIDGET;
		// string hash->index map. Worry about it later
		std::unordered_map<string_hash_t, size_t> m_WidgetLookupByName;
        int z = 0;
		WidgetNode::index_t pHead = WidgetNode::NULLWIDGET;
		WidgetNode::index_t pTail = WidgetNode::NULLWIDGET;
		size_t				m_LogicalSize = 0;
		std::vector<WidgetNode> m_Widgets;


		size_t logical_size() {
			return m_LogicalSize;
		}

		bool is_logically_empty() {
			return logical_size() == 0;
		}
		size_t free_count() {
			return size() - logical_size();
		}
		bool is_empty()
		{
			return size() == 0;
		}

		size_t size() {
			return m_Widgets.size();
		}

		WidgetNode::index_t findInsertionIndex()
		{
			// insert at [0] if empty
			if (pTail == WidgetNode::NULLWIDGET) return 0;

			// if tail's next is null, insert at end of vector
			if (m_Widgets[pTail].m_Next == WidgetNode::NULLWIDGET) return size();

			// otherwise, just use the preallocated one
			return m_Widgets[pTail].m_Next;

		}
		Widget* head()
		{
			if (pHead == WidgetNode::NULLWIDGET) return nullptr;
			return m_Widgets[pHead].m_Widget.get();
		}
		Widget* tail()
		{
			if (pTail == WidgetNode::NULLWIDGET) return nullptr;
			return m_Widgets[pTail].m_Widget.get();
		}

		void insert(const std::string& name, std::unique_ptr<Widget>&& widget)
		{
			if (widget == nullptr) return;
			WidgetNode::index_t pTarget = findInsertionIndex();

			// first insertion
			if (pTarget == 0 && pHead == WidgetNode::NULLWIDGET) {
				pHead = 0;
				pTail = 0;
				m_Widgets.emplace_back(name, WidgetNode::NULLWIDGET, WidgetNode::NULLWIDGET, std::move(widget));
				m_WidgetLookupByName[hash(name)] = 0;
				m_LogicalSize++;
				return;
			}
			// use prealloc'd one. Only update previous to tail
			if (pTarget != size())
			{

				WidgetNode& zombie = m_Widgets[pTarget];

				zombie.m_Widget = std::move(widget);
				zombie.m_NameHash = hash(name);
				zombie.m_Prev = pTail;
				m_Widgets[pTail].m_Next = pTarget;
				pTail = pTarget;
				m_LogicalSize++;
				m_WidgetLookupByName[hash(name)] = pTarget;
				return;
			}

			// Otherwise, We gotta allocate
			m_Widgets.emplace_back(name, pTail, m_Widgets[pTail].m_Next, std::move(widget));

			m_Widgets[pTail].m_Next = pTarget;
			pTail = pTarget;
			m_LogicalSize++;
			m_WidgetLookupByName[hash(name)] = pTarget;
		}

		// Canonical index removal; will wrap with name access later
		void remove(WidgetNode::index_t index)
		{
			if (index >= size() || m_Widgets[index].m_Widget == nullptr)
				return;

			WidgetNode::index_t prev = m_Widgets[index].m_Prev;
			WidgetNode::index_t next = m_Widgets[index].m_Next;

			// unlink from live list
			if (prev != WidgetNode::NULLWIDGET)
				m_Widgets[prev].m_Next = next;
			else
				pHead = next;

			if (next != WidgetNode::NULLWIDGET)
				m_Widgets[next].m_Prev = prev;
			else
				pTail = prev;   // only move pTail if we removed the live tail

			// zombify: append AFTER live tail
			WidgetNode::index_t zombieHead =
				(pTail != WidgetNode::NULLWIDGET) ? m_Widgets[pTail].m_Next : WidgetNode::NULLWIDGET;

			m_Widgets[index].m_Prev = pTail;
			m_Widgets[index].m_Next = zombieHead;

			if (pTail != WidgetNode::NULLWIDGET)
				m_Widgets[pTail].m_Next = index;

			if (zombieHead != WidgetNode::NULLWIDGET)
				m_Widgets[zombieHead].m_Prev = index;

			// cleanup
			m_Widgets[index].m_Widget = nullptr;
			m_WidgetLookupByName.erase(m_Widgets[index].m_NameHash);
			m_LogicalSize--;
		}

		void remove(const std::string& name)
		{
			remove(m_WidgetLookupByName[hash(name)]);
		}

		Widget* getWidgetById(const std::string& name)
		{
			if(m_WidgetLookupByName.find(hash(name)) == m_WidgetLookupByName.end()) return nullptr;
			return m_Widgets[m_WidgetLookupByName[hash(name)]].m_Widget.get();
		}






        
        


	};
}