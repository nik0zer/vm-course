#pragma once

#include "method.hh"

constexpr uint8_t OPCODE_SIZE = sizeof(Method::OpcodeType);
constexpr uint8_t REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType);
constexpr uint8_t IMM_1_REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType)
+ sizeof(Method::RegType);
constexpr uint8_t IMM_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType);
constexpr uint8_t REG_3_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 3U;
constexpr uint8_t REGIN_1_REGOUT_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 2U;
constexpr uint8_t REGIN_2_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 2U;


#define ALL_INSTR_LIST(_)                                                           \
    _(0, MV, IMM_1_REG_1)                                                           \
    _(1, STACC, REG_1)                                                              \
    _(2, LDACC, REG_1)                                                              \
    _(4, SUB, REG_3)                                                                \
    _(5, MUL, REG_3)                                                                \
    _(3, ADD, REG_3)                                                                \
    _(6, DIV, REG_3)                                                                \
    _(7, CMPEQ, REGIN_2)                                                            \
    _(8, CMPGT, REGIN_2)                                                            \
    _(9, CMPGE, REGIN_2)                                                            \
    _(10, JMP, IMM_1)                                                               \
    _(11, CJMPT, IMM_1)                                                             \
    _(12, CJMPF, IMM_1)                                                             \
    _(13, CALL, IMM_1)                                                              \
    _(14, RET, OPCODE)                                                              \
    _(15, CALLNAPI, IMM_1)