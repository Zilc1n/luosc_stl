#pragma once

#include "stl_algobase.h"
#include "stl_config.h"
#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_iterator.h"
#include "stl_uninitialized.h"

__STL_BEGIN_NAMESPACE

template <class _Tp, class _Alloc>
class _Vector_base {
public:
    typedef _Alloc allocator_type;
    allocator_type get_allocator() const {
        return allocator_type();
    }

    _Vector_base(const _Alloc &) :
        _M_start(0), _M_finish(0), _M_end_of_storage(0) {
    }
    _Vector_base(size_t __n, const _Alloc &) :
        _M_start(0), _M_end_of_storage(0), _M_finish(0) {
        _M_start = _M_allocate(__n);
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + __n;
    }

    ~_Vector_base() {
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
    }

protected:
    _Tp *_M_start;
    _Tp *_M_finish;
    _Tp *_M_end_of_storage;

    typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;
    _Tp *_M_allocate(size_t __n) {
        return _M_data_allocator::allocate(__n);
    }
    void _M_deallocate(_Tp *__p, size_t __n) {
        _M_data_allocator::deallocate(__p, __n);
    }
};

template <class _Tp, class _Alloc>
class vector : protected _Vector_base<_Tp, _Alloc> {
private:
    typedef _Vector_base<_Tp, _Alloc> _Base;

public:
    typedef _Tp value_type;
    typedef value_type *pointer;
    typedef const value_type *constpointer;
    typedef value_type &reference;
    typedef const value_type &constreference;
    typedef value_type *iterator;
    typedef const value_type *const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef typename _Base::allocator_type allocator_type;
    allocator_type get_allocator() const {
        return allocator_type();
    }

    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

protected:
    using _Base::_M_allocate;
    using _Base::_M_deallocate;
    using _Base::_M_end_of_storage;
    using _Base::_M_finish;
    using _Base::_M_start;

protected:
    void _M_insert_aux(iterator __pos, const _Tp &__val);
    void _M_insert_aux(iterator __pos);

public:
    iterator begin() {
        return _M_start;
    }
    const_iterator begin() const {
        return _M_start;
    }
    iterator end() {
        return _M_finish;
    }
    const_iterator end() const {
        return _M_finish;
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return reverse_iterator(end());
    }

    size_type size() const {
        return size_type(end() - begin());
    }
    size_type max_size() const {
        return size_type(-1) / sizeof(_Tp);
    }
    size_type capacity() const {
        return size_type(_M_end_of_storage - begin());
    }
    bool empty() const {
        return begin() == end();
    }

    reference operator[](size_type __n) {
        return *(begin() + __n);
    }
    constreference operator[](size_type __n) const {
        return (begin() + __n);
    }

    explicit vector(const _Alloc &__a = allocator_type()) :
        _Base(__a) {
    }
    vector(size_type __n, const _Tp &__val,
           const allocator_type &__a = allocator_type()) :
        _Base(__n, __a) {
        _M_finish = uninitialized_fill_n(_M_start, __n, __val);
    }

    explicit vector(size_type __n) :
        _Base(__n, allocator_type()) {
        _M_finish = uninitialized_fill_n(_M_start, __n, _Tp());
    }
    vector(const vector<_Tp, _Alloc> &__x) :
        _Base(__x.size(), __x.get_allocator()) {
        _M_finish = uninitialized_copy(__x.begin(), __x.end(), _M_start);
    }
    vector(const _Tp *__first, const _Tp *__last, const allocator_type &__a = allocator_type()) :
        _Base(__last - __first, __a) {
        _M_finish = uninitialized(__first, __last, _M_start);
    }

    ~vector() {
        destroy(_M_start, _M_finish);
    }

    vector<_Tp, _Alloc> &operator=(const vector<_Tp, _Alloc> &__x);

    void reserve(size_type __n) {
        if (capacity() < __n) {
            const size_type old_size = size();
            iterator __tmp = _M_allocate_and_copy(__n, _M_start, _M_finish);
            destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = __tmp;
            _M_finish = __tmp + old_size;
            _M_end_of_storage = _M_start + __n;
        }
    }

    void assign(size_type __n, const _Tp &__val) {
        _M_fill_assign(__n, __val);
    }
    void _M_fill_assign(size_type __n, const _Tp &__val);
    reference front() {
        return *begin();
    }
    reference back() {
        return *(end() - 1);
    }
    constreference front() const {
        return *begin();
    }
    constreference back() const {
        return *(end() - 1);
    }

    void push_back(const _Tp &__val) {
        if (_M_finish != _M_end_of_storage) {
            construct(_M_finish, __val);
            ++_M_finish;
        } else {
            _M_insert_aux(end(), __val);
        }
    }
    void push_back() {
        if (_M_finish != _M_end_of_storage) {
            construct(_M_finish, _Tp());
            ++_M_finish;
        } else {
            _M_insert_aux(end());
        }
    }

    void swap(vector<_Tp, _Alloc> &__x) {
        __STL_NAME::swap(_M_start, __x._M_start);
        __STL_NAME::swap(_M_finish, __x._M_finish);
        __STL_NAME::swap(_M_end_of_storage, __x._M_end_of_storage);
    }
    iterator insert(iterator __pos, const _Tp &__val) {
        size_type __n = __pos - begin();
        if (_M_finish != _M_end_of_storage and __pos == end()) {
            construct(_M_finish, __val);
            ++_M_finish;
        } else {
            _M_insert_aux(__pos, __val);
        }
        return begin() + __n;
    }
    void insert(iterator __pos) {
        size_type __n = __pos - begin();
        if (_M_finish != _M_end_of_storage and __pos == end()) {
            construct(_M_finish, _Tp());
            ++_M_finish;
        } else {
            _M_insert_aux(__pos);
        }
        return begin() + __n;
    }

    void insert(iterator __pos, const_iterator __first, const_iterator __last);
    void insert(iterator __pos, size_type __n, const _Tp &__val) {
        _M_fill_insert(__pos, __n, __val);
    }
    void _M_fill_insert(iterator __pos, size_type __n, const _Tp &__x);

    void pop_back() {
        --_M_finish;
        destroy(_M_finish);
    }
    iterator erase(iterator __pos) {
        if (__pos + 1 != end())
            copy(__pos + 1, _M_finish, __pos);
        --_M_finish;
        destroy(_M_finish);
        return __pos;
    }
    iterator erase(iterator __first, iterator __last) {
        iterator __i = copy(__last, _M_finish, __first);
        destroy(__i, _M_finish);
        _M_finish = _M_finish - (__last - __first);
        return __first;
    }

    void resize(size_type __n) {
    }
    void resize(size_type __n, const _Tp &__val) {
    }

    void clear() {
        erase(begin(), end());
    }

protected:
    iterator _M_allocate_and_copy(size_type __n, const_iterator __first, const_iterator __last) {
        iterator __result = _M_allocate(__n);
        __STL_TRY {
            uninitialized(__first, __last, __result);
            return __result;
        }
        __STL_UNWIND(_M_deallocate(__result, __n));
    }
};

template <class _Tp, class _Alloc>
inline bool
operator==(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y) {
    return __x.size() == __y.size() and equal(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Alloc>
inline bool
operator<(const vector<_Tp, _Alloc> &__x, const vector<_Tp, _Alloc> &__y) {
    return lexicographical_compare(__x.begin(), __x.end(), __y.begin(), __y.end());
}

template <class _Tp, class _Alloc>
vector<_Tp, _Alloc> &vector<_Tp, _Alloc>::operator=(const vector<_Tp, _Alloc> &__x) {
    if (&__x != this) {
        const size_type __xlen = __x.size();
        if (__xlen > capacity()) {
            iterator __tmp = _M_allocate_and_copy(__xlen, __x.begin(), __x.end());
            destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = __tmp;
            _M_end_of_storage = __tmp + __xlen;
        } else if (size() >= __xlen) {
            iterator __i = copy(__x.begin(), __x.end(), _M_start);
            destroy(__i, _M_finish);
        } else {
            copy(__x.begin(), __x.begin() + size(), _M_start);
            uninitialized_copy(__x.begin() + size(), __x.end(), end());
        }
        _M_finish = _M_start + __xlen;
    }
    return *this;
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_assign(size_type __n, const _Tp &__val) {
    if (__n > capacity()) {
        vector<_Tp, _Alloc> __tmp = vector<_Tp, _Alloc>(__n, __val, get_allocator());
        swap(__tmp); // 自动销毁
    } else if (__n > size()) {
        fill(begin(), end(), __val);
        _M_finish = _uninitialized_fill_n(_M_finish, __n - size(), __val);
    } else {
        erase(fill_n(begin(), __n, __val), end());
    }
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aux(iterator __pos, const _Tp &__val) {
    if (_M_finish != _M_end_of_storage) {
        construct(_M_finish, __val);
        ++_M_finish;
        _Tp __val_copy = __val;
        copy_backward(__pos, _M_finish - 2, _M_finish - 1);
        *__pos = __val_copy;
    } else {
        const size_type __old_size = size();
        const size_type __len = __old_size != 0 ? __old_size * 2 : 1;
        iterator __new_start = _M_allocate(__len);
        iterator __new_finish = __new_start;
        __STL_TRY {
            __new_finish = uninitialized_copy(begin(), __pos, __new_start);
            construct(__new_finish, __val);
            ++__new_finish;
            __new_finish = uninitialized_copy(__new_finish, end(), __new_finish);
        }
        __STL_UNWIND(destroy(__new_start, __new_finish);
                     _M_deallocate(__new_start, __len));
        destroy(begin(), end());
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
        _M_start = __new_start;
        _M_finish = __new_finish;
        _M_end_of_storage = _M_start + __len;
    }
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aux(iterator __position) {
    if (_M_finish != _M_end_of_storage) {
        construct(_M_finish, *(_M_finish - 1));
        ++_M_finish;
        copy_backward(__position, _M_finish - 2, _M_finish - 1);
        *__position = _Tp();
    } else {
        const size_type __old_size = size();
        const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
        iterator __new_start = _M_allocate(__len);
        iterator __new_finish = __new_start;
        __STL_TRY {
            __new_finish = uninitialized_copy(_M_start, __position, __new_start);
            construct(__new_finish);
            ++__new_finish;
            __new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
        }
        __STL_UNWIND((destroy(__new_start, __new_finish),
                      _M_deallocate(__new_start, __len)));
        destroy(begin(), end());
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
        _M_start = __new_start;
        _M_finish = __new_finish;
        _M_end_of_storage = __new_start + __len;
    }
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_insert(iterator __pos, size_type __n,
                                         const _Tp &__x) {
    if (__x == 0) return;
    if ((size_type)_M_end_of_storage - _M_finish >= __n) {
        const size_type __elems_after = _M_finish - __pos;
        _Tp __val = __x;
        iterator __old_finish = _M_finish;
        if (__elems_after > __n) {
            uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
            _M_finish += __n;
            copy_backward(__pos, __old_finish - __n, __old_finish);
            fill(__pos, __pos + __n, __val);
        } else {
            uninitialized_fill_n(_M_finish, __n - __elems_after, __val);
            _M_finish += __n - __elems_after;
            uninitialized_copy(__pos, __old_finish, _M_finish);
            _M_finish += __elems_after;
            fill(__pos, __old_finish, __val);
        }
    } else {
        const size_type __old_size = size();
        const size_type __len = __old_size + __STL_NAME::max(__old_size, __n);
        iterator __new_start = _M_allocate(__len);
        iterator __new_finish = __new_start;
        __STL_TRY {
            __new_finish = uninitialized_copy(_M_start, __pos, __new_start);
            __new_finish = uninitialized_fill_n(__pos, __n, __x);
            __new_finish = uninitialized_copy(__pos, _M_finish, __new_finish);
        }
        __STL_UNWIND(destroy(__new_start, __new_finish);
                     _M_deallocate(__new_start, __len));
        destroy(_M_start, _M_finish);
        _M_deallocate(_M_start, _M_end_of_storage - _M_start);
        _M_start = __new_start;
        _M_finish = __new_finish;
        _M_end_of_storage = __new_start + __len;
    }
}

template <class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::insert(iterator __position,
                                 const_iterator __first,
                                 const_iterator __last) {
    if (__first != __last) {
        size_type __n = 0;
        distance(__first, __last, __n);
        if (size_type(_M_end_of_storage - _M_finish) >= __n) {
            const size_type __elems_after = _M_finish - __position;
            iterator __old_finish = _M_finish;
            if (__elems_after > __n) {
                uninitialized_copy(_M_finish - __n, _M_finish, _M_finish);
                _M_finish += __n;
                copy_backward(__position, __old_finish - __n, __old_finish);
                copy(__first, __last, __position);
            } else {
                uninitialized_copy(__first + __elems_after, __last, _M_finish);
                _M_finish += __n - __elems_after;
                uninitialized_copy(__position, __old_finish, _M_finish);
                _M_finish += __elems_after;
                copy(__first, __first + __elems_after, __position);
            }
        } else {
            const size_type __old_size = size();
            const size_type __len = __old_size + __STL_NAME::max(__old_size, __n);
            iterator __new_start = _M_allocate(__len);
            iterator __new_finish = __new_start;
            __STL_TRY {
                __new_finish = uninitialized_copy(_M_start, __position, __new_start);
                __new_finish = uninitialized_copy(__first, __last, __new_finish);
                __new_finish = uninitialized_copy(__position, _M_finish, __new_finish);
            }
            __STL_UNWIND((destroy(__new_start, __new_finish),
                          _M_deallocate(__new_start, __len)));
            destroy(_M_start, _M_finish);
            _M_deallocate(_M_start, _M_end_of_storage - _M_start);
            _M_start = __new_start;
            _M_finish = __new_finish;
            _M_end_of_storage = __new_start + __len;
        }
    }
}

__STL_END_NAMESPACE