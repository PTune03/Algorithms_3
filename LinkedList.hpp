#pragma once

#include <iostream>
#include "Errors.h"

template<class T>
struct Node
{
    T value;
    Node* next;
    Node* prev;
};

template<typename T>
class LinkedList
{
private:
    Node<T>* list_head = nullptr;
    Node<T>* list_tail = nullptr;
    int list_size = 0;

public:
    LinkedList();
    explicit  LinkedList(int count);
    LinkedList(T* items, int count);
    LinkedList(const LinkedList& linkedList);
    ~LinkedList();

public:
    int getSize() const;
    const T& get(int index) const;
    const T& getFirst() const;
    const T& getLast() const;
    int find (T item) const;
    void append(const T& item);
    void prepend(const T& item);
    void insertAt(const T& item, int index);
    void print() const;
    LinkedList<T>* concat(LinkedList<T> *other);
    LinkedList<T>* getSubList(int startIndex, int endIndex);

public:
    T& operator[](int index);
    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;
    bool operator ==(const LinkedList& other) const;
};

template<class T>
LinkedList<T>::LinkedList() = default;

template<class T>
LinkedList<T>::LinkedList(int count)
{
    if (count < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    if (count > 0)
        list_head = new Node<T>;
    Node<T> *current = list_head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < count; i++)
    {
        current->value = T();
        current->prev = previous;
        if (i != count - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }
    if (current != nullptr)
    {
        list_tail = current;
        list_tail->next = nullptr;
    }
    list_size = count;

}

template<class T>
LinkedList<T>::LinkedList(T *items, int count)
{
    if (items == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    if (count < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    if (count > 0)
        list_head = new Node<T>;
    Node<T> *current = list_head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < count; i++)
    {
        current->value = items[i];
        current->prev = previous;

        if (i != count -1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }

    if (current != nullptr)
    {
        list_tail = current;
        list_tail->next = nullptr;
    }
    list_size = count;

}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &linkedList)
{
    if (linkedList.list_size > 0)
    {
        list_head = new Node<T>;
    }

    list_size = linkedList.list_size;

    Node<T> *current = list_head;
    Node<T> *previous = nullptr;

    for (int i = 0; i < list_size; i++)
    {
        current->value = linkedList.get(i);
        current->prev = previous;

        if (i != list_size - 1)
        {
            previous = current;
            current->next = new Node<T>;
            current = current->next;
        }
    }

    if (current != nullptr)
    {
        list_tail = current;
        list_tail->next = nullptr;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if (list_head != nullptr)
    {
        Node<T> *current = list_head;
        while (current->next != nullptr)
        {
            current = current->next;
            delete current->prev;
        }
        delete current;
    }
}

template<class T>
int LinkedList<T>::getSize() const
{
    return list_size;
}

template <class T>
const T& LinkedList<T>::get(int index) const
{
    if (list_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= list_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T> *current = list_head;

    for (int i = 0; i < index; i++)
        current = current->next;

    return current->value;
}

template<class T>
const T& LinkedList<T>::getFirst() const
{
    if (list_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    return list_head->value;
}

template<class T>
const T& LinkedList<T>::getLast() const
{
    if (list_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);
    return list_tail->value;
}

template<class T>
int LinkedList<T>::find(T item) const
{
    if (list_head != nullptr)
    {
        int index = 0;
        Node<T> *current = list_head;
        while (current->next != nullptr)
        {
            if (current->value == item)
                return index;

            current = current->next;
            index+=1;
        }

        if (current->value == item)
            return index;

    }

    return -1;
}

template<class T>
void LinkedList<T>::append(const T &item)
{
    if (list_size == 0)
    {
        list_head = new Node<T>;
        list_head->value = item;
        list_head->next = nullptr;
        list_head->prev = nullptr;
        list_tail = list_head;
    }
    else
    {
        list_tail->next = new Node<T>;
        list_tail->next->value = item;
        list_tail->next->prev = list_tail;
        list_tail->next->next = nullptr;
        list_tail = list_tail->next;
    }
    list_size += 1;
}

template<class T>
void LinkedList<T>::prepend(const T &item)
{
    if (list_size == 0)
    {
        list_head = new Node<T>;
        list_head->value = item;
        list_head->next = nullptr;
        list_head->prev = nullptr;
        list_tail = list_head;
    }
    else
    {
        list_head->prev = new Node<T>;
        list_head->prev->value = item;
        list_head->prev->next = list_head;
        list_head->prev->prev = nullptr;
        list_head = list_head->prev;
    }
    list_size += 1;
}

template <class T>
void LinkedList<T>::print() const
{
    Node<T> *current = list_head;
    for (int i = 0; i < list_size; i++)
    {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

template <class T>
void LinkedList<T>::insertAt(const T &item, int index)
{
    if (index < 0 || index > list_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    if (index == 0)
        this -> prepend(item);

    else if (index == list_size)
        this -> append(item);

    else
    {
        Node<T> *current = list_head;
        for (int i = 0; i < index; i++)
            current = current->next;
        auto *new_Node = new Node<T>;
        new_Node->next = current;
        new_Node->prev = current->prev;
        new_Node->value = item;
        new_Node->prev->next = new_Node;
        new_Node->next->prev = new_Node;
        list_size += 1;
    }

}

template <class T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T> *other)
{
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto *resultList = new LinkedList<T>;
    *resultList = *this;

    for (int i = 0; i<other->getSize(); i++)
        resultList->append((*other)[i]);

    return resultList;
}

template<class T>
LinkedList<T>* LinkedList<T>::getSubList(int startIndex, int endIndex)
{
    if (list_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);
    if (startIndex < 0 || endIndex >= list_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T> *current = list_head;
    int count = 0;
    T items[endIndex - startIndex + 1];
    for (int i = 0; i < startIndex; i++)
        current = current->next;

    for (int i = startIndex; i < endIndex + 1; i++)
    {
        count += 1;
        items[i - startIndex] = current->value;
        current = current->next;
    }

    auto *result = new LinkedList(items, count);
    return result;
}
template <class T>
T& LinkedList<T>::operator[](int index)
{
    if (list_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= list_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    Node<T>* current = list_head;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current->value;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
{
    if (this != &other){
        Node<T>* current = list_head;
        if (list_head != nullptr)
        {
            while (current->next != nullptr)
            {
                current = current->next;
                delete current->prev;
            }
            delete current;
        }

        list_head = nullptr; list_tail = nullptr; list_size = 0;
        if (other.list_size > 0)
        {
            list_size = other.list_size;
            list_head = new Node<T>;
        }

        current = list_head;
        Node<T> *previous = nullptr;

        for (int i = 0; i < list_size; i++)
        {
            current->value = other.get(i);
            current->prev = previous;
            if (i != list_size - 1)
            {
                previous = current;
                current->next = new Node<T>;
                current = current->next;
            }
        }
        if (current != nullptr)
        {
            list_tail = current;
            list_tail->next = nullptr;
        }

    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept
{
    Node<T> *current = list_head;
    if (list_head != nullptr)
    {
        while (current->next != nullptr)
        {
            current = current->next;
            delete current->prev;
        }
        delete current;
    }

    list_head = other.list_head;
    list_size = other.list_size;
    list_tail = other.list_tail;

    other.list_head = nullptr;
    other.list_tail = nullptr;
    other.list_size = 0;
    return *this;
}

template <class T>
bool LinkedList<T>::operator ==(const LinkedList& other) const
{
    if (list_size == other.list_size)
    {
        bool flag = true;
        for (int i = 0; i < list_size; i++)
            if (this->get(i) != other.get(i))
                flag = false;
        return flag;
    }

    return false;
}

