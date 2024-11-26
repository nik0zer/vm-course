#include "executor.hh"
#include "method.hh"
#include <cstdint>
#include "all_instrs.hh"

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