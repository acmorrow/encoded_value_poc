#include <iosfwd>

class msg_cview;
class msg_hdr_cview;

std::ostream& operator<<(std::ostream& os, msg_cview msg);

std::ostream& operator<<(std::ostream& os, msg_hdr_cview msg_hdr);

void printf_if_valid(msg_cview msg);
