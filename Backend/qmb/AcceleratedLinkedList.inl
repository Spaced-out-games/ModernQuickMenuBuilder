#pragma once
// TODO: handle collisions!!!!

namespace qmb {




    // --------------------------------------------------
    // Node
    // --------------------------------------------------

    template <class T>
    T* AcceleratedLinkedList<T>::Node::get() noexcept
    {
        return value.get();
    }



    // --------------------------------------------------
    // Sizes
    // --------------------------------------------------

    template <class T>
    size_t AcceleratedLinkedList<T>::size() const
    {
        return m_Nodes.size();
    }

    template <class T>
    size_t AcceleratedLinkedList<T>::live_size() const
    {
        return logical_size;
    }

    // --------------------------------------------------
    // Internals
    // --------------------------------------------------

    template <class T>
    index_t AcceleratedLinkedList<T>::findInsertionIndex() const
    {
        if (tail == NULL_INDEX)
            return 0;

        index_t next = m_Nodes[tail].next;
        return (next == NULL_INDEX) ? size() : next;
    }

    // --------------------------------------------------
    // Lookup
    // --------------------------------------------------

    template <class T>
    T* AcceleratedLinkedList<T>::get(const std::string& name)
    {
        auto it = m_LUT.find(hash(name));
        if (it == m_LUT.end())
            return nullptr;

        return m_Nodes[it->second].get();
    }

    template <class T>
    T* AcceleratedLinkedList<T>::operator[](const std::string& name) {
        return get(name);
    }



    // --------------------------------------------------
    // Insert
    // --------------------------------------------------

    template <class T>
    void AcceleratedLinkedList<T>::insert(const std::string& name, std::unique_ptr<T>&& obj)
    {
        if (!obj)
            return;

        string_hash_t h = hash(name);
        if (m_LUT.contains(h))
            return;

        index_t idx = findInsertionIndex();

        if (idx == size())
            m_Nodes.push_back({});

        Node& n = m_Nodes[idx];
        n.value = std::move(obj);
        n.name_hash = h;
        n.prev = tail;
        n.next = NULL_INDEX;

        if (tail != NULL_INDEX)
            m_Nodes[tail].next = idx;
        else
            head = idx;

        tail = idx;
        m_LUT[h] = idx;
        logical_size++;
    }

    // --------------------------------------------------
    // Remove
    // --------------------------------------------------

    template <class T>
    void AcceleratedLinkedList<T>::remove(index_t idx)
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

    template <class T>
    void AcceleratedLinkedList<T>::remove(const std::string& name)
    {
        auto it = m_LUT.find(hash(name));
        if (it != m_LUT.end())
            remove(it->second);
    }

    template <class T>
    void AcceleratedLinkedList<T>::clear()
    {
        while (head != NULL_INDEX)
            remove(head);
    }


    // --------------------------------------------------
    // Iterator
    // --------------------------------------------------

    template <class T>
    struct qmb::AcceleratedLinkedList<T>::iterator {
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

    private:
        AcceleratedLinkedList<T>* list = nullptr;
        index_t current = NULL_INDEX;

    public:
        iterator() = default;
        iterator(AcceleratedLinkedList<T>* l, index_t idx) : list(l), current(idx) {}

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

    template <class T>
    typename qmb::AcceleratedLinkedList<T>::iterator qmb::AcceleratedLinkedList<T>::begin() {
        return iterator(this, head);
    }

    template <class T>
    typename qmb::AcceleratedLinkedList<T>::iterator qmb::AcceleratedLinkedList<T>::end() {
        return iterator(this, NULL_INDEX);
    }

    template <class T>
    typename qmb::AcceleratedLinkedList<T>::iterator qmb::AcceleratedLinkedList<T>::rbegin() {
        return iterator(this, tail);
    }

    template <class T>
    typename qmb::AcceleratedLinkedList<T>::iterator qmb::AcceleratedLinkedList<T>::rend() {
        return iterator(this, NULL_INDEX);
    }


} // namespace qmb
