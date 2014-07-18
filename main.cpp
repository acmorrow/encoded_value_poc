#include <cstdlib>
#include <iostream>

#include "printers.h"
#include "msg.h"

int main(int argc, char* argv[]) {
    msg m;
    memset(&m, 0, sizeof(m));

    std::cout << "sizeof(msg_hdr_layout_t): " << sizeof(msg_hdr_layout_t) << "\n";
    std::cout << "sizeof(msg_hdr_cview): " << sizeof(msg_hdr_cview) << "\n";
    std::cout << "sizeof(msg_hdr_view): " << sizeof(msg_hdr_view) << "\n";
    std::cout << "sizeof(msg_hdr): " << sizeof(msg_hdr) << "\n";

    std::cout << "sizeof(msg_layout_t): " << sizeof(msg_layout_t) << "\n";
    std::cout << "sizeof(msg_cview): " << sizeof(msg_cview) << "\n";
    std::cout << "sizeof(msg_view): " << sizeof(msg_view) << "\n";
    std::cout << "sizeof(msg): " << sizeof(msg) << "\n";

    std::cout << " MESSAGE: " << m.view() << std::endl;

    m.magic(argc);
    msg_view(m).magic(argc);

    // printf_if_valid(m);

    msg_view(m).valid();
    msg_cview(m).valid();

    msg_view(m).mutable_valid();
    //msg_cview(m).mutable_valid(); // ERROR

    return EXIT_SUCCESS;
}

