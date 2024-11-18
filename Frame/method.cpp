#include "method.hh"

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

const RegValue &Method::getAccumulator (Executor& exec) 
{
    return exec.getAccumulator();
}

void Method::setAccumulator(Executor& exec, const RegValue &val) 
{
    exec.setAccumulator(val);
}

void Method::addInstruction(std::string opcode, Frame::RegType rd, Frame::RegType rs1, Frame::RegType rs2, Frame::Imm immedeate) 
{
    Instruction::Instr instr{opcode, rd, rs1, rs2, immedeate}; 
    instructionSet_.push_back(instr); 
}

std::shared_ptr<Method> Method::getCleanCopy() const 
{
    return std::make_shared<Method>(*this);
}
}