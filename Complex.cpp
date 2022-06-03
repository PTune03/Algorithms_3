#include "Complex.hpp"

Complex::Complex()
{
    Real = 0;
    Imaginary = 0;
}

Complex::Complex(const double &real, const double &imaginary)
{
    Real = real;
    Imaginary = imaginary;
}

void Complex::setReal(const double &real)
{
    Real = real;
}

void Complex::setImaginary(const double &imaginary)
{
    Imaginary = imaginary;
}

const double& Complex::getReal()
{
    return Real;
}

const double& Complex::getImaginary()
{
    return Imaginary;
}

Complex Complex::operator*(const Complex &other) const
{
    return {Real * other.Real - Imaginary * other.Imaginary,
            Real * other.Imaginary + Imaginary * other.Real};
}

Complex Complex::operator+(const Complex &other) const
{
    return {Real + other.Real,
            Imaginary + other.Imaginary};
}

Complex Complex::operator-(const Complex &other) const
{
    return {Real - other.Real,
            Imaginary - other.Imaginary};
}

bool Complex::operator!=(const Complex &other) const
{
    return(!(Real == other.Real && Imaginary == other.Imaginary));
}

bool Complex::operator==(const Complex &other) const
{
    return (Real == other.Real, Imaginary == other.Imaginary);
}














