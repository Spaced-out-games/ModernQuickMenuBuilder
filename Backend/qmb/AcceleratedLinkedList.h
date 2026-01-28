#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "hash.h"

namespace qmb {



    template <class T>
    struct AcceleratedLinkedList
    {
        struct Node
        {
            std::unique_ptr<T> value;
            index_t prev = NULL_INDEX;
            index_t next = NULL_INDEX;
            string_hash_t name_hash = 0;

            T* get() noexcept;
        };

        std::vector<Node> m_Nodes;
        std::unordered_map<string_hash_t, index_t> m_LUT;

        index_t head = NULL_INDEX;
        index_t tail = NULL_INDEX;
        size_t logical_size = 0;

        // sizes
        size_t size() const;
        size_t live_size() const;

        // internals
        index_t findInsertionIndex() const;

        // API
        T* get(const std::string& name);
        void insert(const std::string& name, std::unique_ptr<T>&& obj);
        void remove(index_t idx);
        void remove(const std::string& name);
        void clear();

        T* operator[](const std::string& name);

        // -------------------
        // Iterator declaration (bidirectional)
        struct iterator;
        iterator begin();
        iterator end();

        // Optional: reverse helpers using same iterator
        iterator rbegin(); // starts at tail
        iterator rend();   // points before head
    };

} // namespace qmb

#include "AcceleratedLinkedList.inl"
