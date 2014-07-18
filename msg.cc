#include "msg.h"

#include <cassert>
#include <cmath>
#include <cstdio>

// Can write out-of-line methods

EV_CONST_METHOD_IMPL(bool, msg)::valid() const {
    printf("checking valid\n");
    // Can call const from const
    return std::fabs(value1() - value2()) < 1.0;
}

EV_METHOD_IMPL(bool, msg)::swap_if_valid() {
    printf("swapping if valid\n");
    // Can call const from non-const
    if (this->valid())
        return false;

    const double tmp = value1();
    value1(value2());
    value2(tmp);

    return true;
}

EV_INSTANTIATE(msg)
