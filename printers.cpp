#include "printers.h"

#include <cstdlib>
#include <ostream>

#include "msg.h"

std::ostream& operator<<(std::ostream& os, const msg_cview msg) {
    os << "msg.header: " << msg.header() << "\n"
       << "msg.value1: " << msg.value1() << "\n"
       << "msg.value2: "<< msg.value2() << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const msg_hdr_cview msg_hdr) {
    os << "msg.magic: " << int(msg_hdr.magic()) << "\n"
       << "hdr.size: " << msg_hdr.size() << "\n"
       << "hdr.opcode: "<< msg_hdr.opcode() << "\n";
    return os;
}

void check_magic_val(msg_hdr& msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_cval(const msg_hdr& msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_view(msg_hdr_view msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_cview(msg_hdr_cview msg_hdr) {
    msg_hdr.check_magic();
}

bool validate_val(msg& msg) {
    return msg.valid();
}

bool validate_cval(const msg& msg) {
    return msg.valid();
}

bool validate_view(msg_view msg) {
    return msg.valid();
}

bool validate_cview(msg_cview msg) {
    return msg.valid();
}

bool swap_if_valid_val(msg& msg) {
    return msg.swap_if_valid();
}

bool swap_if_valid_view(msg_view msg) {
    return msg.swap_if_valid();
}
