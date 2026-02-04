#pragma once

namespace qmb {




    // --------------------------------------------------
    // Node
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<K, T, order_fn>::Node::get() noexcept
    {
        return value.get();
    }
    template <class K, class T, order_pfn_t<T> order_fn>
    T& AcceleratedLinkedList<K, T, order_fn>::Node::operator*() noexcept { return *value; }



    // --------------------------------------------------
    // Sizes
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<K, T, order_fn>::size() const
    {
        return m_Nodes.size();
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<K, T, order_fn>::live_size() const
    {
        return m_AliveCount;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    size_t AcceleratedLinkedList<K, T, order_fn>::capacity() const
    {
        return m_Nodes.capacity();
    }


    // --------------------------------------------------
    // Internals
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    index_t AcceleratedLinkedList<K, T, order_fn>::findInsertionIndex()
    {
        if (m_Tail == NULL_LINK || m_Nodes[m_Tail].next == NULL_LINK) {
            m_Nodes.emplace_back();
            return m_Nodes.size() - 1;
        }
        return m_Nodes[m_Tail].next;
    }


    template <class K, class T, order_pfn_t<T> order_fn>
    index_t AcceleratedLinkedList<K, T, order_fn>::findInsertionNeighbors(const T& item) const
    {
        // No ordering? just append after tail
        if constexpr (order_fn == nullptr) return m_Tail;

        index_t prev_candidate = NULL_LINK; // node after which we insert
        index_t current = m_Head;

        // Walk forward from head until we find the first node
        // where 'item' should be inserted **before** the current node
        while (current != NULL_LINK)
        {
            // if item should come before 'current', stop
            if (order_fn(item, *m_Nodes[current].value)) break;

            // otherwise, move forward
            prev_candidate = current;
            current = m_Nodes[current].next;
        }

        // prev_candidate == NULL_LINK -> insert at head
        // otherwise, insert after prev_candidate
        return prev_candidate;
    }


    // --------------------------------------------------
    // Lookup
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<K, T, order_fn>::get(const K& id)
    {
        auto it = m_LUT.find(id);
        if (it == m_LUT.end())
            return nullptr;

        return m_Nodes[it->second].get();
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    T* AcceleratedLinkedList<K, T, order_fn>::operator[](const K& id) {
        return get(id);
    }



    // --------------------------------------------------
    // Insert
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<K, T, order_fn>::insert(const K& id, std::unique_ptr<T>&& obj)
    {
        if (!obj || m_LUT.contains(id)) return;

        // Step 1: find node (reuse tail->next or append)
        index_t target = findInsertionIndex();

        // Step 2: move object in
        m_Nodes[target].value = std::move(obj);

        // Step 3: register in LUT
        m_LUT[id] = target;

        // Step 4: find where to insert in live list
        index_t prev = findInsertionNeighbors(*m_Nodes[target].value);

        if (prev == NULL_LINK)
        {
            // insert at head
            m_Nodes[target].prev = NULL_LINK;
            m_Nodes[target].next = m_Head;

            if (m_Head != NULL_LINK)
                m_Nodes[m_Head].prev = target;

            m_Head = target;
            if (m_Tail == NULL_LINK) m_Tail = target;
        }
        else
        {
            // insert after prev
            index_t next = m_Nodes[prev].next;
            m_Nodes[target].prev = prev;
            m_Nodes[target].next = next;
            m_Nodes[prev].next = target;

            if (next != NULL_LINK)
                m_Nodes[next].prev = target;
            else
                m_Tail = target;
        }

        ++m_AliveCount;
    }



    // --------------------------------------------------
    // Remove
    // --------------------------------------------------



    template <class K, class T, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<K, T, order_fn>::remove(const K& id)
    {
        // Don't destroy what isn't there
        if (!m_LUT.contains(id) || m_AliveCount == 0) return;

        // get the index of the target node
        index_t target = m_LUT[id];
        index_t prev = m_Nodes[target].prev;
        index_t next = m_Nodes[target].next;

        // update sister node pointers, if applicable.
        if (prev != NULL_LINK) m_Nodes[prev].next = next;
        if (next != NULL_LINK) m_Nodes[next].prev = prev;

        // if it's the head or tail, we update those values, too
        if (target == m_Head) m_Head = m_Nodes[m_Head].next;
        if (target == m_Tail) m_Tail = m_Nodes[m_Tail].prev;

        // destroy the asset
        m_Nodes[target].value.reset();

        index_t tail_next = NULL_LINK;
        if (m_Tail != NULL_LINK) {
            tail_next = m_Nodes[m_Tail].next;
            // tail should point to this node
            m_Nodes[m_Tail].next = target;
        }
        if (tail_next != NULL_LINK) m_Nodes[tail_next].prev = target;

        m_Nodes[target].prev = m_Tail;
        m_Nodes[target].next = tail_next;


        // cleanup stuff
        m_LUT.erase(id);
        // always decrement
        m_AliveCount--;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    void AcceleratedLinkedList<K, T, order_fn>::clear()
    {
        m_LUT.clear();
        m_Nodes.clear();
        m_Head = NULL_LINK;
        m_Tail = NULL_LINK;

    }

    // --------------------------------------------------
    // Iterator
    // --------------------------------------------------

    template <class K, class T, order_pfn_t<T> order_fn>
    AcceleratedLinkedList<K, T, order_fn>::iterator::iterator(AcceleratedLinkedList* list, index_t idx) :
        m_List(list),
        m_Index(idx)
    {}

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator::reference
        AcceleratedLinkedList<K, T, order_fn>::iterator::operator*() const {
        assert(m_List);
        assert(m_Index != NULL_LINK);
        auto* p = m_List->m_Nodes[m_Index].value.get();
        if (p == nullptr)
        {
            __debugbreak();
        }

        assert(p != nullptr);
        return *p;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator::pointer
        AcceleratedLinkedList<K, T, order_fn>::iterator::operator->() const {

        T* target = &(**this);

        assert(target);

        return target;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator&
        AcceleratedLinkedList<K, T, order_fn>::iterator::operator++() {
        assert(m_List);
        if (m_Index != NULL_LINK) {
            m_Index = m_List->m_Nodes[m_Index].next;
        }


        return *this;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator
        AcceleratedLinkedList<K, T, order_fn>::iterator::operator++(int) {
        iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    bool AcceleratedLinkedList<K, T, order_fn>::iterator::operator==(
        const iterator& other
        ) const {
        return m_List == other.m_List && m_Index == other.m_Index;
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    bool AcceleratedLinkedList<K, T, order_fn>::iterator::operator!=(
        const iterator& other
        ) const {
        return !(*this == other);
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator AcceleratedLinkedList<K, T, order_fn>::begin() {
        return iterator(this, m_Head);
    }

    template <class K, class T, order_pfn_t<T> order_fn>
    typename AcceleratedLinkedList<K, T, order_fn>::iterator AcceleratedLinkedList<K, T, order_fn>::end() {
        return iterator(this, m_Tail); // was NULL_LINK
    }




} // namespace qmb
