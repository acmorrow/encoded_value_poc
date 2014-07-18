#include "msg.h"

#include <cstdlib>
#include <cstdio>

EV_CONST_METHOD_IMPL(void, msg_hdr)::check_magic() const {
    printf("checking magic\n");
    if (this->magic() != 42)
        abort();
}

EV_INSTANTIATE(msg_hdr)
