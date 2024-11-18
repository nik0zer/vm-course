#include "executor.hh"
#include "method.hh"
#include <stdexcept>

#define SET_REG(reg, val)                                                   \
method->setReg(reg, val);

#define ARITHMETICAL(operator, name)                                        \
case name:                                                                  \
{                                                                           \
    SET_REG(instr.rd, instr.rs1 operator instr.rs2)                         \
    break;                                                                  \
}

#define COMPARE(operator, name)                                             \
case name:                                                                  \
{                                                                           \
    SET_REG(accumulator_, instr.rs1 operator instr.rs2)                     \
    break;                                                                  \
}

#define JUMP(conditional, name, mark)                                       \
case name:                                                                  \
{                                                                           \
    if(conditional) {                                                       \
        method->setPC(method->marks[mark]);                                 \
        break;                                                              \
    }                                                                       \
}

void Executor::handleCall(const std::string& callMethod) 
{
    if(cleanMethodList_.find(callMethod) == cleanMethodList_.end())
    {
        throw std::runtime_error("NO SUCH METHOD");
    }
    callStack_.push_back(cleanMethodList_[callMethod]->getCleanCopy());
}

void Executor::simpleInterpreter(const std::string &EntryPoint)
{
#ifdef DISPATCH_TABLE

#else
    handleCall(EntryPoint);
    while(!callStack_.empty())
    {
        auto method = callStack_.back();
        auto instr = method->instructionSet_[method->getPC()];
        switch(instr.opcode)
        {
            case Frame::OpcodeTable::MV:
            {
                SET_REG(instr.rd, instr.immedeate)
                break;
            }

            case Frame::OpcodeTable::STACC:
            {
                SET_REG(accumulator_, instr.rs1)
                break;
            }

            case Frame::OpcodeTable::LDACC:
            {
                SET_REG(instr.rd, accumulator_)
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
            JUMP(accumulator_, Frame::OpcodeTable::CJMPT, instr.mark)
            JUMP(!accumulator_, Frame::OpcodeTable::CJMPF, instr.mark)

            case Frame::OpcodeTable::CALL:
            {
                handleCall(instr.mark);
                break;
            }

            case Frame::OpcodeTable::RET:
            {
                callStack_.pop_back();
            }
        }
    }
#endif
}