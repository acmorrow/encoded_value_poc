#pragma once

#include <stdint.h>

#include "storage_types.h"

#pragma pack(push, 1)
struct msg_hdr_layout_t {
    uint32_t size;
    uint16_t opcode;
};
#pragma pack(pop)

template<template<typename> class storage_type_t>
class msg_hdr_methods {
    typedef msg_hdr_layout_t layout_type;
    typedef storage_type_t<layout_type> storage_type;

public:

    uint32_t size() const {
        return _storage.template read<uint32_t>(offsetof(layout_type, size));
    }

    void size(uint32_t value) {
        return _storage.write(offsetof(layout_type, size), value);
    }

    uint16_t opcode() const {
        return _storage.template read<uint16_t>(offsetof(layout_type, opcode));
    }

    void opcode(uint16_t value) {
        return _storage.write(offsetof(layout_type, opcode), value);
    }

protected:
    storage_type _storage;
};

class msg_hdr_cview : public msg_hdr_methods<const_pointer_storage_type> {
public:
    msg_hdr_cview(const char* base) {
        _storage.bytes = base;
    }
};

class msg_hdr_view : public msg_hdr_methods<pointer_storage_type> {
public:
    msg_hdr_view(char* base) {
        _storage.bytes = base;
    }

    operator msg_hdr_cview() {
        return msg_hdr_cview(_storage.bytes);
    }
};

class msg_hdr : public msg_hdr_methods<array_storage_type> {
public:
    msg_hdr() {
        size(0);
        opcode(0);
    }

    msg_hdr_view view() {
        return reinterpret_cast<char*>(this);
    }

    operator msg_hdr_view() {
        return view();
    }

    msg_hdr_cview view() const {
        return reinterpret_cast<const char*>(this);
    }

    operator msg_hdr_cview() const {
        return view();
    }
};
