#pragma once

#include "Errors.h"
#include "ArraySequence.hpp"

template<class T>
class Matrix
{
private:
    Sequence<Sequence<T>* >* matr_Data;
    int matr_Size = 0;
    void deleteData();
public:
    Matrix();
    explicit Matrix(int n);
    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&&other) noexcept ;
    ~Matrix();
    Sequence<T>& operator [](int index);
    Matrix<T>& operator =(const Matrix<T> &other);
    Matrix<T>& operator =(Matrix<T> &&other) noexcept ;
    
    bool operator ==(const Matrix<T> &other) const;
    
    const T& get(int stringIndex, int columnIndex) const;
    void set(const T& value, int stringIndex, int columnIndex);
    int getsize() const;

    
    void swapStrings(int index1, int index2);
    void swapColumns(int index1, int index2);
    
    Matrix<T>&& transpose();
    
    void print() const;
};

template <class T>
Matrix<T>&& operator +(const Matrix<T> &matrix1, const Matrix<T> &matrix2);

template <class T>
Matrix<T>&& operator *(const Matrix<T> &matrix, int multiplier);

template <class T>
Matrix<T>&& operator *(int multiplier, const Matrix<T> &matrix);

template <class T>
Matrix<T>&& operator *(const Matrix<T> &matrix1, const Matrix<T> &matrix2);

template <class T>
void Matrix<T>::deleteData() 
{
    if (matr_Data != nullptr)
    {
        for (int i = 0; i < matr_Size; i++)
            delete matr_Data->get(i);
        delete matr_Data;
    }
}

template <class T>
Matrix<T>::Matrix()
{
    matr_Data = new ArraySequence<Sequence<T>*>;
}

template<class T>
Matrix<T>::Matrix(int n)
{
    matr_Data = new ArraySequence<Sequence<T>*>(n);
    
    for(int i = 0; i < n;i++)
        (*matr_Data)[i] = new ArraySequence<T>(n);
    
    matr_Size = n;
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &other) 
{
    matr_Size = other.getsize();
    matr_Data = new ArraySequence<Sequence<T>*>(matr_Size);
    for (int i = 0; i < matr_Size; i++)
        (*matr_Data)[i] = new ArraySequence<T>(*(*other.matr_Data)[i]);

}

template<class T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept
{
    matr_Size = other.getsize();
    matr_Data = other.matr_Data;

    other.matr_Data = nullptr;
    other.matr_Size = 0;
}

template<class T>
Matrix<T>::~Matrix()
{
    deleteData();
}

template<class T>
const T& Matrix<T>::get(int stringIndex, int columnIndex) const
{
    return matr_Data->get(stringIndex)->get(columnIndex);
}

template<class T>
void Matrix<T>::set(const T &value, int stringIndex, int columnIndex)
{
    (*(*matr_Data)[stringIndex])[columnIndex] = value;
}

template<class T>
int Matrix<T>::getsize() const
{
    return matr_Size;
}

template<class T>
Matrix<T> &&Matrix<T>::transpose()
{
    auto* res = new Matrix<T>(matr_Size);
    for (int i = 0; i < matr_Size; i++)
        for (int j = 0; j < matr_Size; j++)
            (*res)[j][i] = (*this)[i][j];

    return std::move(*res);
}

template<class T>
void Matrix<T>::print() const
{
    printf("\n");
    for (int i = 0; i < matr_Size; i++)
        (*matr_Data)[i]->print();
    printf("\n");
}

template<class T>
Sequence<T>& Matrix<T>::operator [](int index)
{
    return (*(*matr_Data)[index]);
}

template<class T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& other)
{
    if (this != &other)
    {
        if (this->getsize() != other.getsize())
        {
            deleteData();
            matr_Size = other.getsize();
            matr_Data = new ArraySequence<Sequence<T>*>(matr_Size);
            for(int i = 0; i < matr_Size; i++)
                (*matr_Data)[i] = new ArraySequence<T>(*(*other.matr_Data)[i]);
        }
        else
            for (int i = 0; i < matr_Size; i++)
                for (int j = 0; j < matr_Size; j++)
                    (*this)[i][j] = other.get(i, j);
    }
    return *this;
}

template<class T>
Matrix<T>& Matrix<T>::operator =(Matrix<T> &&other) noexcept
{
    if (this != &other)
    {
        deleteData();
        matr_Data = other.matr_Data;
        matr_Size = other.getsize();

        other.matr_Data = nullptr;
        other.matr_Size = 0;
    }

    return *this;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &other) const
{
    if (this->getsize() != other.getsize())
        return false;

    for (int i = 0; i < matr_Size; i++)
        for (int j = 0; j < matr_Size; j++)
            if (this->get(i, j) != other.get(i, j))
                return false;

    return true;
}

template<class T>
Matrix<T>&& operator +(const Matrix<T>& matrix1, const Matrix<T>& matrix2)
{
    if(matrix1.getsize() != matrix2.getsize())
        throw Errors(Errors::DIFFERENT_SIZE_ERROR);

    auto* sum_matrix = new Matrix<T>(matrix1.getsize());

    for (int i = 0; i < matrix1.getsize(); i++)
        for (int j = 0; j < matrix1.getsize(); j++)
            (*sum_matrix)[i][j] = matrix1.get(i, j) + matrix2.get(i, j);

    return std::move(*sum_matrix);
}

template<class T>
Matrix<T>&& operator *(const Matrix<T>&matrix, int multiplier)
{
    auto* mul_matrix = new Matrix<T>(matrix.getsize());

    for (int i = 0; i < matrix.getsize(); i++)
        for (int j = 0; j < matrix.getsize(); j++)
            (*mul_matrix)[i][j] = matrix.get(i, j) * multiplier;

    return std::move(*mul_matrix);
}

template<class T>
Matrix<T>&& operator *(int multiplier, const Matrix<T>&matrix)
{
    auto* mul_matrix = new Matrix<T>(matrix.getsize());

    for (int i = 0; i < matrix.getsize(); i++)
        for (int j = 0; j < matrix.getsize(); j++)
            (*mul_matrix)[i][j] = matrix.get(i, j) * multiplier;

    return std::move(*mul_matrix);

}

template<class T>
Matrix<T>&& operator *(const Matrix<T>&matrix1, const Matrix<T>&matrix2)
{
    if(matrix1.getsize() != matrix2.getsize())
        throw Errors(Errors::DIFFERENT_SIZE_ERROR);
    auto *mul_matrix = new Matrix<T>(matrix1.getsize());

    for (int i = 0; i < matrix1.getsize(); i++)
        for (int j = 0; j < matrix2.getsize(); j++)
            {
                T sum = T();
                for (int k = 0; k < matrix1.getsize(); k++)
                    sum += (matrix1.get(i, k) * matrix2.get(k, j));
                (*mul_matrix)[i][j] = std::move(sum);
            }
    return std::move(*mul_matrix);

}

template<class T>
void Matrix<T>::swapStrings(int index1, int index2)
{
    Sequence<T> *temporary;
    temporary = (*matr_Data)[index1];
    (*matr_Data)[index1] = (*matr_Data)[index2];
    (*matr_Data)[index2] = temporary;
}

template <class T>
void Matrix<T>::swapColumns(int index1, int index2)
{
    T temp;
    for (int i = 0; i < matr_Size; i++)
    {
        temp = (*(*matr_Data)[i])[index1];
        (*(*matr_Data)[i])[index1] = (*(*matr_Data)[i])[index2];
        (*(*matr_Data)[i])[index2] = std::move(temp);
    }
}