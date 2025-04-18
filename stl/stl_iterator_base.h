#pragma once
#include "stl_config.h"
#include <cstddef>

__STL_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class _Tp, class _Distance>
struct input_iterator {
    typedef input_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct output_iterator {
    typedef output_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct forward_iterator {
    typedef forward_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct bidirectional_iterator {
    typedef bidirectional_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct random_access_iterator {
    typedef random_access_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
struct _input_iterator {
    typedef input_iterator_tag iterator_categoty;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp, class _Distance>
inline input_iterator_tag
iterator_category(const input_iterator<class Tp, class Distance>) {
    return input_iterator_tag();
}

template <class _Tp, class _Distance>
inline output_iterator_tag
iterator_category(const output_iterator<class Tp, class Distance>) {
    return output_iterator_tag();
}

template <class _Tp, class _Distance>
inline forward_iterator_tag
iterator_category(const forward_iterator<class Tp, class Distance>) {
    return forward_iterator_tag();
}

template <class _Tp, class _Distance>
inline bidirectional_iterator_tag
iterator_category(const bidirectional_iterator_tag) {
    return bidirectional_iterator_tag();
}

template <class _Tp, class _Distance>
inline random_access_iterator_tag
iterator_category(const random_access_iterator<class Tp, class Distance>) {
    return random_access_iterator_tag();
}

template <class _Tp>
inline random_access_iterator_tag 
iterator_category(const _Tp *) {
    return random_access_iterator_tag();
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const input_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const forward_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Tp *value_type(const bidirectional_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

// output_iterator迭代器只写，无法获取类型
template <class _Tp, class _Distance>
inline _Tp *value_type(const random_access_iterator<_Tp, _Distance> &) {
    return (_Tp *)(0);
}

template <class _Tp>
inline _Tp *value_type(const _Tp *) {
    return (_Tp *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *distance_type(const input_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *distance_type(const forward_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *
distance_type(const bidirectional_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp, class _Distance>
inline _Distance *
distance_type(const random_access_iterator<_Tp, _Distance> &) {
    return (_Distance *)(0);
}

template <class _Tp>
inline ptrdiff_t *distance_type(const _Tp *) {
    return (ptrdiff_t *)(0);
}

#define __ITERATOR_CATEGORY(__i) iterator_category(__i)
#define __DISTANCE_TYPE(__i) distance_type(__i)
#define __VALUE_TYPE(__i) value_type(__i)

template <class _InputIterator, class _Distance>
inline void __distance(_InputIterator __first, _InputIterator __last,
                       _Distance &__n, input_iterator_tag) {
    while (__first != __last) {
        ++__first;
        ++__n;
    }
}

template <class _RandomAccessIterator, class _Distance>
inline void __distance(_RandomAccessIterator __first, _RandomAccessIterator __last,
                       _Distance &__n, random_access_iterator_tag) {
    __n += __last - __first;
}

template <class _InputIter, class _Distance>
inline void diatance(_InputIter __first, _InputIter __last, _Distance &__n) {
    __distance(__first, __last, __n, __ITERATOR_CATEGORY(__first));
}

template <class _InputIter, class _Distance>
inline void __advance(_InputIter &__i, _Distance __n, input_iterator_tag) {
    while (__n--) ++__i;
}

template<class _BidirectionalIterator, class _Distance>
inline void __advance(_BidirectionalIterator &__i, _Distance __n, bidirectional_iterator_tag) {
    if (__n >= 0) {
        while (__n--) __i++;
    } else {
        while (__n++) __i--;
    }
}

template<class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator &__i, _Distance __n, random_access_iterator_tag) {
    __i += __n;
}

template<class _InputIterator, class _Distance>
inline void advance(_InputIterator &__i, _Distance __n) {
    __advance(__i, __n, __ITERATOR_CATEGORY(__i));
}

template <class _Iterator>
struct iterator_traits {
    typedef typename _Iterator::iterator_category iterator_category;
    typedef typename _Iterator::value_type value_type;
    typedef typename _Iterator::difference_type difference_type;
    typedef typename _Iterator::pointer pointer;
    typedef typename _Iterator::reference reference;
};

template <class _Tp>
struct iterator_traits<_Tp *> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp *pointer;
    typedef _Tp &reference;
};

template <class _Tp>
struct iterator_traits<const _Tp *> {
    typedef random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef const _Tp *pointer;
    typedef const _Tp &reference;
};

__STL_END_NAMESPACE