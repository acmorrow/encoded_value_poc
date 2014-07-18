#include "msg.h"

#include <cstdlib>
#include <cstdio>

template<template<typename> class storage_type_t>
void msg_hdr_const_methods<storage_type_t>::check_magic() const {
    printf("checking magic\n");
    if (this->magic() != 42)
        abort();
}

template class msg_hdr_const_methods<array_storage_type>;
template class msg_hdr_const_methods<pointer_storage_type>;
template class msg_hdr_const_methods<const_pointer_storage_type>;
template class msg_hdr_methods<array_storage_type>;
template class msg_hdr_methods<pointer_storage_type>;
