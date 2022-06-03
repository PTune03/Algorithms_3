#pragma once

#include "Matrix.hpp"


class MatrixTests
{
private:
    static void constuctorSizeTest();
    static void constructorAnotherMatrixTest();
    static void constructorAnotherMatrixValueTest();
    static void equalityTest();
    static void oneEqualAnotherTest();
    static void oneEqualAnotherValueTest();
    static void sumTest();
    static void multiplyOnScalarTest();
    static void multiplyOnMatrixTest();
    static void swapStringsTest();
    static void swapColumnsTest();
    static void transposeTest();

public:
    static void allTestsTogether();
};

void MatrixTests::constuctorSizeTest()
{
    Matrix<int> matrix(5);
    assert(matrix.getsize() == 5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            assert(matrix.get(i, j) == 0);
}

void MatrixTests::constructorAnotherMatrixTest()
{
    Matrix<int> matrix(4);
    Matrix<int> matrix2(4);
    matrix2 = matrix;
    assert(matrix == matrix2);
}

void MatrixTests::constructorAnotherMatrixValueTest()
{
    Matrix<int> matrix(4);
    Matrix<int> identicalmatrix(4);
    Matrix<int> matrix2 = std::move(matrix);
    assert(identicalmatrix == matrix2);
}

void MatrixTests::equalityTest()
{
    Matrix<int> matrix1(4);
    Matrix<int> matrix2(4);
    assert(matrix1 == matrix2);
    matrix1[1][1] = 4;
    assert(!(matrix1 == matrix2));
    matrix2[1][1] = 4;
    assert(matrix1 == matrix2);
}

void MatrixTests::oneEqualAnotherTest()
{
    Matrix<int> matrix1(4);
    Matrix<int> matrix2(4);
    matrix2 = matrix1;
    assert(matrix1 == matrix2);
}

void MatrixTests::oneEqualAnotherValueTest()
{
    Matrix<int> matrix1(4);
    Matrix<int> identical_matrix(4);
    identical_matrix = matrix1;
    Matrix<int> matrix2(5);
    matrix2 = std::move(matrix1);
    assert(identical_matrix == matrix2);
}

void MatrixTests::sumTest()
{
    Matrix<int> matrix1(4);
    Matrix<int> matrix2(4);
    matrix1[0][0] = 1;
    matrix2[1][1] = 2;
    Matrix<int> matrix3(4);
    matrix3[0][0] = 1;
    matrix3[1][1] = 2;
    assert(matrix1 + matrix2 == matrix3);
}

void MatrixTests::multiplyOnScalarTest()
{
    Matrix<int> matrix1(4);
    matrix1[1][1] = 4;

    Matrix<int> matrix2(4);
    matrix2[1][1] = 8;
    assert(matrix1 * 2 == matrix2);
    assert(2 * matrix1 == matrix2);
}

void MatrixTests::multiplyOnMatrixTest()
{
    Matrix<int> matrix(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            matrix[i][j] = 4;

    Matrix<int> res(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            res[i][j] = 48;

    matrix = matrix * matrix;
    assert(res == matrix);

}

void MatrixTests::swapStringsTest()
{
    Matrix<int> matrix(4);
    Matrix<int> res(4);

    for (int i = 0; i < 4; i++)
        matrix[2][i] = 3;
    for (int i = 0; i < 4; i++)
        res[1][i] = 3;

    matrix.swapStrings(1, 2);
    assert(res == matrix);
}

void MatrixTests::swapColumnsTest()
{
    Matrix<int> matrix(4);
    Matrix<int> res(4);

    for (int i = 0; i < 4; i++)
        matrix[i][1] = 5;

    for (int i = 0; i < 4; i++)
        res[i][2] = 5;

    matrix.swapColumns(1,2);
    assert(res == matrix);
}

void MatrixTests::transposeTest()
{
    Matrix<int> matrix(3);
    for (int i = 0; i < 3; i++)
        matrix[i][1] = i + 1;

    Matrix<int> res(3);
    for (int i = 0; i < 3; i++)
        res[1][i] = i + 1;

    matrix = matrix.transpose();

    assert(res == matrix);
}

void MatrixTests::allTestsTogether()
{
    constructorAnotherMatrixTest();
    constructorAnotherMatrixValueTest();
    constuctorSizeTest();
    equalityTest();
    oneEqualAnotherTest();
    oneEqualAnotherValueTest();
    sumTest();
    multiplyOnMatrixTest();
    multiplyOnScalarTest();
    swapColumnsTest();
    swapStringsTest();
    transposeTest();
}