#pragma once
#include <cmath>

template <class Var>
struct Dual {
    Var re;
    Var eps;
    Dual(Var real = 0, Var epsilon = 0) : re(real), eps(epsilon) {};
    inline Dual operator+(const Dual& other) const {
        return Dual(this->re + other.re, this->eps + other.eps);
    }
    inline Dual operator-(const Dual& other) const {
        return Dual(this->re - other.re, this->eps - other.eps);
    }
    Dual operator*(const Dual& other) const {
        return Dual(this->re * other.re, (this->eps * other.re) + (this->re * other.eps));
    }
    inline Dual operator*(const Var& scalar) const {
        return Dual(this->re * scalar, this->eps * scalar);
    }
    inline Dual operator/(const Var& scalar) const {
        return Dual(this->re / scalar, this->eps / scalar);
    }
    inline Dual operator+(const Var& scalar) const {
        return Dual(this->re + scalar, this->eps);
    }
    inline Dual operator-(const Var& scalar) const {
        return Dual(this->re - scalar, this->eps);
    }
    Dual operator/(const Dual& other) const {

        if (other.re == 0) // ##! error handling for zero division in dual
            return other;

        return Dual(
            this->re / other.re,
            ((this->eps * other.re) - (this->re * other.eps)) / ((other.re * other.re))
            );

    }
    __forceinline bool operator==(const Dual& other) const {
        return this->re == other.re && this->eps == other.eps;
    }
    __forceinline bool operator!=(const Dual& other) const {
        return !(this->operator==(other));
    }
    void operator=(const Dual& other) {
        this->re = other.re;
        this->eps = other.eps;
    }
    __forceinline Var ang() const { return const_cast<Var>(this->eps / this->re); }
    __forceinline Var abs() const { return this->re; }

};


