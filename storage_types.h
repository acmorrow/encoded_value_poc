#pragma once

#include <cstddef>
#include <cstring>

template<typename T>
struct storage_type_ops {


    template<typename U>
    U read(std::size_t offset) const {
        U u;
        std::memcpy(&u, static_cast<const T&>(*this).view(offset), sizeof(u));
        return u;
    }

    template<typename U>
    void write(std::size_t offset, const U& value) {
        std::memcpy(static_cast<T&>(*this).view(offset), &value, sizeof(value));
    }

};

template<typename T>
struct pointer_storage_type : storage_type_ops< pointer_storage_type<T> > {
    char* bytes;

    pointer_storage_type() {
    }

    pointer_storage_type(char* bytes)
        : bytes(bytes) {}

    char* view(std::size_t offset = 0) {
        return bytes + offset;
    }

    const char* view(std::size_t offset = 0) const {
        return bytes + offset;
    }
};

template<typename T>
struct const_pointer_storage_type : storage_type_ops< const_pointer_storage_type<T> > {
    const char* bytes;

    const_pointer_storage_type() {
    }

    const_pointer_storage_type(const char* bytes)
        : bytes(bytes) {}

    const char* view(std::size_t offset = 0) const {
        return bytes + offset;
    }
};

struct zero_init_tag_t {};
const zero_init_tag_t zero_init_tag;
