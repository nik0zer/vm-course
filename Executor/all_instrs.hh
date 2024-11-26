#pragma once

#include "method.hh"

constexpr uint8_t OPCODE_SIZE = sizeof(Method::OpcodeType);
constexpr uint8_t REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType);
constexpr uint8_t IMM_1_REG_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType)
+ sizeof(Method::RegType);
constexpr uint8_t IMM_1_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::ImmType);
constexpr uint8_t REG_3_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 3U;
constexpr uint8_t REG_2_SIZE = sizeof(Method::OpcodeType) + sizeof(Method::RegType) * 2U;


#define ALL_INSTR_LIST(_)                       \
    _(0, MV, IMM_1_REG_1_SIZE)                  \
    _(1, STACC, REG_1_SIZE)                     \
    _(2, LDACC, REG_1_SIZE)                     \
    _(3, ADD, REG_3_SIZE)                       \
    _(4, SUB, REG_3_SIZE)                       \
    _(5, MUL, REG_3_SIZE)                       \
    _(6, DIV, REG_3_SIZE)                       \
    _(7, CMPEQ, REG_2_SIZE)                     \
    _(8, CMPGT, REG_2_SIZE)                     \
    _(9, CMPGE, REG_2_SIZE)                     \
    _(10, JMP, IMM_1_SIZE)                      \
    _(11, CJMPT, IMM_1_SIZE)                    \
    _(12, CJMPF, IMM_1_SIZE)                    \
    _(13, CALL, IMM_1_SIZE)                     \
    _(14, RET, OPCODE_SIZE)                     \
    _(15, CALLNAPI, IMM_1_SIZE)