#pragma once
// TODO: handle collisions!!!!

namespace qmb {




    // --------------------------------------------------
    // Node
    // --------------------------------------------------

    template <class T, class K>
    T* AcceleratedLinkedList<T, K>::Node::get() noexcept
    {
        return value.get();
    }



    // --------------------------------------------------
    // Sizes
    // --------------------------------------------------

    template <class T, class K>
    size_t AcceleratedLinkedList<T, K>::size() const
    {
        return m_Nodes.size();
    }

    template <class T, class K>
    size_t AcceleratedLinkedList<T, K>::live_size() const
    {
        return logical_size;
    }

    template <class T, class K>
    size_t AcceleratedLinkedList<T, K>::capacity() const
    {
        return m_Nodes.capacity();
    }


    // --------------------------------------------------
    // Internals
    // --------------------------------------------------

    template <class T, class K>
    index_t AcceleratedLinkedList<T, K>::findInsertionIndex() const
    {
        if (tail == NULL_INDEX)
            return 0;

        index_t next = m_Nodes[tail].next;
        return (next == NULL_INDEX) ? size() : next;
    }

    // --------------------------------------------------
    // Lookup
    // --------------------------------------------------

    template <class T, class K>
    T* AcceleratedLinkedList<T, K>::get(const K& id)
    {
        auto it = m_LUT.find(id);
        if (it == m_LUT.end())
            return nullptr;

        return m_Nodes[it->second].get();
    }

    template <class T, class K>
    T* AcceleratedLinkedList<T, K>::operator[](const K& id) {
        return get(id);
    }



    // --------------------------------------------------
    // Insert
    // --------------------------------------------------

    template <class T, class K>
    void AcceleratedLinkedList<T, K>::insert(const K& id, std::unique_ptr<T>&& obj)
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

    template <class T, class K>
    void AcceleratedLinkedList<T, K>::remove(index_t idx)
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

    template <class T, class K>
    void AcceleratedLinkedList<T, K>::remove(const K& id)
    {
        auto it = m_LUT.find(id);
        if (it != m_LUT.end())
            remove(it->second);
    }

    template <class T, class K>
    void AcceleratedLinkedList<T, K>::clear()
    {
        while (head != NULL_INDEX)
            remove(head);
    }


    // --------------------------------------------------
    // Iterator
    // --------------------------------------------------

    template <class T, class K>
    struct qmb::AcceleratedLinkedList<T, K>::iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

    private:
        AcceleratedLinkedList<T, K>* list = nullptr;
        index_t current = NULL_INDEX;

    public:
        iterator() = default;
        iterator(AcceleratedLinkedList<T, K>* l, index_t idx) : list(l), current(idx) {}

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

    template <class T, class K>
    typename qmb::AcceleratedLinkedList<T, K>::iterator qmb::AcceleratedLinkedList<T, K>::begin() {
        return iterator(this, head);
    }

    template <class T, class K>
    typename qmb::AcceleratedLinkedList<T, K>::iterator qmb::AcceleratedLinkedList<T, K>::end() {
        return iterator(this, NULL_INDEX);
    }

    template <class T, class K>
    typename qmb::AcceleratedLinkedList<T, K>::iterator qmb::AcceleratedLinkedList<T, K>::rbegin() {
        return iterator(this, tail);
    }

    template <class T, class K>
    typename qmb::AcceleratedLinkedList<T, K>::iterator qmb::AcceleratedLinkedList<T, K>::rend() {
        return iterator(this, NULL_INDEX);
    }


} // namespace qmb
