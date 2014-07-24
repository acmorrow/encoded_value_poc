#pragma once

#include <cstddef>
#include <cstring>

class const_pointer_view {
public:
    const_pointer_view(const char* bytes)
        : bytes(bytes) {
    }

    const char* view(std::size_t offset = 0) const {
        return bytes + offset;
    }

    template<typename T>
    T read(std::size_t offset) const {
        T t;
        std::memcpy(&t, view(offset), sizeof(t));
        return t;
    }

private:
    const char* const bytes;
};

struct pointer_view : public const_pointer_view {

    pointer_view(char* bytes)
        : const_pointer_view(bytes) {
    }

    char* view(std::size_t offset = 0) {
        // It is safe to cast away const here since the pointer stored in our base class was
        // originally non-const by way of our constructor.
        return const_cast<char*>(const_pointer_view::view(offset));
    }

    template<typename T>
    void write(std::size_t offset, const T& value) {
        std::memcpy(view(offset), &value, sizeof(value));
    }
};

struct zero_init_tag_t {};
const zero_init_tag_t zero_init_tag;

template<typename layout_type, typename cview_type, typename view_type>
class value_storage {
public:

    value_storage() {
    }

    value_storage(zero_init_tag_t) {
        std::memset(_data, 0, sizeof(_data));
    }

    view_type view() {
        return _data;
    }

    cview_type cview() const {
        return _data;
    }

    operator view_type() {
        return view();
    }

    operator cview_type() const {
        return cview();
    }

private:
    char _data[sizeof(layout_type)];
};
