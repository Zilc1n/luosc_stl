#pragma once
#include "stl_config.h"
#include <new>
#include "stl_type_traits.h"
#include "stl_iterator_base.h"

__STL_BEGIN_NAMESPACE

template <typename _T1, typename _T2>
inline void _Construct(_T1 *__p, _T2 __value) {
    new ((void *)__p) _T1(__value);
}

template <typename _T1, typename _T2>
inline void _Construct(_T1 *__p) {
    new ((void *)__p) _T1();
}

template <class _Tp>
void destroy_one(_Tp *, __true_type) {
}

template <class _Tp>
void destroy_one(_Tp *pointer, __false_type) {
    if (pointer != nullptr) {
        pointer->~Tp();
    }
}

template <class _Tp>
inline void _Destroy(_Tp *__pointer) {
    destroy_one(__pointer, typename __type_traits<_Tp>::has_trivial_destructor());
    //        __pointer->~Tp();
}

template <class _ForwardIterator>
inline void __destroy_aux(_ForwardIterator first, _ForwardIterator last, __true_type) {
}

template <class _ForwardIterator>
inline void __destroy_aux(_ForwardIterator first, _ForwardIterator last, __false_type) {
    for (; first != last; ++first) {
        _destroy(&*first);
    }
}

template <class _ForwardIterator, class _Tp>
inline void __destroy(_ForwardIterator first, _ForwardIterator last, _Tp *) {
    typedef typename __type_traits<_Tp>::has_trivial_destructor _flag;
    __destroy_aux(first, last, _flag());
}

template <class _ForwardIterator>
inline void _destroy(_ForwardIterator first, _ForwardIterator last) {
    __destroy(first, last, __VALUE_TYPE(first));
}

inline void _Destroy(char *, char *) {
}
inline void _Destroy(int *, int *) {
}
inline void _Destroy(long *, long *) {
}
inline void _Destroy(float *, float *) {
}
inline void _Destroy(double *, double *) {
}

template<class _T1, class _T2>
inline void _Construct(_T1* __point, const _T2 &__value) {
    _Construct(__point, __value);
}

template<class _T1>
inline void construct(_T1* __point) {
    _Construct(__point);
}

template<class _T1>
inline void destroy(_T1 *__point) {
    _Destroy(__point);
}

template<class _ForwardIterator, class _Tp>
inline void destroy(_ForwardIterator __first, _ForwardIterator __last) {
    __destroy(__first, __last);
}

__STL_END_NAMESPACE