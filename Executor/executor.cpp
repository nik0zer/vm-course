#include "executor.hh"
#include "instruction.hh"
#include "method.hh"

void Executor::handleInstruction(Instruction::Instr& instr, Frame::Method& frame)
{
    
}

void Executor::handleCall(const std::string& callMethod) 
{
    callStack_.push_back(cleanMethodList_[callMethod]->getCleanCopy());
}

const Frame::RegValue& Executor::getAccumulator() 
{
    return accumulator_;
}