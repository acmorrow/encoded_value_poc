#pragma once

#include "msg_hdr.h"

#pragma pack(push, 1)
struct msg_layout_t {
    char reserved[4];
    msg_hdr_layout_t header;
    double value1;
    double value2;
};
#pragma pack(pop)


/////// POSSIBLE MACROIZATION //////

/// msg.h

// EV_DECL_CONST_VIEWS_AND_VALUES(msg_layout_t, msg)
// public:
//
//   EV_DECL_VIEW_ACCESSOR(header);
//   EV_DECL_ACCESSOR(value1);
//   EV_DECL_ACCESSOR(value2);
//
//   bool valid() const;
//
// EV_DECL_CONST_VIEWS_AND_VALUES_END;

// EV_DECL_VIEWS_AND_VALUES(msg_layout_t, msg)
//
// public:
//
//   EV_DECL_VIEW_MUTATOR(header);
//   EV_DECL_MUTATOR(value1);
//   EV_DECL_MUTATOR(value2);
//
//   bool swap_if_valid();
//
// EV_DECL_VIEWS_AND_VALUES_END;
//
// EV_DECL_VIEW_AND_VALUE_TYPES(msg);

/// msg.cc

// EV_DECL_CONST_METHOD(bool, msg)::valid() const {
//   // ...
// }
//
// EV_DECL_METHOD(bool, msg)::swap_if_valid() {
//    // ...
// }
//
// EV_INSTANTIATE_VIEW_AND_VALUE_TYPES(msg);


template<template<typename> class storage_type_t>
class msg_const_methods {
public:

    typedef msg_layout_t layout_type;

    msg_hdr_cview header() const {
        return this->_storage.view(offsetof(layout_type, header));
    }

    double value1() const {
        return this->_storage.template read<double>(offsetof(layout_type, value1));
    }

    double value2() const {
        return this->_storage.template read<double>(offsetof(layout_type, value2));
    }

    bool valid() const;

protected:
    storage_type_t<layout_type> _storage;
};

template<template<typename> class storage_type_t>
class msg_methods : public msg_const_methods<storage_type_t> {
public:

    typedef msg_const_methods<storage_type_t> base;
    using typename base::layout_type;

    using base::header;
    msg_hdr_view header() {
        return this->_storage.view(offsetof(layout_type, header));
    }

    using base::value1;
    void value1(double value) {
        return this->_storage.write(offsetof(layout_type, value1), value);
    }

    using base::value2;
    void value2(double value) {
        return this->_storage.write(offsetof(layout_type, value2), value);
    }

    bool swap_if_valid();
};

class msg_cview : public msg_const_methods<const_pointer_storage_type> {
public:
    msg_cview(const char* base) {
        _storage.bytes = base;
    }
private:
    // MAYBE
    msg_cview* operator&();
    msg_cview* operator&() const;
};

class msg_view : public msg_methods<pointer_storage_type> {
public:
    msg_view(char* base) {
        _storage.bytes = base;
    }

    operator msg_cview() {
        return msg_cview(_storage.bytes);
    }

private:
    // MAYBE
    msg_view* operator&();
    msg_view* operator&() const;
};

class msg : public msg_methods<array_storage_type> {
public:
    msg_view view() {
        // TODO: static_assert sizes
        return reinterpret_cast<char*>(this);
    }

    operator msg_view() {
        return view();
    }

    msg_cview view() const {
        // TODO: static_assert sizes
        return reinterpret_cast<const char*>(this);
    }

    operator msg_cview() const {
        return view();
    }

};
