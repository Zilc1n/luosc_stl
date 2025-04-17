#pragma once
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template <class _T1, class _T2>
struct pair {
    typedef _T1 first_type;
    typedef _T2 second_type;
    _T1 first;
    _T2 second;

    pair() :
        first(_T1()), second(_T2()) {
    }

    pair(const _T1 &__a, const _T2 &__b) :
        first(__a), second(__b) {
    }

    template <class _U1, class _U2>
    pair(const pair<_U1, _U2> &__p) :
        first(__p.first), second(__p.second) {
    }
};

template <class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return __a.first == __b.first and __a.second == __b.second;
}

template <class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return __a.first < __b.first or (__a.first == __b.first and __a.second < __b.second);
}

template <class _T1, class _T2>
inline bool operator<=(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return !(__b > __a);
}

template <class _T1, class _T2>
inline bool operator>(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return __a.first > __b.first or (__a.first == __b.first and __a.second > __b.second);
}

template <class _T1, class _T2>
inline bool operator!=(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return !(__a == __b);
}

template <class _T1, class _T2>
inline bool operator>=(const pair<_T1, _T2> &__a, const pair<_T1, _T2> &__b) {
    return !(__a < __b);
}

template <class _T1, class _T2>
inline pair<_T1, _T2> make_pair(const _T1 &__x, const _T2 &__y) {
    return pair<_T1, _T2>(__x, __y);
}

__STL_END_NAMESPACE