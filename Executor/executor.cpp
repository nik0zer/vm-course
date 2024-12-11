#include "executor.hh"
#include "method.hh"
#include <cstdint>
#include "all_instrs.hh"



namespace Executor
{

#ifndef COMPUTED_GOTO

#define CASE_INSTR(opcode, name, size)                                              \
    case opcode:                                                                    \
        handle##name(this, frame, acc);                                             \
        break;

#define GENERATE_DISPATCH_SWITCH()                                                  \
    while(true)                                                                     \
    {                                                                               \
        numOfOperations++;                                                          \
        auto opcode = frame->getBytecodePC<Method::OpcodeType>();                   \
        switch (opcode) {                                                           \
            ALL_INSTR_LIST(CASE_INSTR)                                              \
        }                                                                           \
    }

#endif

#ifdef COMPUTED_GOTO

#define CASE_INSTR(opcode, name, size)                                              \
    name:                                                                           \
    numOfOperations++;                                                              \
    handle##name(this, frame, acc);                                                 \
    instrOpcode = frame->getBytecodePC<Method::OpcodeType>();                       \
    goto *instrMarks[instrOpcode];                                                  \

#define CREATE_GOTO_LABELS(opcode, name, size)                                      \
    &&name,                                                                         \


#define GENERATE_DISPATCH_SWITCH()                                                  \
    static void *instrMarks[] = {ALL_INSTR_LIST(CREATE_GOTO_LABELS)};               \
    auto instrOpcode = frame->getBytecodePC<Method::OpcodeType>();                  \
    goto *instrMarks[instrOpcode];                                                  \
    ALL_INSTR_LIST(CASE_INSTR)                                                      \

#endif


#define SET_REG(method, reg, val)                                                   \
    method->setReg(reg, val)

#define GET_REG(method, reg)                                                        \
    method->getReg(reg)

#define SET_PC(method, pc)                                                          \
    method->setPC(pc)

#define GET_PC(method)                                                              \
    method->getPC()

static inline void handleMV(Executor *executor, Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    auto imm = frame->getBytecodePC<const Method::ImmType>();
    SET_REG(frame, reg, imm);
}

static inline void handleSTACC(Executor *executor, Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    acc = GET_REG(frame, reg);
}

static inline void handleLDACC(Executor *executor, Frame::Frame *frame, Method::RegValue &acc) {
    auto reg = frame->getBytecodePC<const Method::RegType>();
    SET_REG(frame, reg, acc);
}

#define ARITHMETICAL(operator, name, acc)                                                               \
static inline void handle##name (Executor *executor, Frame::Frame *frame, Method::RegValue& acc) {      \
    auto rd = frame->getBytecodePC<const Method::RegType>();                                            \
    auto rs1 = frame->getBytecodePC<const Method::RegType>();                                           \
    auto rs2 = frame->getBytecodePC<const Method::RegType>();                                           \
    SET_REG(frame, rd, GET_REG(frame, rs1) operator GET_REG(frame, rs2));                               \
}

ARITHMETICAL(+, ADD, acc)
ARITHMETICAL(*, MUL, acc)
ARITHMETICAL(-, SUB, acc)
ARITHMETICAL(/, DIV, acc)

#define COMPARE(operator, name, acc)                                                                    \
static inline void handle##name (Executor *executor, Frame::Frame *frame, Method::RegValue& acc) {      \
    auto rs1 = frame->getBytecodePC<const Method::RegType>();                                           \
    auto rs2 = frame->getBytecodePC<const Method::RegType>();                                           \
    acc = GET_REG(frame, rs1) operator GET_REG(frame, rs2);                                             \
}

COMPARE(==, CMPEQ, acc)
COMPARE(>, CMPGT, acc)
COMPARE(>=, CMPGE, acc)

#define JUMP(conditional, name, acc)                                                                    \
static inline void handle##name (Executor *executor, Frame::Frame *frame, Method::RegValue& acc) {      \
    auto offset = frame->getBytecodePC<const Method::OffsetType>();                                     \
    if(conditional) {                                                                                   \
        SET_PC(frame, GET_PC(frame) + offset);                                                          \
    }                                                                                                   \
}

JUMP(true, JMP, acc)
JUMP(acc != 0, CJMPT, acc)
JUMP(acc == 0, CJMPF, acc)

static inline void handleCALL(Executor *executor, Frame::Frame *frame, Method::RegValue &acc) {
    auto callMark = frame->getBytecodePC<const Method::CallMarkType>();
    frame->setAcc(acc);
    executor->simpleInterpreterExecute(executor->getMethod(callMark), frame);
    acc = frame->getAcc();  
}

#define handleRET(this, frame, acc)                                                                     \
    frame->setAcc(acc);                                                                                 \
    if(frame->getPrevFrame() != nullptr) { frame->getPrevFrame()->setAcc(acc); }                        \
    return;

static inline void handleCALLNAPI(Executor *executor, Frame::Frame *frame, Method::RegValue &acc) {
    auto address = const_cast<uint8_t *>(frame->getBytecodePC<Method::AddressType>());
    frame->setAcc(acc);
    executor->nativeExecute(address, frame);
}



void Executor::simpleInterpreterExecute(Method::Method *method, Frame::Frame *prevFrame)
{
    auto frame = new (stackPtr_) Frame::Frame(method, prevFrame, &stackPtr_);
    if(prevFrame != nullptr) { frame->copyParams(*prevFrame); }
    auto acc = frame->getAcc();
    GENERATE_DISPATCH_SWITCH()
}

void Executor::nativeExecute(void *nativeMethod, Frame::Frame *prevFrame)
{
    auto nativeCall = reinterpret_cast<void (*)(Frame::Frame *)>(nativeMethod);
    nativeCall(prevFrame);
}

}