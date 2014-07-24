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

class msg_cview {

public:
    typedef msg_layout_t layout_type;
    typedef const_pointer_storage_type<layout_type> pointer_type;

    msg_cview(const char* data)
        : _data(data) {}

    const char* view2ptr() const {
        return data().bytes;
    }

    msg_hdr_cview header() const {
        return data().view(offsetof(layout_type, header));
    }

    double value1() const {
        return data().template read<double>(offsetof(layout_type, value1));
    }

    double value2() const {
        return data().template read<double>(offsetof(layout_type, value2));
    }

    bool valid() const;

protected:
    const pointer_type& data() const {
        return _data;
    }

private:
    const pointer_type _data;
};

class msg_view : public msg_cview {
public:

    using typename msg_cview::layout_type;
    typedef pointer_storage_type<layout_type> pointer_type;

    msg_view(char* data)
        : msg_cview(data) {}

    using msg_cview::view2ptr;
    char* view2ptr() {
        return data().bytes;
    }

    using msg_cview::header;
    msg_hdr_view header() {
        return data().view(offsetof(layout_type, header));
    }

    using msg_cview::value1;
    void value1(double value) {
        return data().write(offsetof(layout_type, value1), value);
    }

    using msg_cview::value2;
    void value2(double value) {
        return data().write(offsetof(layout_type, value2), value);
    }

    bool swap_if_valid();

private:
    pointer_type data() const {
        return const_cast<char*>(msg_cview::view2ptr());
    }
};

class msg {
public:
    typedef msg_cview::layout_type layout_type;

    msg() {
    }

    msg(zero_init_tag_t) {
        std::memset(&_data, 0, sizeof(_data));
    }

    operator msg_view() {
        return view();
    }

    operator msg_cview() const {
        return view();
    }

    msg_hdr_cview header() const {
        return view().header();
    }

    double value1() const {
        return view().value1();
    }

    double value2() const {
        return view().value2();
    }

    bool valid() const {
        return view().valid();
    }

    msg_hdr_view header() {
        return view().header();
    }

    void value1(double value) {
        return view().value1(value);
    }

    void value2(double value) {
        return view().value2(value);
    }

    bool swap_if_valid() {
        return view().swap_if_valid();
    }

private:
    msg_view view() {
        return _data;
    }

    msg_cview view() const {
        return _data;
    }

    char _data[sizeof(layout_type)];
};
