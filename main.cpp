#include <cstdlib>
#include <iostream>

#include "msg.h"

int main(int argc, char* argv[]) {
    msg m;

    m.magic(argc);

    if (m.valid())
        std::cout << int(m.magic()) << std::endl;
    else
        std::cout << "INVALID MAGIC VALUE" << std::endl;

    return EXIT_SUCCESS;
}

