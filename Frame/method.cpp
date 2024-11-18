#include "method.hh"
#include "executor.hh"

#include <stdexcept>

namespace Frame
{

const RegValue &Method::getReg(const RegType &reg)
{
    if(reg >= allRegisters_)
    {
        throw std::runtime_error("REG NUM OUT OF BOUNDS");
    }
    return regFile_[reg];
}

void Method::setReg(const RegType &reg, const RegValue &val)
{
    if(reg >= allRegisters_)
    {
        throw std::runtime_error("REG NUM OUT OF BOUNDS");
    }
    regFile_[reg] = val;
}

void Method::addInstruction(Frame::Instr instr) 
{
    instructionSet_.push_back(instr); 
}

std::shared_ptr<Method> Method::getCleanCopy() const 
{
    return std::make_shared<Method>(*this);
}

void Method::setPC(const RegValue &pc)
{
    PC = pc;
}

const RegValue &Method::getPC()
{
    return PC;
}
}