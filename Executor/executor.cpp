#include "executor.hh"
#include "method.hh"
#include <cstdint>


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
    _(4, SUB, REG_3_SIZE)                       \
    _(5, MUL, REG_3_SIZE)                       \
    _(3, ADD, REG_3_SIZE)                       \
    _(6, DIV, REG_3_SIZE)                       \
    _(7, CMPEQ, REG_2_SIZE)                     \
    _(8, CMPGT, REG_2_SIZE)                     \
    _(9, CMPGE, REG_2_SIZE)                     \
    _(10, JMP, IMM_1_SIZE)                      \
    _(11, CJMPT, IMM_1_SIZE)                    \
    _(12, CJMPF, IMM_1_SIZE)                    \
    _(13, CALL, IMM_1_SIZE)                     \
    _(14, RET, OPCODE_SIZE)                      \
    _(15, CALLNAPI, IMM_1_SIZE)

#define CASE_INSTR(opcode, name, size)          \
    case opcode:                                \
        handle##name(frame);                    \
        break;

#define GENERATE_DISPATCH_SWITCH(frame, opcode) \
    switch (opcode) {                           \
        ALL_INSTR_LIST(CASE_INSTR)              \
    }


#define SET_REG(reg, val)                                                   \
    method->setReg(reg, val)

#define GET_REG(reg)                                                        \
    method->getReg(reg)

#define MV(name)                                                            \
inline void name (Method::RegType rd, Method::RegType imm) {                \
    SET_REG(rd, imm);                                                       \
}

#define ARITHMETICAL(operator, name)                                        \
inline void name (RegType rd, RegType rs1, RegType rs2) {                   \
    SET_REG(rd, GET_REG(rs1) operator GET_REG(rs2));                        \
}

#define COMPARE(operator, name)                                             \
inline void name (RegType rs1, RegType rs2) {                               \
    accumulator_ = GET_REG(rs1) operator GET_REG(rs2) ;                     \
}

#define JUMP(conditional, name, offset)                                     \
inline void name (RegType offset) {                                         \
    if(conditional) {                                                       \
        method->setPC(method->getMark(offset) - 1);                         \
    }                                                                       \
}

namespace Executor
{

void Executor::handleCall(int callMethod)
{

}

void Executor::simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame)
{

#ifndef COMPUTED_GOTO
    uint64_t numOfOperations = 0;
    while(true)
    {
        auto frame = stackPtr_;
        auto opcode = frame->getBytecodePC<const uint8_t>();
        GENERATE_DISPATCH_SWITCH(frame, opcode);
    }
#endif
}

}