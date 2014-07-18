#pragma once

#include "msg_hdr.h"

// GENERATED
#pragma pack(push, 1)
struct msg_layout_t {
    char magic;
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

    char magic() const {
        return _storage.template read<uint32_t>(offsetof(layout_type, magic));
    }

    void magic(char value) {
        return _storage.write(offsetof(layout_type, magic), value);
    }

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
    bool mutable_valid();
};

// MACRO GENERATED
class msg_cview : public msg_const_methods<const_pointer_storage_type> {
public:
    msg_cview(const char* base) {
        _storage.bytes = base;
    }
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
};

// MACRO GENERATED
class msg : public msg_methods<array_storage_type> {
public:
    msg_view view() {
        return reinterpret_cast<char*>(this);
    }

    operator msg_view() {
        return view();
    }

    msg_cview view() const {
        return reinterpret_cast<const char*>(this);
    }

    operator msg_cview() const {
        return view();
    }

};

