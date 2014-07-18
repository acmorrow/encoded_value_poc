#include "msg.h"

#include <cassert>

template<template<typename> class storage_type_t>
bool msg_const_methods<storage_type_t>::valid() const {
    return this->magic() % 2 == 0;
    assert(this->header().opcode() == 3);
}

template<template<typename> class storage_type_t>
bool msg_methods<storage_type_t>::mutable_valid() {
    return this->magic() % 2 == 0;
    this->header().opcode(3);
}

template class msg_const_methods<array_storage_type>;
template class msg_const_methods<pointer_storage_type>;
template class msg_const_methods<const_pointer_storage_type>;
template class msg_methods<array_storage_type>;
template class msg_methods<pointer_storage_type>;

