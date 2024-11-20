#include "executor.hh"
#include "frame.hh"
#include <cstdint>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <iostream>

#define SET_REG(reg, val)                                                   \
method->setReg(reg, val)

#define GET_REG(reg)                                                        \
method->getReg(reg)

#ifndef COMPUTED_GOTO

#define ARITHMETICAL(operator, name)                                        \
case name:                                                                  \
{                                                                           \
    SET_REG(instr.rd, GET_REG(instr.rs1) operator GET_REG(instr.rs2));      \
    break;                                                                  \
}

#define COMPARE(operator, name)                                             \
case name:                                                                  \
{                                                                           \
    accumulator_ = GET_REG(instr.rs1) operator GET_REG(instr.rs2) ;         \
    break;                                                                  \
}

#define JUMP(conditional, name, mark)                                       \
case name:                                                                  \
{                                                                           \
    if(conditional) {                                                       \
        method->setPC(method->getMark(mark) - 1);                           \
    }                                                                       \
    break;                                                                  \
}

#else

#define PC_NEXT(method)                                                     \
    method->setPC(method->getPC() + 1);

#define RUN_NEXT_INST(method)                                               \
    PC_NEXT(method)                                                         \
    instr = method->getInstrPC();                                           \
    goto *gotoLabels[static_cast<int>(instr.opcode)];                       \

#define ARITHMETICAL(label, method, operator)                               \
  label:                                                                    \
    SET_REG(instr.rd, GET_REG(instr.rs1) operator GET_REG(instr.rs2));      \
    RUN_NEXT_INST(method)                                                   \

#define COMPARE(label, method, operator)                                    \
  label:                                                                    \
    accumulator_ = GET_REG(instr.rs1) operator GET_REG(instr.rs2) ;         \
    RUN_NEXT_INST(method)                                                   \

#define JUMP(label, method, conditional, mark)                              \
  label:                                                                    \
    if(conditional) {                                                       \
        method->setPC(method->getMark(mark) - 1);                           \
    }                                                                       \
    RUN_NEXT_INST(method)                                                   \

#endif

void Executor::handleCall(const std::string& callMethod)
{
    if(cleanMethodList_.find(callMethod) == cleanMethodList_.end())
    {
        throw std::runtime_error("NO SUCH METHOD");
    }
    auto newFrame = std::make_shared<Frame::Frame>(cleanMethodList_[callMethod]);
    if(!callStack_.empty())
    {
        newFrame->copyParams(*(callStack_.back()));
    }
    callStack_.push_back(newFrame);
}

void Executor::simpleInterpreter(const std::string &EntryPoint)
{
    handleCall(EntryPoint);
#ifndef COMPUTED_GOTO
    uint64_t numOfOperations = 0;
    while(!callStack_.empty())
    {
        auto method = callStack_.back();
        auto instr = method->getInstrPC();
        switch(instr.opcode)
        {
            case Frame::OpcodeTable::MV:
            {
                SET_REG(instr.rd, instr.immedeate);
                break;
            }

            case Frame::OpcodeTable::STACC:
            {
                accumulator_ = GET_REG(instr.rs1);
                break;
            }

            case Frame::OpcodeTable::LDACC:
            {
                SET_REG(instr.rd, accumulator_);
                break;
            }

            ARITHMETICAL(+, Frame::OpcodeTable::ADD)
            ARITHMETICAL(-, Frame::OpcodeTable::SUB)
            ARITHMETICAL(*, Frame::OpcodeTable::MUL)
            ARITHMETICAL(/, Frame::OpcodeTable::DIV)

            COMPARE(==, Frame::OpcodeTable::CMPEQ)
            COMPARE(>, Frame::OpcodeTable::CMPGT)
            COMPARE(>=, Frame::OpcodeTable::CMPGE)

            JUMP(true, Frame::OpcodeTable::JMP, instr.mark)
            JUMP(accumulator_ == 1, Frame::OpcodeTable::CJMPT, instr.mark)
            JUMP(accumulator_ != 1, Frame::OpcodeTable::CJMPF, instr.mark)

            case Frame::OpcodeTable::CALL:
            {
                handleCall(instr.mark);
                break;
            }

            case Frame::OpcodeTable::RET:
            {
                callStack_.pop_back();
                break;
            }
            case Frame::OpcodeTable::PRINT:
            {
                std::cout << instr.mark << GET_REG(instr.rs1) << std::endl;
                break;
            }
        }
        numOfOperations++;
        method->setPC(method->getPC() + 1);
    }
    std::cout << "[EXECUTED NUMBER OF OPERATIONS]: " << numOfOperations << std::endl;

#else
    const void* gotoLabels[] = {&&MV, &&STACC, &&LDACC, &&ADD, &&SUB, &&MUL, &&DIV, &&CMPEQ, 
    &&CMPGT, &&CMPGE, &&JMP, &&CJMPT, &&CJMPF, &&CALL, &&RET, &&PRINT};
    std::shared_ptr<Frame::Frame> method = callStack_.back();
    Frame::Instr instr = method->getInstrPC();
  GETMETHOD:
    method = callStack_.back();
    instr = method->getInstrPC();
    goto *gotoLabels[static_cast<int>(instr.opcode)];

  MV:
    SET_REG(instr.rd, instr.immedeate);
    RUN_NEXT_INST(method)
    
  STACC:
    accumulator_ = GET_REG(instr.rs1);
    RUN_NEXT_INST(method)

  LDACC:
    SET_REG(instr.rd, accumulator_);
    RUN_NEXT_INST(method)

    ARITHMETICAL(ADD, method, +)
    ARITHMETICAL(SUB, method, -)
    ARITHMETICAL(MUL, method, *)
    ARITHMETICAL(DIV, method, /)

    COMPARE(CMPEQ, method, ==)
    COMPARE(CMPGT, method, >)
    COMPARE(CMPGE, method, >=)

    JUMP(JMP, method, true, instr.mark)
    JUMP(CJMPT, method, accumulator_ == 1, instr.mark)
    JUMP(CJMPF, method, accumulator_ != 1, instr.mark)

  CALL:
    PC_NEXT(method)
    handleCall(instr.mark);
    goto GETMETHOD;


  RET:
    callStack_.pop_back();
    if(!callStack_.empty())
    {
        goto GETMETHOD;
    }
    goto END;
    

  PRINT:
    std::cout << instr.mark << GET_REG(instr.rs1) << std::endl;
    RUN_NEXT_INST(method)

  END:
    return;

#endif


}