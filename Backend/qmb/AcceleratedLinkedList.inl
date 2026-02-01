#pragma once
// TODO: handle collisions!!!!

namespace qmb {




    // --------------------------------------------------
    // Node
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<T, K, order_fn>::Node::get() noexcept
    {
        return value.get();
    }



    // --------------------------------------------------
    // Sizes
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<T, K, order_fn>::size() const
    {
        return m_Nodes.size();
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<T, K, order_fn>::live_size() const
    {
        return logical_size;
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<T, K, order_fn>::capacity() const
    {
        return m_Nodes.capacity();
    }


    // --------------------------------------------------
    // Internals
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    index_t AcceleratedLinkedList<T, K, order_fn>::findInsertionIndex() const
    {
        if (tail == NULL_INDEX)
            return 0;

        index_t next = m_Nodes[tail].next;
        return (next == NULL_INDEX) ? size() : next;
    }

    // --------------------------------------------------
    // Lookup
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<T, K, order_fn>::get(const K& id)
    {
        auto it = m_LUT.find(id);
        if (it == m_LUT.end())
            return nullptr;

        return m_Nodes[it->second].get();
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<T, K, order_fn>::operator[](const K& id) {
        return get(id);
    }



    // --------------------------------------------------
    // Insert
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<T, K, order_fn>::insert(const K& id, std::unique_ptr<T>&& obj)
    {
        if (!obj || m_LUT.contains(id)) return;

        index_t idx = findInsertionIndex();

        if (idx == size()) m_Nodes.push_back({});

        Node& n = m_Nodes[idx];
        n.value = std::move(obj);
        n.prev = tail;
        n.next = NULL_INDEX;

        if (tail != NULL_INDEX)
            m_Nodes[tail].next = idx;
        else
            head = idx;

        tail = idx;
        m_LUT[id] = idx;
        logical_size++;
    }

    // --------------------------------------------------
    // Remove
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<T, K, order_fn>::remove(index_t idx)
    {
        if (idx >= size() || !m_Nodes[idx].value)
            return;

        Node& n = m_Nodes[idx];
        index_t p = n.prev;
        index_t nx = n.next;

        // unlink from live list
        if (p != NULL_INDEX) m_Nodes[p].next = nx;
        else head = nx;

        if (nx != NULL_INDEX) m_Nodes[nx].prev = p;
        else tail = p;

        // zombify
        index_t zombie_head =
            (tail != NULL_INDEX) ? m_Nodes[tail].next : NULL_INDEX;

        n.prev = tail;
        n.next = zombie_head;

        if (tail != NULL_INDEX)
            m_Nodes[tail].next = idx;

        if (zombie_head != NULL_INDEX)
            m_Nodes[zombie_head].prev = idx;

        m_LUT.erase(n.name_hash);
        n.name_hash = 0;
        n.value.reset();
        logical_size--;
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<T, K, order_fn>::remove(const K& id)
    {
        auto it = m_LUT.find(id);
        if (it != m_LUT.end())
            remove(it->second);
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<T, K, order_fn>::clear()
    {
        while (head != NULL_INDEX)
            remove(head);
    }


    // --------------------------------------------------
    // Iterator
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    struct qmb::AcceleratedLinkedList<T, K, order_fn>::iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

    private:
        AcceleratedLinkedList<T, K, order_fn>* list = nullptr;
        index_t current = NULL_INDEX;

    public:
        iterator() = default;
        iterator(AcceleratedLinkedList<T, K, order_fn>* l, index_t idx) : list(l), current(idx) {}

        reference operator*() const { return *list->m_Nodes[current].get(); }
        pointer operator->() const { return list->m_Nodes[current].get(); }

        iterator& operator++() {
            if (current != NULL_INDEX) {
                current = list->m_Nodes[current].next;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        iterator& operator--() {
            if (current == NULL_INDEX) {
                // If at end(), go to tail
                current = list->tail;
            }
            else {
                current = list->m_Nodes[current].prev;
            }
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const iterator& rhs) const {
            return list == rhs.list && current == rhs.current;
        }

        bool operator!=(const iterator& rhs) const { return current != rhs.current; }
    };

    // --------------------------------------------------
    // begin/end
    // --------------------------------------------------

    template <class T, class K, order_pfn_t<T> order_fn>
    typename qmb::AcceleratedLinkedList<T, K, order_fn>::iterator qmb::AcceleratedLinkedList<T, K, order_fn>::begin() {
        return iterator(this, head);
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    typename qmb::AcceleratedLinkedList<T, K, order_fn>::iterator qmb::AcceleratedLinkedList<T, K, order_fn>::end() {
        return iterator(this, NULL_INDEX);
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    typename qmb::AcceleratedLinkedList<T, K, order_fn>::iterator qmb::AcceleratedLinkedList<T, K, order_fn>::rbegin() {
        return iterator(this, tail);
    }

    template <class T, class K, order_pfn_t<T> order_fn>
    typename qmb::AcceleratedLinkedList<T, K, order_fn>::iterator qmb::AcceleratedLinkedList<T, K, order_fn>::rend() {
        return iterator(this, NULL_INDEX);
    }


} // namespace qmb
