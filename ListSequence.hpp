#pragma once

#include "Sequence.h"
#include "LinkedList.hpp"

template<class T>
class ListSequence: public Sequence<T>
{
private:
    LinkedList<T>* m_List;

public:
    ListSequence();
    explicit ListSequence(int count);
    ListSequence(T* items, int count);
    explicit ListSequence(const LinkedList<T>& other);
    ListSequence(const ListSequence<T>& other);
    explicit ListSequence(const Sequence<T>&  other);
    ~ListSequence();

public:
    const T& get(int index) const;
    T getFirst() const;
    T getLast() const;
    int getLength() const;
    int find(const T& item) const;
    void clear();

public:
    T& operator[](int index);
    ListSequence<T>& operator =(const Sequence<T>& other);
    bool operator ==(const Sequence<T>& other) const;

public:
    void set(T item, int index);
    Sequence<T>* getSubSequence(int startIndex, int endIndex) const;
    void insertAt(T item, int index);
    void append(T item);
    void prepend(T item);
    Sequence<T>* concat(Sequence<T>* other) const;
    void print() const;

};

template <class T>
ListSequence<T>::ListSequence()
{
    m_List = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(int count)
{
    m_List = new LinkedList<T>(count);
}

template <class T>
ListSequence<T>::ListSequence(T* items, int count)
{
    m_List = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& other)
{
    m_List = new LinkedList<T>(other);
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other)
{
    m_List = new LinkedList<T>(*other.m_List);
}

template <class T>
ListSequence<T>::ListSequence(const Sequence<T>& other)
{
    m_List = new LinkedList<T>;
    for (int i = 0; i < other.getLength(); i++)
        m_List->append(other.get(i));
}

template <class T>
ListSequence<T>::~ListSequence()
{
    delete m_List;
}

template <class T>
const T& ListSequence<T>::get(int index) const
{
    return m_List->get(index);
}

template <class T>
T ListSequence<T>::getFirst() const
{
    return m_List->getFirst();
}

template <class T>
T ListSequence<T>::getLast() const
{
    return m_List->getLast();
}

template <class T>
int ListSequence<T>::getLength() const
{
    return m_List->getSize();
}

template <class T>
int ListSequence<T>::find(const T& item) const
{
    return m_List->find(item);
}

template <class T>
void ListSequence<T>::clear()
{
    delete this;
}

template <class T>
T& ListSequence<T>::operator[](int index)
{
    return (*m_List)[index];
}

template <class T>
ListSequence<T>& ListSequence<T>::operator =(const Sequence<T>& other)
{
    if (this != &other)
    {
        delete m_List;

        m_List = new LinkedList<T>;
        for (int i = 0; i < other.getLength(); i++)
            m_List->append(other.get(i));
    }
    return *this;
}

template <class T>
bool ListSequence<T>::operator ==(const Sequence<T>& other) const
{
    if (m_List->getSize() == other.getLength())
    {
        bool flag = true;
        for (int i = 0; i < m_List->getSize(); i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}

template <class T>
void ListSequence<T>::set(T item, int index)
{
    (*m_List)[index] = item;
}

template <class T>
Sequence<T>* ListSequence<T>::getSubSequence(int startIndex, int endIndex) const
{
    auto* res = new ListSequence<T>(*m_List->getSubList(startIndex, endIndex));
    return res;
}

template <class T>
void ListSequence<T>::insertAt(T item, int index)
{
    m_List->insertAt(item, index);
}

template <class T>
void ListSequence<T>::append(T item)
{
    m_List->append(item);
}

template <class T>
void ListSequence<T>::prepend(T item)
{
    m_List->prepend(item);
}

template <class T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>* other) const
{
    if (other == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    auto* resultList = new ListSequence<T>;
    *(resultList->m_List) = *(m_List);

    for (int i = 0; i < other->getLength(); i++)
        resultList->append((*other)[i]);

    return resultList;
}

template <class T>
void ListSequence<T>::print() const
{
    m_List->print();
}
