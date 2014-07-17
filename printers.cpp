#include "printers.h"

#include <ostream>

#include "msg.h"

std::ostream& operator<<(std::ostream& os, const msg_cview msg) {
    os << "msg.magic: " << int(msg.magic()) << "\n"
       << "msg.header: " << msg.header() << "\n"
       << "msg.value1: " << msg.value1() << "\n"
       << "msg.value2: "<< msg.value2() << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const msg_hdr_cview msg_hdr) {
    os << "hdr.size: " << msg_hdr.size() << "\n"
       << "hdr.opcode: "<< msg_hdr.opcode() << "\n";
    return os;
}

void printf_if_valid(const msg_cview msg) {
    if (msg.value1() != 0.0)
        abort();
}
