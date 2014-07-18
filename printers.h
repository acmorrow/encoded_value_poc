#include <iosfwd>

class msg_hdr;
class msg_hdr_view;
class msg_hdr_cview;

class msg;
class msg_view;
class msg_cview;


std::ostream& operator<<(std::ostream& os, msg_cview msg);
std::ostream& operator<<(std::ostream& os, msg_hdr_cview msg_hdr);

void check_magic_val(msg_hdr& msg_hdr);
void check_magic_cval(const msg_hdr& msg_hdr);
void check_magic_view(msg_hdr_view msg_hdr);
void check_magic_cview(msg_hdr_cview msg_hdr);

bool validate_val(msg& msg);
bool validate_cval(const msg& msg);
bool validate_view(msg_view msg);
bool validate_cview(msg_cview msg);

bool swap_if_valid_val(msg& msg);
bool swap_if_valid_view(msg_view msg);
