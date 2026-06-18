#pragma once
#include <cmath>

#if defined(_MSC_VER)
#define __DUALFORCEINLINE __forceinline
#else
#define __DUALFORCEINLINE [[gnu::always_inline]]
#endif

template <typename Var>
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
        if (scalar == 0)
            return *this;
        return Dual(this->re / scalar, this->eps / scalar);
    }
    inline Dual operator+(const Var& scalar) const {
        return Dual(this->re + scalar, this->eps);
    }
    inline Dual operator-(const Var& scalar) const {
        return Dual(this->re - scalar, this->eps);
    }
    __DUALFORCEINLINE Dual operator~() const { //conjugate operator
        return Dual(re, -eps);
    }
    __DUALFORCEINLINE Dual conj() const {
        return Dual(re, -eps);
    }
    Dual operator/(const Dual& other) const {

        if (other.re == 0) // ##! error handling for zero division in dual
            return *this;

        return Dual(
            this->re / other.re,
            ((this->eps * other.re) - (this->re * other.eps)) / ((other.re * other.re))
            );
    }
    __DUALFORCEINLINE bool operator==(const Dual& other) const {
        return this->re == other.re && this->eps == other.eps;
    }
    __DUALFORCEINLINE bool operator!=(const Dual& other) const {
        return !(this->operator==(other));
    }
    __DUALFORCEINLINE Var ang() const { return static_cast<Var>(this->eps / this->re); }
    __DUALFORCEINLINE Var abs() const { return this->re; }

};


