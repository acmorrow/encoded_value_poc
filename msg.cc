#include "msg.h"

template<template<typename> class storage_type_t>
bool msg_methods<storage_type_t>::valid() const {
    return magic() % 2 == 0;
}

template<template<typename> class storage_type_t>
bool msg_methods<storage_type_t>::mutable_valid() {
    return magic() % 2 == 0;
}

template class msg_methods<array_storage_type>;
template class msg_methods<pointer_storage_type>;

template bool msg_methods<const_pointer_storage_type>::valid() const;

