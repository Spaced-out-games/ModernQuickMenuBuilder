#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "hash.h"

namespace qmb {


    /// <summary>
    /// Accelerated linked list data structure. Conceptually, it's a linked list with a human-readable
    /// interface to access and mutate Ts with ease. There is no need to manage memory by the end user,
    /// reshuffle items when resizing, or update hash map keys.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    template <class T, class K = std::string>
    struct AcceleratedLinkedList
    {
        /// <summary>
        /// Linked list node
        /// </summary>
        struct Node
        {
            std::unique_ptr<T> value;
            index_t prev = NULL_INDEX;
            index_t next = NULL_INDEX;

            T* get() noexcept;
        };

        /// The pool of nodes
        std::vector<Node> m_Nodes;

        // Lookup table
        std::unordered_map<K, index_t> m_LUT;

        // Head of the linked list
        index_t head = NULL_INDEX;

        // Tail of the linked list
        index_t tail = NULL_INDEX;

        // Number of nodes actively in use
        size_t logical_size = 0;

        // Number of alive and dead nodes in the linked list
        size_t size() const;
        // Number of alive nodes in the linked list
        size_t live_size() const;

        // Gets the number of slots allocated before a resize is needed
        size_t capacity() const;

        // Finds where in the linked list to insert another node.
        index_t findInsertionIndex() const;

        // Gets a node by name
        T* get(const K& id);

        // Inserts a node by name
        void insert(const K& id, std::unique_ptr<T>&& obj);

        // Removes a node by index
        void remove(index_t idx);

        // Removes a node by name
        void remove(const K& id);

        // Clears the linked list
        void clear();

        // Array access operator, by name
        T* operator[](const K& id);

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
