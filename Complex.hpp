#pragma once
#include <cmath>

#if defined(_MSC_VER)
#define __COMPLEXFORCEINLINE __forceinline
#else
#define __COMPLEXFORCEINLINE [[gnu::always_inline]]
#endif

template <typename Var>
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
        if (scalar == 0)
            return *this;
        return Complex(this->re / scalar, this->im / scalar);
    }
    inline Complex operator+(const Var& scalar) const {
        return Complex(this->re + scalar, this->im);
    }
    inline Complex operator-(const Var& scalar) const {
        return Complex(this->re - scalar, this->im);
    }
    Complex operator/(const Complex& other) const {

        if (other.re == 0 && other.im == 0)  // ##! error handling for zero division in complex
            return *this;

        return Complex( 
            ((this->re * other.re) + (this->im * other.im)) / ((other.re * other.re) + (other.im * other.im)), 
            ((this->im * other.re) - (this->re * other.im)) / ((other.re * other.re) + (other.im * other.im))
        );
    }
    __COMPLEXFORCEINLINE bool operator==(const Complex& other) const {
        return this->re == other.re && this->im == other.im;
    }
    __COMPLEXFORCEINLINE bool operator!=(const Complex& other) const {
        return !(this->operator==(other));
    }
    void operator=(const Complex& other) {
        this->re = other.re;
        this->im = other.im;
    }
    __COMPLEXFORCEINLINE Var slope() const { return static_cast<Var>(this->im / this->re); }
    __COMPLEXFORCEINLINE Var ang() const { return static_cast<Var>(atan2(this->im, this->re)); } //angle ##! improve performance with faster atan2
    __COMPLEXFORCEINLINE Var abs() const { return static_cast<Var>(sqrt(this->re * this->re + this->im * this->im)); }
    __COMPLEXFORCEINLINE Var abssqr() const { return (this->re * this->re + this->im * this->im); }
};


