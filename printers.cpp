#include "printers.h"

#include <cstdlib>
#include <ostream>

#include "msg.h"

std::ostream& operator<<(std::ostream& os, msg::cview msg) {
    os << "msg.header:\n" << msg.header() << "\n"
       << "msg.reserved: " << msg.reserved() << "\n"
       << "msg.value1: " << msg.value1() << "\n"
       << "msg.value2: "<< msg.value2() << "\n"
       << "msg.intvals[0]: " << msg.intvals(0) << "\n"
       << "msg.intvals[1]: "<< msg.intvals(1) << "\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, msg_hdr::cview msg_hdr) {
    os << "msg.magic: " << int(msg_hdr.magic()) << "\n"
       << "hdr.size: " << msg_hdr.size() << "\n"
       << "hdr.opcode: "<< msg_hdr.opcode() << "\n";
    return os;
}

void check_magic_val(msg_hdr::value& msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_cval(const msg_hdr::value& msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_view(msg_hdr::view msg_hdr) {
    msg_hdr.check_magic();
}

void check_magic_cview(msg_hdr::cview msg_hdr) {
    msg_hdr.check_magic();
}

bool validate_val(msg::value& msg) {
    return msg.valid();
}

bool validate_cval(const msg::value& msg) {
    return msg.valid();
}

bool validate_view(msg::view msg) {
    return msg.valid();
}

bool validate_cview(msg::cview msg) {
    return msg.valid();
}

bool swap_if_valid_val(msg::value& msg) {
    return msg.swap_if_valid();
}

bool swap_if_valid_view(msg::view msg) {
    return msg.swap_if_valid();
}
