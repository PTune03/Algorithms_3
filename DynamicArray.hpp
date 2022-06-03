#pragma once

#include <iostream>
#include "Errors.h"

template <class T>
class DynamicArray{
private:
    T* arr_data = nullptr;
    int arr_size = 0;
    int arr_capacity = 0;

public:
    DynamicArray();
    explicit DynamicArray(int size);
    DynamicArray(T* items, int counter);
    DynamicArray(const DynamicArray<T>& dynamicArray);
    ~DynamicArray();

public:
    void print() const;
    const T& get(int index) const;
    int getSize() const;
    void set(int index, const T& value);
    void resize(int new_size);
    T* begin();
    T* end();

public:
    T& operator[](int index);
    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    DynamicArray<T>& operator=(DynamicArray<T>&& other) noexcept;
    bool operator ==(const DynamicArray<T>&);


};

template <class T>
DynamicArray<T>::DynamicArray() = default;

template <class T>
DynamicArray<T>::DynamicArray(int size)
{
    if (size < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);
    arr_size = size;
    arr_capacity = size;
    arr_data = new T[arr_size]();
}

template <class T>
DynamicArray<T>::DynamicArray(T* items, int counter)
{
    if (items == nullptr)
        throw Errors(Errors::NULL_POINTER_ERROR);

    if (counter < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    arr_size = counter;
    arr_capacity = arr_size;
    arr_data = new T[arr_size];

    for (int i = 0; i < counter; i++)
        arr_data[i] = items[i];
}

template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &dynamicArray)
{
    arr_size = dynamicArray.arr_size;
    arr_capacity = arr_size;
    arr_data = new T[arr_size];

    for (int i = 0; i < arr_size; i++)
        arr_data[i] = dynamicArray.arr_data[i];
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] arr_data;
}

template <class T>
void DynamicArray<T>::print() const
{
    if (arr_data != nullptr)
        for (int i = 0; i < arr_size; i++)
            std::cout << arr_data[i] << ' ';
    std::cout << '\n';
}

template <class T>
const T& DynamicArray<T>::get(int index) const
{
    if (arr_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= arr_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    return arr_data[index];
}

template <class T>
int DynamicArray<T>::getSize() const
{
    return arr_size;
}

template <class T>
void DynamicArray<T>::set(int index, const T &value)
{
    if (arr_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index <= arr_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    arr_data[index] = value;
}

template <class T>
void DynamicArray<T>::resize(int new_size)
{
    if (new_size < 0)
        throw Errors(Errors::NEGATIVE_SIZE_ERROR);

    while (arr_capacity < new_size)
        if (arr_capacity != 0)
            arr_capacity *= 2;
        else
            arr_capacity += 1;

    T* new_data = new T[arr_capacity]();

    for (int i = 0; i < std::min(new_size, arr_size); i++)
        new_data[i] = arr_data[i];

    delete[] arr_data;
    arr_data = new_data;
    arr_size = new_size;
}

template <class T>
T* DynamicArray<T>::begin()
{
    return arr_data;
}

template <class T>
T* DynamicArray<T>::end()
{
    return &arr_data[arr_size];
}

template <class T>
T& DynamicArray<T>::operator[](int index)
{
    if (arr_size == 0)
        throw Errors(Errors::ZERO_SIZE_ERROR);

    if (index < 0 || index >= arr_size)
        throw Errors(Errors::INDEX_OUT_OF_RANGE_ERROR);

    return arr_data[index];
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &other)
{
    if (this != &other)
    {
        delete[] arr_data;
        arr_size = other.arr_size;
        arr_capacity = arr_size;
        arr_data = new T[arr_size];

        for (int i = 0; i < arr_size; i++)
            arr_data[i] = other.arr_data[i];
    }

    return *this;
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept
{
    delete[] arr_data;
    arr_size = other.arr_size;
    arr_capacity = arr_size;
    arr_data = other.arr_data;

    other.arr_data = nullptr;
    return *this;
}

template <class T>
bool DynamicArray<T>::operator ==(const DynamicArray<T>& other)
{
    if (arr_size == other.getSize())
    {
        bool flag = true;
        for (int i = 0; i < arr_size; i++)
            if (this->get(i) != other.get(i))
                flag = false;

        return flag;
    }

    return false;
}
