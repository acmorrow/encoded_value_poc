#include <iosfwd>

namespace msg_hdr {
    class value;
    class view;
    class cview;
}

namespace msg {
    class value;
    class view;
    class cview;
}

std::ostream& operator<<(std::ostream& os, msg::cview msg);
std::ostream& operator<<(std::ostream& os, msg_hdr::cview msg_hdr);

void check_magic_val(msg_hdr::value& msg_hdr);
void check_magic_cval(const msg_hdr::value& msg_hdr);
void check_magic_view(msg_hdr::view msg_hdr);
void check_magic_cview(msg_hdr::cview msg_hdr);

bool validate_val(msg::value& msg);
bool validate_cval(const msg::value& msg);
bool validate_view(msg::view msg);
bool validate_cview(msg::cview msg);

bool swap_if_valid_val(msg::value& msg);
bool swap_if_valid_view(msg::view msg);
