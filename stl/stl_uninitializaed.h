#pragma once

#include "stl_config.h"
#include "stl_type_traits.h"
#include "stl_algo.h"
#include <cstring>
#include "stl_construct.h"
#include "stl_iterator_base.h"

__STL_BEGIN_NAMESPACE

template <class _ForwardIter, class _InputIter>
inline _ForwardIter
__uninitialized_copy_aux(_InputIter __first, _InputIter __last, _ForwardIter __result, __true_type) {
    return copy(__first, __last, __result);
}

template <class _ForwardIter, class _InputIter>
inline _ForwardIter
__uninitialized_copy_aux(_InputIter __first, _InputIter __last, _ForwardIter __result, __false_type) {
    _ForwardIter __cur = __result;
    __STL_TRY {
        for (; __first != __last; ++__first, __cur) {
            _Construct(&*__cur, *__first);
        }
        return __cur;
    }
    __STL_UNWIND(_Destroy(__result, __cur));
}

template <class _ForwardIter, class _InputIter, class _Tp>
inline _ForwardIter
__uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, _Tp *) {
    typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
    return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter
uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result) {
    return __uninitialized_copy(__first, __last, __result, __VALUE_TYPE(__result));
}

inline char *uninitialized_copy(const char *__first, const char *__last,
                                char *__result) {
    memmove(__result, __first, __last - __first);
    return __result + (__last - __first);
}

inline wchar_t *
uninitialized_copy(const wchar_t *__first, const wchar_t *__last,
                   wchar_t *__result) {
    memmove(__result, __first, sizeof(wchar_t) * (__last - __first));
    return __result + (__last - __first);
}

template <class _ForwardIter, class _Tp>
inline void
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last,
                         const _Tp &__x, __true_type) {
    fill(__first, __last, __x);
}

template <class _ForwardIter, class _Tp>
inline void
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last,
                         const _Tp &__x, __false_type) {
    _ForwardIter __cur = __first;
    __STL_TRY {
        for (; __cur != __last; ++__cur) {
            _Construct(&*__cur, __x);
        }
    }
    __STL_UNWIND(_Destroy(__first, __cur));
}

// _Tp1是要fill的对象类型
template <class _ForwardIter, class _Tp, class _Tp1>
inline void
__uninitialized__fill(_ForwardIter __first, _ForwardIter __last, const _Tp &__x, _Tp1 *) {
    typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
    __uninitialized_fill_aux(__first, __last, __x, _Is_POD());
}

template <class _ForwardIter, class _Tp, class _Tp1>
inline void
uninitialized_fill(_ForwardIter __first, _ForwardIter __last, const _Tp &__x) {
    __uninitialized_fill(__first, __last, __x, __VALUE_TYPE(__first));
}

template <class _ForwardIter, class _Size, class _Tp>
inline void
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __count, const _Tp &__x, __true_type) {
    fill(__first, __count, __x);
}

template <class _ForwardIter, class _Size, class _Tp>
inline void
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __count, const _Tp &__x, __false_type) {
    _ForwardIter __cur = __first;
    __STL_TRY {
        for (; __count > 0; --__count, ++__cur) {
            _Construct(&*__cur, __x);
        }
    }
    __STL_UNWIND(_Destroy(__first, __cur));
}

template <class _ForwardIter, class _Size, class _Tp, class _Tp1>
inline void
__uninitialized_fill_n(_ForwardIter __first, _Size __count, const _Tp &__x, _Tp1 *) {
    typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
    __uninitialized_fill_n_aux(__first, __count, __x, _Is_POD());
}

template <class _ForwardIter, class _Size, class _Tp>
inline void
uninitialized_fill_n(_ForwardIter __first, _Size __count, const _Tp &__x) {
    __uninitialized_fill_n(__first, __count, __x, __VALUE_TYPE(__first));
}

__STL_END_NAMESPACE