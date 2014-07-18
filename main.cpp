#include <cstdlib>
#include <iostream>
#include <vector>

#include "printers.h"
#include "msg.h"

int main(int argc, char* argv[]) {

    std::cout << "sizeof(msg_hdr_layout_t): " << sizeof(msg_hdr_layout_t) << "\n";
    std::cout << "sizeof(msg_hdr_cview): " << sizeof(msg_hdr_cview) << "\n";
    std::cout << "sizeof(msg_hdr_view): " << sizeof(msg_hdr_view) << "\n";
    std::cout << "sizeof(msg_hdr): " << sizeof(msg_hdr) << "\n";

    std::cout << "sizeof(msg_layout_t): " << sizeof(msg_layout_t) << "\n";
    std::cout << "sizeof(msg_cview): " << sizeof(msg_cview) << "\n";
    std::cout << "sizeof(msg_view): " << sizeof(msg_view) << "\n";
    std::cout << "sizeof(msg): " << sizeof(msg) << "\n";

    msg_hdr hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.magic(42);

    check_magic_val(hdr);
    check_magic_cval(hdr);
    check_magic_view(hdr);
    check_magic_cview(hdr);
    check_magic_view(hdr.view());
    check_magic_cview(hdr.view());
    check_magic_cview(const_cast<const msg_hdr&>(hdr).view());
    // ERROR: check_magic_view(const_cast<const msg_hdr&>(hdr).view());

    msg m;
    memset(&m, 0, sizeof(m));
    m.header().magic(42);
    m.value1(1.0);
    m.value2(1.1);

    validate_val(m);
    validate_cval(m);
    validate_view(m);
    validate_cview(m);
    validate_view(m.view());
    validate_cview(m.view());
    validate_cview(const_cast<const msg&>(m).view());
    // ERROR: validate_view(const_cast<const msg&>(m).view());

    swap_if_valid_val(m);
    swap_if_valid_view(m.view());
    swap_if_valid_view(m);

    // ERROR: const_cast<const msg&>(m).swap_if_valid();
    // ERROR: const_cast<const msg&>(m).view().swap_if_valid();

    std::vector<msg_view> views;
    views.push_back(m.view());

    std::vector<msg_cview> cviews;
    cviews.push_back(m.view());

    msg orig;
    std::memset(&orig, 0, sizeof(orig));
    // ERROR: std::memset(&orig.view(), 0, sizeof(orig.view()));

    return EXIT_SUCCESS;
}

