#pragma once

#include "msg_hdr.h"

#pragma pack(1)
struct msg_layout_t {
    char reserved[4];
    msg_hdr_layout_t header;
    double value1;
    double value2;
    int intvals[2];
};
#pragma pack()

EV_DECL_CLASS_BEGIN(msg, msg_layout_t)

EV_DECL_CONST_VIEWS_AND_VALUES_BEGIN
public:
    EV_DECL_ARRAY_ACCESSOR(intvals)
    EV_DECL_RAW_ACCESSOR(reserved)
    EV_DECL_VIEW_ACCESSOR(header)
    EV_DECL_ACCESSOR(value1)
    EV_DECL_ACCESSOR(value2)

    bool valid() const;
EV_DECL_CONST_VIEWS_AND_VALUES_END

EV_DECL_VIEWS_AND_VALUES_BEGIN
public:
    EV_DECL_ARRAY_MUTATOR(intvals)
    EV_DECL_RAW_MUTATOR(reserved)
    EV_DECL_VIEW_MUTATOR(header)
    EV_DECL_MUTATOR(value1)
    EV_DECL_MUTATOR(value2)

    bool swap_if_valid();
EV_DECL_VIEWS_AND_VALUES_END

EV_DECL_CLASS_END
