#pragma once
#include "stl_config.h"
#include <new>

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
inline void _Destory(_Tp *__p) {
    __p->~_Tp();
}

template <class _ForwardIterator>
inline void _Destory(_ForwardIterator first, _ForwardIterator last) {
    
}

__STL_END_NAMESPACE