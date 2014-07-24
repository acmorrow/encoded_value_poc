#include "msg_hdr.h"

#include <cstdlib>
#include <cstdio>

void msg_hdr_cview::check_magic() const {
    if (magic() != 42)
        abort();
}
