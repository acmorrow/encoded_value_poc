#include "msg.h"

#include <cassert>
#include <cmath>
#include <cstdio>

template<template<typename> class storage_type_t>
bool msg_const_methods<storage_type_t>::valid() const {
    printf("checking valid\n");
    return std::fabs(this->value1() - this->value2()) < 1.0;
}

template<template<typename> class storage_type_t>
bool msg_methods<storage_type_t>::swap_if_valid() {
    printf("swapping if valid\n");
    if (!this->valid())
        return false;

    double tmp = this->value1();
    this->value1(this->value2());
    this->value2(tmp);

    return true;
}

template class msg_const_methods<array_storage_type>;
template class msg_const_methods<pointer_storage_type>;
template class msg_const_methods<const_pointer_storage_type>;
template class msg_methods<array_storage_type>;
template class msg_methods<pointer_storage_type>;

