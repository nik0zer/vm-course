#include "executor.hh"
#include "method.hh"
#include <cstdint>
#include "all_instrs.hh"



namespace Executor
{

#define CASE_INSTR(opcode, name, size)                                              \
    case opcode:                                                                    \
        handle##name(frame, acc);                                                   \
        break;

#define GENERATE_DISPATCH_SWITCH()                                                  \
    while(true)                                                                     \
    {                                                                               \
        auto opcode = frame->getBytecodePC<const uint8_t>();                        \
        switch (opcode) {                                                           \
            ALL_INSTR_LIST(CASE_INSTR)                                              \
        }                                                                           \
    }


#define SET_REG(method, reg, val)                                                   \
    method->setReg(reg, val)

#define GET_REG(method, reg)                                                        \
    method->getReg(reg)

#define SET_PC(method, pc)                                                          \
    method->setPC(pc)

#define GET_PC(method)                                                              \
    method->getPC()

static inline void handleMV(Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    auto imm = frame->getBytecodePC<const Method::ImmType>();
    SET_REG(frame, reg, imm);
}

static inline void handleSTACC(Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    acc = GET_REG(frame, reg);
}

static inline void handleLDACC(Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    SET_REG(frame, reg, acc);
}

#define ARITHMETICAL(operator, name, acc)                                           \
static inline void name (Frame::Frame *frame, Method::RegValue &##acc) {            \
    SET_REG(rd, GET_REG(rs1) operator GET_REG(rs2));                                \
}

#define COMPARE(operator, name, acc)                                                \
static inline void name (Frame::Frame *frame, Method::RegValue &##acc) {            \
    accumulator_ = GET_REG(rs1) operator GET_REG(rs2) ;                             \
}

#define JUMP(conditional, name, offset, acc)                                        \
static inline void name (Frame::Frame *frame, Method::RegValue &##acc) {            \
    auto offset = frame->getBytecodePC<const uint32_t>();                           \
    SET_PC(frame, GET_PC(frame));                                                   \
    if(conditional) {                                                               \
        method->setPC(method->getMark(offset) - 1);                                 \
    }                                                                               \
}


void Executor::simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame)
{
    uint64_t numOfOperations = 0;
    auto frame = stackPtr_;
    auto acc = frame->getAcc();
#ifndef COMPUTED_GOTO
    GENERATE_DISPATCH_SWITCH()
#endif
}

}