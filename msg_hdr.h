#pragma once

#include <stdint.h>

#include "storage_types.h"
#include "macros.h"

#pragma pack(1)
struct msg_hdr_layout_t {
    uint8_t  magic;
    uint32_t size;
    uint16_t opcode;
};
#pragma pack()

EV_DECL_CLASS_BEGIN(msg_hdr, msg_hdr_layout_t)

EV_DECL_CONST_VIEWS_AND_VALUES_BEGIN
public:
    EV_DECL_ACCESSOR(magic)
    EV_DECL_ACCESSOR(size)
    EV_DECL_ACCESSOR(opcode)

    void check_magic() const;
EV_DECL_CONST_VIEWS_AND_VALUES_END

EV_DECL_VIEWS_AND_VALUES_BEGIN
public:
    EV_DECL_MUTATOR(magic);
    EV_DECL_MUTATOR(size);
    EV_DECL_MUTATOR(opcode);
EV_DECL_VIEWS_AND_VALUES_END

EV_DECL_CLASS_END
