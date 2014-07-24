#pragma once

#include <stdint.h>

#include "storage_types.h"

// This is the 'layout type'. We never actually use one of these structures. It is just an
// 'atlas' that tells us the offsets at which particular fields are found in an otherwise
// structureless region of bytes.
#pragma pack(push, 1)
    struct msg_hdr_layout_t {
        uint8_t  magic;
        uint32_t size;
        uint16_t opcode;
    };
#pragma pack(pop)

// This is the constant view type. It gives us accessors and const methods over a region of
// memory which we are interpreting as having the same structure as a msg_hdr_layout_t.
class msg_hdr_cview {
public:

    typedef msg_hdr_layout_t layout_type;
    typedef const_pointer_view view_type;

    msg_hdr_cview(const char* data)
        : _data(data) {
    }

    const char* view2ptr() const {
        return data().view();
    }

    uint8_t magic() const {
        return data().read<uint8_t>(offsetof(layout_type, magic));
    }

    uint32_t size() const {
        return data().read<uint32_t>(offsetof(layout_type, size));
    }

    uint16_t opcode() const {
        return data().read<uint16_t>(offsetof(layout_type, opcode));
    }

    void check_magic() const;

protected:
    const view_type& data() const {
        return _data;
    }

private:
    const view_type _data;
};

// This is the mutable view type. It gives us field mutators and non-const methods over a
// region of memory which we are interpreting as having the same structure as a
// msg_hdr_layout_t. It doesn't have a pointer of its own, instead inheriting from the constant
// view, and safely casting away the constness of the constant view when necessary.
class msg_hdr_view : public msg_hdr_cview {
public:

    using msg_hdr_cview::layout_type;
    typedef pointer_view view_type;

    msg_hdr_view(char* data)
        : msg_hdr_cview(data) {
    }

    using msg_hdr_cview::view2ptr;
    char* view2ptr() {
        return data().view();
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
    view_type data() const {
        // It is safe to cast away const here since the pointer stored in our base class was
        // originally non-const by way of our constructor.
        return const_cast<char*>(msg_hdr_cview::view2ptr());
    }
};

// This is the (optional) value type. It owns, via the value_storage base class, a chunk of
// bytes sufficient to hold the fields specified by our layout type. It re-iterates the methods
// of the constant and non-constant views allowing us to invoke them like normal accessors,
// mutators, and methods. However, all of the methods simply delegate to the view types,
// instantiated over the underlying storage. This way, we only write the methods once. Writing
// the forwarding methods is optional. It is equally valid to require users to always invoke
// .view() and then call the intended method.
class msg_hdr : public value_storage<msg_hdr_layout_t, msg_hdr_cview, msg_hdr_view> {
public:

    msg_hdr() {
    }

    msg_hdr(zero_init_tag_t zit)
        : value_storage<msg_hdr_layout_t, msg_hdr_cview, msg_hdr_view>(zit) {
    }

    char magic() const {
        return cview().magic();
    }

    uint32_t size() const {
        return cview().magic();
    }

    uint16_t opcode() const {
        return cview().magic();
    }

    void check_magic() const {
        return cview().check_magic();
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
};
