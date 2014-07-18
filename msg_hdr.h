#pragma once

#include <stdint.h>

#include "storage_types.h"

#pragma pack(push, 1)
struct msg_hdr_layout_t {
    uint8_t  magic;
    uint32_t size;
    uint16_t opcode;
};
#pragma pack(pop)

template<template<typename> class storage_type_t>
class msg_hdr_const_methods {
public:

    typedef msg_hdr_layout_t layout_type;
    typedef storage_type_t<layout_type> storage_type;

    char magic() const {
        return this->_storage.template read<uint32_t>(offsetof(layout_type, magic));
    }

    uint32_t size() const {
        return this->_storage.template read<uint32_t>(offsetof(layout_type, size));
    }

    uint16_t opcode() const {
        return this->_storage.template read<uint16_t>(offsetof(layout_type, opcode));
    }

    void check_magic() const;

protected:
    storage_type _storage;
};

template<template<typename> class storage_type_t>
class msg_hdr_methods : public msg_hdr_const_methods<storage_type_t> {
public:

    typedef msg_hdr_const_methods<storage_type_t> base;
    using typename base::layout_type;

    void magic(char value) {
        return this->_storage.write(offsetof(layout_type, magic), value);
    }

    void size(uint32_t value) {
        return this->_storage.write(offsetof(layout_type, size), value);
    }

    void opcode(uint16_t value) {
        return this->_storage.write(offsetof(layout_type, opcode), value);
    }

};

class msg_hdr_cview : public msg_hdr_const_methods<const_pointer_storage_type> {
public:
    msg_hdr_cview(const char* base) {
        _storage.bytes = base;
    }

private:
    // MAYBE
    msg_hdr_cview* operator&();
    msg_hdr_cview* operator&() const;
};

class msg_hdr_view : public msg_hdr_methods<pointer_storage_type> {
public:
    msg_hdr_view(char* base) {
        _storage.bytes = base;
    }

    operator msg_hdr_cview() {
        return msg_hdr_cview(_storage.bytes);
    }

private:
    // MAYBE
    msg_hdr_view* operator&();
    msg_hdr_view* operator&() const;
};

class msg_hdr : public msg_hdr_methods<array_storage_type> {
public:
    msg_hdr_view view() {
        // TODO: static_assert sizes
        return reinterpret_cast<char*>(this);
    }

    operator msg_hdr_view() {
        return view();
    }

    msg_hdr_cview view() const {
        // TODO: static_assert sizes
        return reinterpret_cast<const char*>(this);
    }

    operator msg_hdr_cview() const {
        return view();
    }
};
