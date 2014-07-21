#include "msg.h"

#include <cstdlib>
#include <cstdio>

template <class T>
void msg_hdr::const_methods<T>::check_magic() const {
    printf("checking magic\n");
    if (this->magic() != 42)
        abort();
}

EV_INSTANTIATE(msg_hdr)
