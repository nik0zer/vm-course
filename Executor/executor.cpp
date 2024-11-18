#include "executor.hh"
#include "method.hh"
#include <stdexcept>

#define SET_REG(reg, val) \
method->setReg(reg, val);

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
        }
    }
#endif
}