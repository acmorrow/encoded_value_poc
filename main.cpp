#include <cstdlib>
#include <iostream>

#include "printers.h"
#include "msg.h"

int main(int argc, char* argv[]) {
    msg m;

    std::cout << " MESSAGE: " << m.view() << std::endl;

    m.magic(argc);

    printf_if_valid(m);

    return EXIT_SUCCESS;
}

