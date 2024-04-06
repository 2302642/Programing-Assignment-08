/*!******************************************************************************************************************************************************************************************************************************************************************
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
*******************************************************************************************************************************************************************************************************************************************************************/

#ifndef SLLIST_TPP_
#define SLLIST_TPP_

namespace hlp2 {
//##################################################################################################################################################################################################################################################################
//==================================================================================================================================================================================================================================================================
//|                                                                               CONSTRUCTORS FOR SLIST SECTION                                                                                                                                                   |
//==================================================================================================================================================================================================================================================================
    template <typename T> sllist<T> :: sllist(): head{nullptr}, tail{nullptr}, counter{0} { ++object_counter;}                          // default constructor
    template <typename T> sllist<T> :: sllist(sllist const& rhs) {                                                                      // single-argument copy constructor
        Node* current = rhs.head;                                                                                                       // pointing to the head of the list for reference to start
        while (current != nullptr) {                                                                                                    // looping through each node in the list
            push_back(current->data);                                                                                                   // appending each element from the initializer list to the end of this list 
            current = current->next;                                                                                                    // moving to the next node in the list that is being accessed 
        }
        ++object_counter;                                                                                                               // incrementing the object counter
    }
    template <typename T> sllist<T> :: sllist(std::initializer_list<sllist::value_type> const &rhs) {                                   // single-argument constructor with initializer list
        for (const_reference value : rhs) { push_back(value); }                                                                         // appending each element from the initializer list to the end of this list 
        ++object_counter;                                                                                                               // incrementing the object counter
    }
    template <typename T> sllist<T> :: sllist(typename sllist<T>::const_pointer start, typename sllist<T>::const_pointer end) {         // double-argument constructor with range
        typename sllist<T>::const_pointer temp = start;                                                                                 // pointing to the start of the range
        for (; temp != end; ++temp) { push_back(*temp); }                                                                               // creating a new list with elements from start to end
        ++object_counter;                                                                                                               // incrementing the object counter
    }
    template <typename T> sllist<T >:: ~sllist() { clear();   --object_counter; }                                                       // destructor to call clear function to deallocate memory and decrementing object counter           
//==================================================================================================================================================================================================================================================================
//|                                                                               COPY ASSIGNMENT OPERATORS                                                                                                                                                        |
//==================================================================================================================================================================================================================================================================
    template <typename T> sllist<T>& sllist<T>::operator=(sllist const& rhs){                                                           // copy assignment operator that copies the contents of the given list 'rhs' to the current list
        sllist temp {rhs};                                                                                                              // creating // Create a copy of the current list
        swap(temp);                                                                                                                     // swaping the contents of 'temp' with the current list
        return *this;                                                                                                                   // returning a reference to the current list after the swap
    }
    template <typename T> sllist<T>& sllist<T>::operator=(std::initializer_list<sllist::value_type> const & rhs) {                      // copy assignment operator with initializer list
        sllist temp {rhs};                                                                                                              // creating a temporary list 'temp' by using the copy constructor with 'rhs'
        swap(temp);                                                                                                                     // swaping the contents of 'temp' with the current list
        return *this;                                                                                                                   // returning a reference to the current list after the swap
    }
//==================================================================================================================================================================================================================================================================
//|                                                                               CONCATENATION OPERATORS                                                                                                                                                          |
//==================================================================================================================================================================================================================================================================
    template <typename T> sllist<T>& sllist<T>::operator+=(sllist const & rhs){                                                         // compound assignment operator for adding a list
        sllist <T> current{*this};                                                                                                      // createing a temporary list 'current' by copying the contents of the current list
        for(size_t i = 0; i < rhs.size(); i++){  current.push_back(rhs[i]); }                                                           // Appending the elements from the given list 'rhs' to the 'current' list
        swap(current);                                                                                                                  // swaping the contents of 'current' with the current list, effectively appending the elements
        return *this;                                                                                                                   // returning a reference to the current list after the swap
    }
    template <typename T> sllist<T>& sllist<T>::operator += (std::initializer_list<sllist::value_type>const & rhs){                     // compound assignment operator for adding elements from an initializer list
        sllist <T> current{*this};                                                                                                      // createing a copy of the current list
        typename std::initializer_list<value_type>::iterator start = rhs.begin();                                                       // iterator to traverse the initializer list
        for(size_t i = 0; i < rhs.size(); i++){ current.push_back(*(start++)); }                                                        // adding each element from the initializer list to the copy
        swap(current);                                                                                                                  // Swaps the contents of 'current' with the current list, effectively appending the elements
        return *this;                                                                                                                   // returning a reference to the current list after the swap
    }
//==================================================================================================================================================================================================================================================================
//|                                                                               ELEMENT ACCESSOR OPERATORS                                                                                                                                                       |
//==================================================================================================================================================================================================================================================================
    template<typename T> typename sllist<T>::reference sllist<T>::operator[](size_type index){                                          // element access operator to accesses the element at the specified 'index' in the list
        Node * current = head;                                                                                                          // pointing to the head of the list for reference to start
        for(size_type i = 0 ; i < counter; ++i){
            if(i == index){ break; }                                                                                                    // leaving the loop when the specified index is reached
            current = current->next;                                                                                                    // moving to the next node
        }
        return current->data;                                                                                                           // returning a reference to the data stored in the node at the specified index
    }
    template<typename T> typename sllist<T>::const_reference sllist<T>::operator[](size_type index) const{                              // element access operator to accesses the element at the specified 'index' in the list (const version)
        Node * current = head;                                                                                                          // pointing to the head of the list for reference to start
        for(size_type i = 0 ; i < counter; ++i){    
            if(i == index){  break; }                                                                                                   // leaving the loop when the desired specified is reached
            current = current->next;                                                                                                    // moving to the next node
        }
        return current->data;                                                                                                           // returning a const reference to the data stored in the node at the specified index
    }
//==================================================================================================================================================================================================================================================================
//|                                                                                   MODIFIER FUNCTIONS                                                                                                                                                           |
//==================================================================================================================================================================================================================================================================
    template <typename T> void sllist<T>::push_front(const_reference data) {                                                            // adding a new node with the specified value to the front of the linked list
        Node *newNode = new_node(data);                                                                                                 // creating a new node with the given value 
        newNode->next = head;                                                                                                           // setting the next pointer of the new node to the current head
        head = newNode;                                                                                                                 // updating the tail to point to the new node
        if (empty()) { tail = newNode; }                                                                                                // if the list was empty update the tail to point to the new node
        ++counter;                                                                                                                      // incrementing the counter to show the addition of a node
    }  
    template <typename T> void sllist<T>::push_back(const_reference data) {                                                             // adding a new node with the specified value to the back of the linked list
        Node* newNode = new_node(data);                                                                                                 // creating a new node with the given value  
        if (empty()) { head = newNode; }                                                                                                // if the list is empty set head of the node  
        else {   tail->next = newNode; }                                                                                                // else add the new node to the back of the list
        tail = newNode;                                                                                                                 // updating the tail to point to the new node
        ++counter;                                                                                                                      // incrementing the counter to show the addition of a node
    }
    template <typename T> void sllist<T>::pop_front() {                                                                                 // remove and return the value of the node at the front of the linked list
        if (empty()) { return; }                                                                                                        // if the list is empty, return nothing
        Node* temp = head;                                                                                                              // pointing to the head of the list for reference to start
        head = head->next;                                                                                                              // moving the head pointer to the next node
        delete temp;                                                                                                                    // deleting the temp to free memory
        --counter;                                                                                                                      // decrementing the counter to show the removal of a node
    }
    template <typename T> typename sllist<T>::reference sllist<T>::front() {                                                            // returning a reference to the first element of the list
        if (empty()) { throw std::runtime_error("List is empty"); }                                                                     // checking if the list is empty and throwing a runtime error if it is empty
        return head->data;                                                                                                              // returning a reference to the data of the first node in the list
    }
    template <typename T> void sllist<T>::clear() {                                                                                     // remove and return the value of the node at the front of the linked list
        while (!empty()) { pop_front(); }                                                                                               // removing and deleting the first element from the list
        tail = nullptr;                                                                                                                 // setting the tail pointer to nullptr to indicate an empty list
    }
    template <typename T> void sllist<T>::swap(sllist& rhs) {                                                                           // swaping all the contents of this list container with another list container
        std::swap(head, rhs.head);                                                                                                      // Swaping the head with another head in the other list container
        std::swap(tail, rhs.tail);                                                                                                      // Swaping the tail with another tail in the other list container
        std::swap(counter, rhs.counter);                                                                                                // Swaping the counter with another counter in the other list container
    }
//==================================================================================================================================================================================================================================================================
//|                                                                                     CAPACITY STATUS FUNCTIONS                                                                                                                                |
//==================================================================================================================================================================================================================================================================
    template <typename T> typename sllist<T>::size_type sllist<T>::size() const{ return counter; }                                      // to check the number of nodes in the linked list
    template <typename T> bool sllist<T>::empty() const { return counter == 0 ; }                                                       // to check if the linked list is empty
//==================================================================================================================================================================================================================================================================
//|                                                                               STATIC MEMBER FUNCTION SECTION                                                                                                                                 |
//==================================================================================================================================================================================================================================================================
    template<typename T> typename sllist<T>::size_type sllist<T>::object_counter     = 0;                                               // static member initialization for object_counter
    template<typename T> typename sllist<T>::size_type sllist<T>::Node::node_counter = 0;                                               // static member initialization for node_counter
    template <typename T> typename sllist<T>::size_type sllist<T>::object_count(){ return object_counter;               }               // returning the number of objects created from the class
    template <typename T> typename sllist<T>::size_type sllist<T>::node_count()  { return sllist<T>::Node::node_counter; }              // returning the number of nodes created
//==================================================================================================================================================================================================================================================================
//|                                                                               CONSTRUCTORS FOR NODE SECTION                                                                                                                                  |
//==================================================================================================================================================================================================================================================================
    template<typename T> typename sllist<T>::Node* sllist<T>::new_node(sllist::const_reference data) const{                             // creating a new node with the given data
        Node* newnode = new Node(data);                                                                                                 // allocatig memory for a new node and initialize it with the specified data
        return newnode;                                                                                                                 // returning a pointer to the newly created node
    }
    template<typename T> sllist<T>::Node::Node(typename sllist<T>::value_type const &val) : data{val} {++node_counter;}                 // constructing a node with the given value and incrementing the node counter.    
    template<typename T> sllist<T>::Node::~Node(){ --node_counter; }                                                                    // destroying the node and decrementing the node counter.
//==================================================================================================================================================================================================================================================================
//|                                                           NON-MEMBER & OVERLOADED OPERATOR SECTION (overloading "+" operator)                                                                                                                                  |
//==================================================================================================================================================================================================================================================================
    template <typename T> sllist<T> operator+(sllist<T> const& lhs, sllist<T> const& rhs){                                              // Overloaded addition operator for concatenating two lists returns the result
        sllist<T> temp = lhs;                                                                                                           // costructing a list from initializer list
        temp+=rhs;
        return temp;                                                                                                                    // Return the modified list
    }
    template <typename T> sllist<T> operator+(sllist<T> const& lhs, std::initializer_list<typename sllist<T>::value_type> const & rhs){ // Overloaded addition operator for concatenating a list and an initializer list and returns the result (const version)
        sllist<T> temp = lhs;                                                                                                           // costructing a list from initializer list
        temp+=rhs;
        return temp;                                                                                                                    // Return the modified list
    }
    template <typename T> sllist<T> operator+(std::initializer_list<typename sllist<T>::value_type> lhs, const sllist<T>& rhs) {        // Overloaded addition operator for concatenating an initializer list and a list
        sllist<T> temp { lhs };                                                                                                         // costructing a list from initializer list
        temp += rhs;                                                                                                            
        return temp;                                                                                                                    // Return the modified list
    }
    template <typename T> void swap(sllist<T> &lhs , sllist <T> &rhs){                                                                  // Swaps the contents of two lists
        sllist<T> temp = lhs;
        lhs = rhs;
        rhs = temp;
    }
//==================================================================================================================================================================================================================================================================
//|                                                                                   GIVEN CODE SECTION                                                                                                                                                           |
//==================================================================================================================================================================================================================================================================
    template <typename T> std::ostream& operator<<(std::ostream& os, sllist<T> const& list) {                                           // Overloaded stream insertion operator to print the list
      typename sllist<T>::size_type ls_sz = list.size();                                                                                // start at the first node ...
      for (typename sllist<T>::size_type i = 0; i < ls_sz; ++i) { os << list[i] << std::setw(4); }                                      // uses overloaded subscript operator for class sllist ...
      os << "\n";                                                                                                                       // extra newline for readability
      return os;
    }
//##################################################################################################################################################################################################################################################################
}

#endif // SLLIST_TPP_

