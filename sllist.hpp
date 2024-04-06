/*!*********************************************************************************************************************************************************************************************************************
\file       sllist.hpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202
\par        Section:         RSE
\par        Tutorial:        assinment 08
\par        File created on: 20/03/2024
\brief      Singly Linked List Implementation using class template

\par        File information:
            This file contains 
            4 constructurs & 1 destructor function 
            2 copy assignment, 2 concatenation & 2 element accessor operators
            6 modifer functions
            2 capacity & 2 object counter status functions

            non-member functions:
            3 overloaded "+" operator functions
            1 overloaded "<<" operator functions
            1 swap fucntion
            to be called by main inlistint-driver.
***********************************************************************************************************************************************************************************************************************/
#ifndef SLLIST_H 
#define SLLIST_H 

#include <iostream>                // For input/output streams
#include <iomanip>                 // For std::setw
#include <stdexcept>               // For std::runtime_error
#include <initializer_list>        // For std::initializer_list
#include <string>

namespace hlp2 {
//######################################################################################################################################################################################################################
    template <typename T>
    class sllist {
    public:
        using size_type = size_t;                                                   // default definition for size.
        using value_type = T;                                                       // default definition for value.
        using reference = value_type&;                                              // default definition for reference.
        using const_reference = const value_type&;                                  // default definition for const reference.
        using pointer = value_type*;                                                // default definition for pointer.
        using const_pointer = const value_type*;                                    // default definition for const pointer.
//==================================================================================================================================================================================================================================================================
//|                                                                               CONSTRUCTORS FOR SLIST SECTION                                                                                                                                                   |
//==================================================================================================================================================================================================================================================================
        sllist();                                                                   // default constructor
        sllist(sllist const&);                                                      // copy constructor
        sllist(std::initializer_list<value_type> const&);                           // single-argument constructor with initializer list
        sllist(const_pointer, const_pointer);                                       // double-argument Constructor with range
        ~sllist();                                                                  // destructor

//==================================================================================================================================================================================================================================================================
//|                                                                               COPY ASSIGNMENT OPERATORS                                                                                                                                                        |
//==================================================================================================================================================================================================================================================================
        sllist<T>& operator=(sllist const&);                                        // copy assignment with another sllist object using copy-and-swap idiom
        sllist<T>& operator=(std::initializer_list<value_type>const&);
//==================================================================================================================================================================================================================================================================
//|                                                                               CONCATENATION OPERATORS                                                                                                                                                          |
//==================================================================================================================================================================================================================================================================
        sllist<T>& operator+=(sllist const&);                                       // Concatenation assignment operator for adding a list.
        sllist<T>& operator+=(std::initializer_list<value_type> const&);            // Concatenation assignment operator for adding elements from an initializer list.
//==================================================================================================================================================================================================================================================================
//|                                                                               ELEMENT ACCESSOR OPERATORS                                                                                                                                                       |
//==================================================================================================================================================================================================================================================================
        reference operator[](size_type index);                                      // returning the size_type(int) data of node at position index
        const_reference operator[](size_type index) const;                          // returning the size_type(int) data of node at position index (const version).
//==================================================================================================================================================================================================================================================================
//|                                                                                   MODIFIER FUNCTIONS                                                                                                                                                           |
//==================================================================================================================================================================================================================================================================
        void push_front(const_reference);                                           // adding a new node with the specified value to the front of the linked list.
        void push_back(const_reference);                                            // adding a new node with the specified value to the back of the linked list.
        void pop_front();                                                           // remove and return the value of the node at the front of the linked list
        reference front();                                                          // Returning the reference to the first element of the list.
        void clear();                                                               // remove and return the value of the node at the front of the linked list
        void swap(sllist&);                                                         // swaping all the contents ofthis ListInt container with another ListInt container

//==================================================================================================================================================================================================================================================================
//|                                                                                     CAPACITY STATUS FUNCTIONS                                                                                                                                |
//==================================================================================================================================================================================================================================================================
        size_type size() const;                                                     // to check the number of nodes in the linked list
        bool empty() const;                                                         // to check if the linked list is empty
//==================================================================================================================================================================================================================================================================
//|                                                                               STATIC MEMBER FUNCTION SECTION                                                                                                                                 |
//==================================================================================================================================================================================================================================================================
        static size_type object_count();                                            // static member function that counts and returns the total number of objects created
        static size_type node_count();                                              // static member function that counts the total number of nodes created.
//==================================================================================================================================================================================================================================================================
//|                                                                               CONSTRUCTORS FOR NODE SECTION                                                                                                                                  |
//==================================================================================================================================================================================================================================================================
    private:
        struct Node {
            value_type data;                                                        // Data member to store the value
            Node* next{ nullptr };                                                  // Pointer to the next node in the list
            Node(value_type const&);                                                // Constructor for Node
            ~Node();                                                                // Destructor for Node

            static size_type node_counter;                                          // Counter for node objects
        };

        Node* head {nullptr};                                                       // Pointer to the first node in the list
        Node* tail {nullptr};                                                       // Pointer to the last node in the list
        size_type counter {0};                                                      // Counter for the number of elements in the list
        static size_type object_counter;                                            // Counter for list objects
        Node* new_node(const_reference) const;                                      // Creates a new node with the given data
    };
//==================================================================================================================================================================================================================================================================
//|                                                           NON-MEMBER & OVERLOADED OPERATOR SECTION (overloading "+" operator)                                                                                                                                  |
//==================================================================================================================================================================================================================================================================
    template <typename T> void swap(sllist<T>& lhs, sllist<T>& rhs);                                        // Swaping the contents of two lists.
    template <typename T> sllist<T> operator+(sllist<T> const&, sllist<T> const&);                          // Concatenating two lists 
    template <typename T> sllist<T> operator+(sllist<T> const&, std::initializer_list<sllist<T>> const&);   // Concatenating a list and an initializer list
    template <typename T> sllist<T> operator+(std::initializer_list<sllist<T>> const&, sllist<T> const&);   // Concatenating an initializer list and a list
    template <typename T> std::ostream& operator<<(std::ostream& os, const sllist<T>& rhs);                 // Overloaded stream insertion operator for printing the list
//######################################################################################################################################################################################################################
}
#include "sllist.tpp"
#endif // SLLIST_H

