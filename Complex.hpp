#pragma once

#include <iostream>
class Complex
{
private:
    double Real;
    double Imaginary;

public:
    Complex();
    Complex(const double &real, const double &imaginary);
    const double &getReal();
    const double &getImaginary();
    void setReal(const double &real);
    void setImaginary(const double  &imaginary);

    Complex operator *(const Complex &other) const;
    Complex operator +(const Complex &other) const;
    Complex operator -(const Complex &other) const;
    bool operator ==(const Complex &other) const;
    bool operator !=(const Complex &other) const;


};

