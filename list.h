#ifndef LIST_H
#define LIST_H

#include <typeinfo>
#include <stdexcept>
#include "memtrace.h"

/// @brief A list item consisting of a T type item and a pointer to the next element
/// @tparam T 
template <typename T>
class listItem{
    T item;
    listItem<T>* next;

    public:
        /// @brief Default constructor (no name, next is nullptr)
        listItem():next(nullptr){}

        /// @brief Constructor for the list item
        /// @param newItem the item to contain (next is nullptr)
        listItem(const T& newItem):item(newItem), next(nullptr){}

        /// @brief Assings the item and next of the given list item to this object
        /// @param newItem the list item to copy
        /// @returns A reference to this object
        listItem& operator=(const listItem<T>& newItem){
            if(this != &newItem){
                item = newItem.item;

                delete next;

                next = (newItem.next != nullptr) ? new listItem<T>(*newItem.next) : nullptr;
            }
            return *this;
        }

        /// @brief Copy constructor for the list item
        /// @param newItem the list item to copy
        listItem(const listItem<T>& newItem):item(newItem.item), next(nullptr){
            if(newItem.next != nullptr){
                next = new listItem<T>(*newItem.next);
            }
        }

        /// @brief Returns a reference to the item of this object
        T& getItem(){return item;}

        /// @brief Returns a constant reference to the item of this object 
        const T& getItem() const{return item;}

        /// @brief Returns a pointer to the next element 
        listItem<T>* getNext()const{return next;}

        template <typename U>
        friend class List;
};

class bfsData;
class Junction;

//EGESZ LISTAT TESZTELNI
/// @brief A linked list of listItems
/// @tparam T 
template <typename T> 
class List{
    size_t n;
    listItem<T>* arr;

    /// @brief Finds the 'i'th element in the list if it exists
    /// @param i index
    /// @returns A pointer to the element
    listItem<T>* find(size_t i) const{
        if(i>=n) throw std::out_of_range("Error: Index is out of range!");
        listItem<T>* ret = arr;
        for (size_t j = 0; j < i; j++) {
            ret = ret->next;
        }
        return ret;
    }

    public:
        /// @brief Constructor for the list 
        /// @param size the size which the list should be (default 0)
        List(size_t size = 0):n(size){
            arr = nullptr;

            for (size_t i = 0; i < n; i++)
            {
                listItem<T>* moving = new listItem<T>();
                moving->next = arr;
                arr = moving;
            }
        }

        /// @brief Adds an item to the list
        /// @param item the item to add
        void add(const T& item){
            listItem<T>* last = new listItem<T>(item);
            if(arr == nullptr){
                arr = last;
            }else{
                listItem<T>* temp = arr;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = last;
            }
            n++;
        }

        /// @brief Removes the 'i'th element from the list if it exists
        /// @param i index
        void remove(size_t i){
            if(i>=n) throw std::out_of_range("Error: Index is out of range!");
        
            if(i == 0){
                listItem<T>* temp = arr->next; 
                delete arr;
                arr = temp;
            }
            else{
                listItem<T>* prev = find(i-1);
                listItem<T>* curr = prev->next;
                prev->next = curr->next;
                delete curr;
            }
            n--;
        }

        /// @brief Removes an item from the list if it's in there
        /// @param item 
        void remove(const T& item){
            if(arr == nullptr){throw std::logic_error("Error: Removing from an empty list!");}

            if(arr->item == item){
                listItem<T>* temp = arr->next;
                delete arr;
                arr = temp;
                n--;
                return;
            }

            listItem<T>* curr = arr;
            while(curr->next != nullptr && curr->next->item != item){
                curr = curr->next;
            }

            if(curr->next != nullptr){
                listItem<T>* temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                n--;
            }else{
                throw std::invalid_argument("Error: The item doesn't exist in the list!");
            }
        }

        /// @brief Removes and returns the first element of the list
        T pop(){
            if(arr == nullptr){
                throw std::logic_error("Error: Function 'pop' was called on an empty list!");
            }

            listItem<T>* temp = arr->next;
            T ret = arr->item;
            delete arr;
            arr = temp;
            n--;

            return ret;
        }

        /// @brief Searches for an item in the list
        /// @param item 
        /// @returns True if it exist in the list
        bool search(const T& item)const{
            listItem<T>* moving = arr;
            for (size_t i = 0; i < n; i++)
            {
                if(moving->item == item) return true;
                moving = moving->next;
            }
            return false;
        }

        /// @brief Finds an item in the list if it can be compared to the items in the list
        /// @tparam K 
        /// @param item 
        /// @returns A pointer to the element
        template <typename K>
        listItem<T>* find(const K& item)const{
            listItem<T>* ret = arr;
            while(ret != nullptr && ret->item != item){
                ret = ret->next;
            }
            return ret;
        }

        /// @brief Specifically made for bfsData lists\\\n
        /// @brief It finds a bfsData item with the junction's name 
        /// @param name the junction's name
        /// @returns A pointer to the element
        listItem<bfsData>* findDataByChar(char name)const;

        /// @brief Specifically made for junction lists\\\n
        /// @brief Finds a junction in the list by its name
        /// @param name The junction's name
        /// @returns A pointer to the element
        listItem<Junction>* findJunctionByChar(char name)const;

        /// @brief Returns true if the list is empty
        bool empty(){return arr == nullptr;}

        /// @brief Returns the number of items in the list 
        size_t size()const{return n;}

        /// @param i index
        /// @return A reference to the 'i'th element of the list
        listItem<T>& operator[](size_t i) { return *find(i);}

        /// @param i index
        /// @return A constant reference to the 'i'th element of the list
        const listItem<T>& operator[](size_t i ) const{ return *find(i); }

        /// @brief Returns a pointer to the first element of the list 
        listItem<T>* first()const{return arr;}

        /// @brief Copy constructor of the list
        /// @param l the other list to copy
        List(const List& l):n(l.n), arr(nullptr){

            listItem<T>* source = l.arr;
            listItem<T>* last = nullptr;

            while (source != nullptr) {
                listItem<T>* newItem = new listItem<T>(source->item);
                if (arr == nullptr) {
                    arr = newItem;
                } else {
                    last->next = newItem;
                }
                last = newItem;
                source = source->next;
            }
        }

        /// @brief Assigns the values of the other list to this object
        /// @param l the other list object
        /// @return A reference to this object
        List& operator=(const List& l){
            if(this != &l){
                listItem<T>* curr = arr;
                while(curr != nullptr){
                    listItem<T>* temp = curr->next;
                    delete curr;
                    curr = temp;
                }

                n = l.n;
                arr = nullptr;

                listItem<T>* source = l.arr;
                listItem<T>* last = nullptr;

                while (source != nullptr) {
                    listItem<T>* newItem = new listItem<T>(source->item);
                    if (arr == nullptr) {
                        arr = newItem;
                    } else {
                        last->next = newItem;
                    }
                    last = newItem;
                    source = source->next;
                }
            }
            return *this;
        }

        /// @param l the other list object
        /// @return True if the two lists match
        bool operator==(const List<T>& l)const{
            if(this == &l) return true;
            if(n != l.n) return false;

            listItem<T>* curr = arr;
            listItem<T>* lcurr = l.arr;
            while(curr != nullptr){
                if(curr->item != lcurr->item) return false;
                curr = curr->next;
                lcurr = lcurr->next;
            }

            return true;
        }

        /// @param l the other list object
        /// @return True if the two lists don't match
        bool operator!=(const List<T>& l)const{
            if(this == &l) return false;
            if(n != l.n) return true;

            listItem<T>* curr = arr;
            listItem<T>* lcurr = l.arr;
            while(curr != nullptr){
                if(curr->item == lcurr->item) return false;
                curr = curr->next;
                lcurr = lcurr->next;
            }

            return true;
        }

        /// @brief Reverses the list
        void reverse(){
            listItem<T>* curr = arr;
            listItem<T>* prev = nullptr;
            listItem<T>* next = nullptr;

            while(curr != nullptr){
                next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            arr = prev;
        }

        ~List(){
            while (arr != nullptr) {
                listItem<T>* next = arr->next;
                delete arr;
                arr = next;
            }
        }
};

/// @brief Writes the items to the given output stream followed by a space
/// @tparam T 
/// @param os output stream
/// @param l list
/// @return The output stream
template < typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l){
    listItem<T>* curr = l.first();
    while(curr != nullptr){
        os << curr->getItem() << " ";
        curr = curr->getNext();
    }

    return os;
}

#endif