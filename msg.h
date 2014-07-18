#pragma once

#include "msg_hdr.h"

// GENERATED
#pragma pack(push, 1)
struct msg_layout_t {
    char reserved[4];
    msg_hdr_layout_t header;
    double value1;
    double value2;
};
#pragma pack(pop)

// GENERATED
template<template<typename> class storage_type_t>
class msg_field_access {

    typedef msg_layout_t layout_type;
    typedef storage_type_t<layout_type> storage_type;

public:

    msg_hdr_view header() {
        return _storage.view(offsetof(layout_type, header));
    }

    msg_hdr_cview header() const {
        return _storage.view(offsetof(layout_type, header));
    }

    double value1() const {
        return _storage.template read<double>(offsetof(layout_type, value1));
    }

    void value1(double value) {
        return _storage.write(offsetof(layout_type, value1), value);
    }

    double value2() const {
        return _storage.template read<double>(offsetof(layout_type, value2));
    }

    void value2(double value) {
        return _storage.write(offsetof(layout_type, value2), value);
    }

protected:
    storage_type _storage;
};

// USER
template<template<typename> class storage_type_t>
class msg_const_methods : public msg_field_access<storage_type_t> {
public:
    bool valid() const;
};

template<template<typename> class storage_type_t>
class msg_methods : public msg_const_methods<storage_type_t> {
public:
    bool swap_if_valid();
};

// MACRO GENERATED
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

// MACRO GENERATED
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

// MACRO GENERATED
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

