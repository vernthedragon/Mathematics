#pragma once
#include <cmath>

#ifndef __VECTOR
#include <immintrin.h>

#define __VECTORFORCEAVX2
//#define __VECTORFORCEAVX512
//#define __VECTORFORCESEEORNEON
#define __VECTORSEGMENTATIONCHECKS
#define __VECTORDISABLEINLINEFOROPERANDS //disable inline because it makes large code when using SIMD

#if defined (__VECTORDISABLEINLINEFOROPERANDS)
#define __VECOPINLINE
#else
#define __VECOPINLINE inline
#endif

#if defined (__VECTORFORCEAVX2)
#define __VECTOR8FLOAT4DOUBLE
#elif (defined(__AVX512F__) || defined(__VECTORFORCEAVX512))
#define __VECTOR16FLOAT8DOUBLE
#elif defined(__AVX2__)
#define __VECTOR8FLOAT4DOUBLE
#elif (defined(__SSE4_2__) || defined(__VECTORFORCESEEORNEON))
#define __VECTOR4FLOAT2DOUBLE
#elif defined(__ARM_NEON)
#define __VECTOR4FLOAT2DOUBLE
#endif

#define __VECTORROUND_UP_32(x) (((x) + 31) & ~31)
#define __VECTORROUND_UP_8(x) (((x) + 7) & ~7)
#define __VECTORROUND_UP_4(x) (((x) + 3) & ~3)
#define __VECTORROUND_UP_2(x) (((x) + 1) & ~1)
#define __VECTOR
#endif

#if defined(_MSC_VER)
#define __VECTORFORCEINLINE __forceinline
#else
#define __VECTORFORCEINLINE [[gnu::always_inline]]
#endif




/*
int i = 0;

    // Process 8 floats at a time using AVX2
    for (; i <= N - 8; i += 8) {
        __m256 v1 = _mm256_loadu_ps(&this->comp[i]);
        __m256 v2 = _mm256_loadu_ps(&other.comp[i]);
        __m256 res = _mm256_add_ps(v1, v2);
        _mm256_storeu_ps(&ret.comp[i], res);
    }

    // Clean up any remaining elements if N is not a multiple of 8
    for (; i < N; i++) {
        ret.comp[i] = this->comp[i] + other.comp[i];
    }
*/

//typedef float Var;// for teseting
//constexpr size_t N = 3;

#ifndef __HELPERISSAME
template <typename T, typename U>
struct HelperIsSameType {
    static constexpr bool value = false;
};

template <typename T>
struct HelperIsSameType<T, T> {
    static constexpr bool value = true;
};

#define __HELPERISSAME
#endif


template <size_t N, typename Var = float>
struct Vector {

#if defined (__VECTOR16FLOAT8DOUBLE)
 
#elif defined (__VECTOR8FLOAT4DOUBLE)
    static constexpr unsigned long long Alignment = (HelperIsSameType<Var, float>::value || HelperIsSameType<Var, double>::value || HelperIsSameType<Var, int>::value) ? 32 : alignof(Var) ;

    alignas(Alignment) Var comp[N];
#elif defined (__VECTOR4FLOAT2DOUBLE)
 
#else
    Var comp[N];
#endif
   

    template <typename... Args>
    Vector(Args... args) { 
        static_assert((sizeof...(Args)) <= N, "Vector | Cannot initialize Vector with more elements than container size");

#if defined (__VECTOR16FLOAT8DOUBLE) //##! ADD EXTENDED VECTOR OPERATION OPTIMIZATION

#elif defined (__VECTOR8FLOAT4DOUBLE)
        
#elif defined (__VECTOR4FLOAT2DOUBLE)

#endif
        size_t n = 0;
        ((comp[n++] = static_cast<Var>(args)), ...);
        n = sizeof...(Args); 

#if defined (__VECTOR16FLOAT8DOUBLE) 

#elif defined (__VECTOR8FLOAT4DOUBLE)

        if (n >= N)
            return;

        if constexpr (HelperIsSameType<Var, float>::value) {
            size_t nearest8 = __VECTORROUND_UP_8(n);
            while (n < nearest8) { comp[n] = 0; n++; } //32 byte alignment, 8 floats

            __m256 zero_vec = _mm256_setzero_ps();
            while (n < N) {


                _mm256_storeu_ps(&comp[n], zero_vec);

                n += 8;

            }
            return;
        }
        else if constexpr (HelperIsSameType<Var, double>::value) {
            size_t nearest4 = __VECTORROUND_UP_4(n);
            while (n < nearest4) { comp[n] = 0; n++; } //32 byte alignment, 4 doubles

            __m256d zero_vec = _mm256_setzero_pd();
            while (n < N) {


                _mm256_storeu_pd(&comp[n], zero_vec);

                n += 4;

            }
            return;
        }
      
#elif defined (__VECTOR4FLOAT2DOUBLE)

#endif

        while (n < N) { comp[n] = 0; n++; } 

    }
    Vector(bool a, char d) {  /*no init to not waste any space*/ }
    Var& operator[](size_t index) {
        if (index >= N)
            return comp[0]; // ##! add error handling better here

        return comp[index];
    }
    __VECTORFORCEINLINE Var& operator()(size_t index) {
        return operator[](index);
    }
    __VECOPINLINE Vector operator+(const Vector& other) const {

#if defined (__VECTOR16FLOAT8DOUBLE)

#elif defined (__VECTOR8FLOAT4DOUBLE)
        if constexpr (HelperIsSameType<Var, float>::value) {
            __m256 Left, Right, Sum;
            Vector ret(true, 'a');
            for (size_t i = 0; i < N; i += 8) {
              
                Left = _mm256_load_ps(&comp[i]);
                Right = _mm256_load_ps(&other.comp[i]);
                Sum = _mm256_add_ps(Left, Right);
                _mm256_store_ps(&ret.comp[i], Sum);
            }
            return ret;
        }
        else if constexpr (HelperIsSameType<Var, double>::value) {
            __m256d Left, Right, Sum;
            Vector ret(true, 'a');
            for (size_t i = 0; i < N; i += 4) {

                Left = _mm256_load_pd(&comp[i]);
                Right = _mm256_load_pd(&other.comp[i]);
                Sum = _mm256_add_pd(Left, Right);
                _mm256_store_pd(&ret.comp[i], Sum);
            }
            return ret;
        }
       
#elif defined (__VECTOR4FLOAT2DOUBLE)

#endif

        Vector ret(true, 'a');
        for (int i = 0; i < N; i++) {
            ret.comp[i] = this->comp[i] + other.comp[i];
        }
        return ret;

    }

    __VECOPINLINE Vector operator-(const Vector& other) const {

#if defined (__VECTOR16FLOAT8DOUBLE)

#elif defined (__VECTOR8FLOAT4DOUBLE)
        if constexpr (HelperIsSameType<Var, float>::value) {
            __m256 Left, Right, Sum;
            Vector ret(true, 'a');
            for (size_t i = 0; i < N; i += 8) {

                Left = _mm256_load_ps(&comp[i]);
                Right = _mm256_load_ps(&other.comp[i]);
                Sum = _mm256_sub_ps(Left, Right);
                _mm256_store_ps(&ret.comp[i], Sum);
            }
            return ret;
        }
        else if constexpr (HelperIsSameType<Var, double>::value) {
            __m256d Left, Right, Sum;
            Vector ret(true, 'a');
            for (size_t i = 0; i < N; i += 4) {

                Left = _mm256_load_pd(&comp[i]);
                Right = _mm256_load_pd(&other.comp[i]);
                Sum = _mm256_sub_pd(Left, Right);
                _mm256_store_pd(&ret.comp[i], Sum);
            }
            return ret;
        }
       
#elif defined (__VECTOR4FLOAT2DOUBLE)

#endif

        Vector ret(true, 'a');
        for (int i = 0; i < N; i++) {
            ret.comp[i] = this->comp[i] - other.comp[i];
        }
        return ret;

    }

};
