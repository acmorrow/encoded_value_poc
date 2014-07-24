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

class msg_hdr_cview {
public:
    typedef msg_hdr_layout_t layout_type;
    typedef const_pointer_storage_type<layout_type> pointer_type;

    msg_hdr_cview(const char* data)
        : _data(data) {}

    const char* view2ptr() const {
        return data().bytes;
    }

    char magic() const {
        return data().template read<uint32_t>(offsetof(layout_type, magic));
    }

    uint32_t size() const {
        return data().template read<uint32_t>(offsetof(layout_type, size));
    }

    uint16_t opcode() const {
        return data().template read<uint16_t>(offsetof(layout_type, opcode));
    }

    void check_magic() const;

protected:
    const pointer_type& data() const {
        return _data;
    }

private:
    const pointer_type _data;
};

class msg_hdr_view : public msg_hdr_cview {
public:

    using msg_hdr_cview::layout_type;
    typedef pointer_storage_type<layout_type> pointer_type;

    msg_hdr_view(char* data)
        : msg_hdr_cview(data) {
    }

    using msg_hdr_cview::view2ptr;
    char* view2ptr() {
        return data().bytes;
    }

    using msg_hdr_cview::magic;
    void magic(char value) {
        return data().write(offsetof(layout_type, magic), value);
    }

    using msg_hdr_cview::size;
    void size(uint32_t value) {
        return data().write(offsetof(layout_type, size), value);
    }

    using msg_hdr_cview::opcode;
    void opcode(uint16_t value) {
        return data().write(offsetof(layout_type, opcode), value);
    }

private:
    pointer_type data() const {
        return const_cast<char*>(msg_hdr_cview::view2ptr());
    }
};

class msg_hdr {
public:
    typedef msg_hdr_cview::layout_type layout_type;

    msg_hdr() {
    }

    msg_hdr(zero_init_tag_t) {
        std::memset(_data, 0, sizeof(_data));
    }

    operator msg_hdr_view() {
        return view();
    }

    operator msg_hdr_cview() const {
        return view();
    }

    char magic() const {
        return view().magic();
    }

    uint32_t size() const {
        return view().magic();
    }

    uint16_t opcode() const {
        return view().magic();
    }

    void check_magic() const {
        return view().check_magic();
    }

    void magic(char value) {
        return view().magic(value);
    }

    void size(uint32_t value) {
        return view().size(value);
    }

    void opcode(uint16_t value) {
        return view().opcode(value);
    }

private:
    msg_hdr_view view() {
        return _data;
    }

    msg_hdr_cview view() const {
        return _data;
    }

    char _data[sizeof(layout_type)];
};
