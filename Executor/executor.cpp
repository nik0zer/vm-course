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

void Executor::handleCall(const std::string& callMethod)
{
    if(cleanMethodList_.find(callMethod) == cleanMethodList_.end())
    {
        throw std::runtime_error("NO SUCH METHOD");
    }
    callStack_.push_back(std::make_shared<Frame::Frame>(cleanMethodList_[callMethod]));
}

void Executor::simpleInterpreter(const std::string &EntryPoint)
{
#ifdef DISPATCH_TABLE

#else
    uint64_t numOfOperations = 0;
    handleCall(EntryPoint);
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
#endif
}