#pragma once

template <class Var> 
struct Complex {
    Var re;
    Var im;
    Complex(Var real = 0, Var imaginary = 0) : re(real), im(imaginary) {};
    inline Complex operator+(const Complex& other) const {
        return Complex(this->re + other.re, this->im + other.im);
    }
    inline Complex operator-(const Complex& other) const {
        return Complex(this->re - other.re, this->im - other.im);
    }
    Complex operator*(const Complex& other) const {
        return Complex((this->re * other.re) - (this->im * other.im), (this->im * other.re) + (this->re * other.im));
    }
    inline Complex operator*(const Var& scalar) const {
        return Complex(this->re * scalar, this->im * scalar);
    }
    inline Complex operator/(const Var& scalar) const {
        return Complex(this->re / scalar, this->im / scalar);
    }
    inline Complex operator+(const Var& scalar) const {
        return Complex(this->re + scalar, this->im);
    }
    inline Complex operator-(const Var& scalar) const {
        return Complex(this->re - scalar, this->im);
    }
    Complex operator/(const Complex& other) const {
#ifndef MATHUSEINVERSEAPPROX
        return Complex( 
            ((this->re * other.re) + (this->im * other.im)) / ((other.re * other.re) + (other.im * other.im)), 
            ((this->im * other.re) - (this->re * other.im)) / ((other.re * other.re) + (other.im * other.im))
        );
#endif
    }
    __forceinline bool operator==(const Complex& other) const {
        return this->re == other.re && this->im == other.im;
    }
    __forceinline bool operator!=(const Complex& other) const {
        return !(this->operator==(other));
    }
    void operator=(const Complex& other) {
        this->re = other.re;
        this->im = other.im;
    }
    __forceinline Var tan() const { return const_cast<Var>(this->im / this->re); }
    __forceinline Var ang() const { return const_cast<Var>(atan2(this->im, this->re)); } //angle ##! improve performance with faster atan2
    __forceinline Var abs() const { return const_cast<Var>(sqrt(this->re * this->re + this->im * this->im)); }
    __forceinline Var abssqr() const { return (this->re * this->re + this->im * this->im); }
};


