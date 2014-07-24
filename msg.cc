#include "msg.h"

#include <cassert>
#include <cmath>
#include <cstdio>

bool msg_cview::valid() const {
    const bool near =  std::fabs(value1() - value2()) < 1.0;
    const bool same_sign = ((value1() < 0.0) == (value2() < 0.0));
    return near && same_sign;
}

bool msg_view::swap_if_valid() {
    if (!valid())
        return false;

    const double tmp = value1();
    value1(value2());
    value2(tmp);

    return true;
}

