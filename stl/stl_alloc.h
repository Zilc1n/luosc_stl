#pragma once

#include "stl_config.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

__STL_BEGIN_NAMESPACE

template <int __inst>
class malloc_alloc_template {
public:
    static void *allocate(size_t __n) {
        void *result = malloc(__n);
        if (result == 0) {
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
        return result;
    }

    static void deallocate(void *__p, size_t /* size */) {
        free(__p);
    }

    static void *reallocate(void *__p, size_t /* old_size */, size_t __new_sz) {
        void *result = realloc(__p, __new_sz);
        if (result == 0) {
            fprintf(stderr, "out of memory\n");
            exit(1);
        }
        return result;
    }
};

typedef malloc_alloc_template<0> malloc_alloc;

template <class _Tp, class _Alloc>
class simple_alloc {
public:
    static _Tp *allocate(size_t __n) {
        return __n == 0 ? 0 : (_Tp *)_Alloc::allocate(__n * sizeof(_Tp));
    }

    static _Tp *allocate() {
        return (_Tp *)_Alloc::allocate(sizeof(_Tp));
    }

    static void deallocate(_Tp* __p, size_t __n) {
        if (__n != 0) _Alloc::deallocate(__p, __n * sizeof(_Tp));
    }

    static void deallocate(_Tp* __p) {
        _Alloc::deallocate(__p, sizeof(_Tp));
    }
};

typedef malloc_alloc alloc;

__STL_END_NAMESPACE