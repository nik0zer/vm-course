#pragma once

#include "method.hh"

constexpr uint8_t SIZE_OPCODE = sizeof(Method::OpcodeType);
constexpr uint8_t SIZE_REG_1 = sizeof(Method::OpcodeType) + sizeof(Method::RegType);
constexpr uint8_t SIZE_IMM_1_REG_1 = sizeof(Method::OpcodeType) + sizeof(Method::ImmType)
+ sizeof(Method::RegType);
constexpr uint8_t SIZE_MARK = sizeof(Method::OpcodeType) + sizeof(Method::OffsetType);
constexpr uint8_t SIZE_CALL_MARK = sizeof(Method::OpcodeType) + sizeof(Method::ImmType);
constexpr uint8_t SIZE_CALL_NAPI = sizeof(Method::OpcodeType) + sizeof(Method::AddressType);
constexpr uint8_t SIZE_REG_3 = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 3U;
constexpr uint8_t SIZE_REGIN_1_REGOUT_1 = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 2U;
constexpr uint8_t SIZE_REGIN_2 = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 2U;


#define ALL_INSTR_LIST(_)                                                           \
    _(0, MV, IMM_1_REG_1)                                                           \
    _(1, STACC, REG_1)                                                              \
    _(2, LDACC, REG_1)                                                              \
    _(3, ADD, REG_3)                                                                \
    _(4, SUB, REG_3)                                                                \
    _(5, MUL, REG_3)                                                                \
    _(6, DIV, REG_3)                                                                \
    _(7, CMPEQ, REGIN_2)                                                            \
    _(8, CMPGT, REGIN_2)                                                            \
    _(9, CMPGE, REGIN_2)                                                            \
    _(10, JMP, MARK)                                                                \
    _(11, CJMPT, MARK)                                                              \
    _(12, CJMPF, MARK)                                                              \
    _(13, CALL, CALL_MARK)                                                          \
    _(14, RET, OPCODE)                                                              \
    _(15, CALLNAPI, CALL_NAPI)