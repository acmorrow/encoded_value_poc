#include <cstdlib>
#include <iostream>
#include <vector>

#include "printers.h"
#include "msg.h"

int main(int argc, char* argv[]) {

    msg_hdr hdr(zero_init_tag);
    hdr.magic(42);

    check_magic_val(hdr);
    check_magic_cval(hdr);
    check_magic_view(hdr);
    check_magic_cview(hdr);
    check_magic_cview(const_cast<const msg_hdr&>(hdr));

    msg m(zero_init_tag);
    m.header().magic(42);
    m.value1(1.0);
    m.value2(1.1);

    validate_val(m);
    validate_cval(m);
    validate_view(m);
    validate_cview(m);
    validate_cview(const_cast<const msg&>(m));

    swap_if_valid_val(m);
    swap_if_valid_view(m);

    return EXIT_SUCCESS;
}

